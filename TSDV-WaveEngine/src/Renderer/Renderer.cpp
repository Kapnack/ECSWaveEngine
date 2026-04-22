#include "Renderer.h"

#include "FileReader/FileReader.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialFactory.h"
#include "VertexData.h"

#include "ECS/Camera/Camera.h"
#include <ECS/Transform/ECSTransform.h>
#include <ECS/Mesh/MeshID.h>
#include <ECS/MaterialID.h>

#define MAX_INSTANCES 1000

using namespace std;

namespace WaveEngine
{
	Renderer::Renderer()
	{
		Init();
	}

	Renderer::~Renderer()
	{
		Unload();
	}

	Window* Renderer::GetWindow()
	{
		return ServiceProvider::Instance().Get<Window>();
	}

	MaterialManager* Renderer::GetMaterialManager()
	{
		return ServiceProvider::Instance().Get<MaterialManager>();
	}

	MeshManager* Renderer::GetMeshManager()
	{
		return ServiceProvider::Instance().Get<MeshManager>();
	}

	TextureManager* Renderer::GetTextureManager()
	{
		return ServiceProvider::Instance().Get<TextureManager>();
	}

	Texture* Renderer::ChooseTextureToUse(const unsigned int& ID)
	{
		return GetTextureManager()->TryGetTexture(ID) ? GetTextureManager()->GetTexture(ID) : GetTextureManager()->GetTexture(defualtTextureID);
	}

	ComponentRegistry* Renderer::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}

	void Renderer::Init()
	{
		defualtTextureID = ServiceProvider::Instance().Get<TextureImporter>()->LoadTextureAbsolutePath("Sprites/whiteImage.png");

		glViewport(0, 0, GetWindow()->GetWidth(), GetWindow()->GetHeight());

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_CULL_FACE);

		FileReader* fileReader = ServiceProvider::Instance().Get<FileReader>();

		string vertexShader = fileReader->ReadFile("Shaders/Shapes/basicVertexShader.shader");

		string fragmentShader = fileReader->ReadFile("Shaders/Shapes/defaultFragmentShader.shader");

		shapeShaders = ServiceProvider::Instance().Get<MaterialFactory>()->CreateMaterial("defaultShapeShader", vertexShader, fragmentShader);

		vertexShader = fileReader->ReadFile("Shaders/Sprites/basicVertexShader.shader");

		fragmentShader = fileReader->ReadFile("Shaders/Sprites/defaultFragmentShader.shader");

		spriteShaders = ServiceProvider::Instance().Get<MaterialFactory>()->CreateMaterial("defaultSpriteShader", vertexShader, fragmentShader);
	}

	const unsigned int Renderer::ReturnWorkingMaterial(const unsigned int& materialIDToTry, const unsigned int& materialIDfallBack)
	{
		return materialIDToTry != Material::NULL_MATERIAL ? materialIDToTry : materialIDfallBack;
	}

	void Renderer::CreateBuffers(
		const VertexData* vertex,
		const int& vertexSize,
		const unsigned int* indices,
		const int& indicesSize,
		unsigned& VAO,
		unsigned& VBO,
		unsigned& EBO,
		unsigned& instanceVBO
	) const
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenBuffers(1, &instanceVBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(VertexData), vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, color));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, textureCordinates));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, normal));
		glEnableVertexAttribArray(3);

		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceData) * MAX_INSTANCES, nullptr, GL_DYNAMIC_DRAW);

		for (int i = 0; i < 4; i++)
		{
			glEnableVertexAttribArray(4 + i);
			glVertexAttribPointer(
				4 + i,
				4,
				GL_FLOAT,
				GL_FALSE,
				sizeof(InstanceData),
				(void*)(offsetof(InstanceData, model) + i * sizeof(glm::vec4))
			);

			glVertexAttribDivisor(4 + i, 1);
		}

		glEnableVertexAttribArray(8);
		glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE,
			sizeof(InstanceData),
			(void*)offsetof(InstanceData, uvOffsetScale));

		glVertexAttribDivisor(8, 1);

		glBindVertexArray(0);
	}

	void Renderer::DeleteBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Renderer::UpdateBuffer(VertexData* vertex, int vertexSize, unsigned& VBO)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertexSize * sizeof(VertexData), vertex);
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawCalls = 0;
	}

	unsigned int Renderer::GetDrawCalls() const
	{
		return drawCalls;
	}

	unsigned int Renderer::GetBatchCalls() const
	{
		return batchCalls;
	}

	void Renderer::DrawElement(const unsigned int& materialID, const unsigned int& indicesSize, const unsigned int& VAO)
	{
		Material* materialToUse =
			GetMaterialManager()->GetMaterial(
				ReturnWorkingMaterial(materialID, spriteShaders));

		if (!materialToUse)
			return;

		materialToUse->Bind();

		materialToUse->SetVec4("uColor", materialToUse->GetColor());
		materialToUse->SetMat4("uView", GetComponentRegistry()->GetComponentStorage<Camera>().Get(0).GetView());
		materialToUse->SetMat4("uProj", GetComponentRegistry()->GetComponentStorage<Camera>().Get(0).GetProjection());

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, (void*)0);

		materialToUse->UnBind();

		++drawCalls;
	}

	void Renderer::Submit(const ECSTransform& transform, const MeshID& meshComp, const MeshRenderer& matComp)
	{
		++batchCalls;

		RenderData& batch =
			batching[hash<unsigned int>()(matComp.materialID) ^
			(hash<unsigned int>()(meshComp.meshID) << 1)];

		batch.batchData =
		{
			matComp.materialID,
			meshComp.meshID
		};

		batch.instances.reserve(MAX_INSTANCES);
		batch.instances.push_back({ transform.GetGlobalModel(),  glm::vec4(0.8f, 0.0f, 1.0f, 1.0f) });
	}

	void Renderer::Flush()
	{
		batchCalls = 0;

		for (auto& [key, batch] : batching)
		{
			if (batch.instances.empty())
				continue;

			Mesh& mesh = GetMeshManager()->Get(batch.batchData.meshID);

			if (batch.VAO == 0)
			{
				CreateBuffers(
					mesh.GetVertexBuffer(),
					mesh.GetVertexSize(),
					mesh.GetIndexes(),
					mesh.GetIndexesSize(),
					batch.VAO,
					batch.VBO,
					batch.EBO,
					batch.instanceVBO
				);

				batch.instanceCapacity = 0;
			}

			glBindVertexArray(batch.VAO);
			glBindBuffer(GL_ARRAY_BUFFER, batch.instanceVBO);

			if (batch.instances.size() > batch.instanceCapacity)
			{
				batch.instanceCapacity = batch.instances.size();

				glBufferData(GL_ARRAY_BUFFER,
					batch.instanceCapacity * sizeof(InstanceData),
					nullptr,
					GL_DYNAMIC_DRAW);
			}

			glBufferSubData(GL_ARRAY_BUFFER,
				0,
				batch.instances.size() * sizeof(InstanceData),
				batch.instances.data());

			Material* materialToUse =
				GetMaterialManager()->GetMaterial(
					ReturnWorkingMaterial(batch.batchData.materialID, spriteShaders));

			if (!materialToUse)
				continue;

			materialToUse->Bind();

			auto& camera = GetComponentRegistry()
				->GetComponentStorage<Camera>()
				.Get(0);

			glm::mat4 view = camera.GetView();
			glm::mat4 proj = camera.GetProjection();

			materialToUse->SetVec4("uColor", materialToUse->GetColor());
			materialToUse->SetMat4("uView", view);
			materialToUse->SetMat4("uProj", proj);
			materialToUse->SetFloat("AmbientStrength", 1.0f);
			materialToUse->SetVec3("LightColor", Vector3(0, 1, 1));

			glDrawElementsInstanced(
				GL_TRIANGLES,
				mesh.GetIndexesSize(),
				GL_UNSIGNED_INT,
				0,
				batch.instances.size()
			);

			materialToUse->UnBind();

			++drawCalls;

			batch.instances.clear();
		}
	}

	void Renderer::Unload()
	{
		for (auto& renderData : batching)
			DeleteBuffers(renderData.second.VAO, renderData.second.VBO, renderData.second.EBO);
	}
}