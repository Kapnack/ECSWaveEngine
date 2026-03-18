#include "Renderer.h"

#include "FileReader/FileReader.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialFactory.h"
#include "VertexData.h"

#include "ECS/Camera/Camera.h"
#include <ECS/Transform/ECSTransform.h>
#include <ECS/Mesh/MeshID.h>
#include <ECS/MaterialID.h>

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

		glDisable(GL_DEPTH_TEST);
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

	void Renderer::CreateBuffers(const VertexData* vertex, const int& vertexSize, const unsigned int* indices, const int& indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO) const
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(VertexData), vertex, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, color));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, textureCordinates));
		glEnableVertexAttribArray(2);

		glVertexAttribIPointer(3, 1, GL_INT, sizeof(VertexData), (void*)offsetof(VertexData, textureID));
		glEnableVertexAttribArray(3);

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

	void Renderer::Submit(const int& entityID)
	{
		auto& registry = *GetComponentRegistry();

		if (!registry.Has<ECSTransform>(entityID) ||
			!registry.Has<MeshID>(entityID) ||
			!registry.Has<MaterialID>(entityID))
			return;

		ECSTransform& transform = registry.Get<ECSTransform>(entityID);
		MeshID& meshComp = registry.Get<MeshID>(entityID);
		MaterialID& matComp = registry.Get<MaterialID>(entityID);


		RenderData& batch = batching[std::hash<unsigned int>()(matComp.materialID) ^ (std::hash<unsigned int>()(meshComp.meshID) << 1)];
		
		batch.batchData =
		{
			matComp.materialID,
			meshComp.meshID
		};

		Mesh& mesh = GetMeshManager()->Get(meshComp.meshID);

		int baseVertex = batch.vertices.size();

		for (unsigned int v = 0; v < mesh.GetVertexSize(); ++v)
		{
			const VertexData& currentVertex = mesh.GetVertexBuffer()[v];

			VertexData newVertex = currentVertex;

			glm::vec4 pos = transform.GetModel() *
				glm::vec4(currentVertex.position.x,
					currentVertex.position.y,
					currentVertex.position.z,
					1.0f);

			newVertex.position = Vector3(pos.x, pos.y, pos.z);

			batch.vertices.push_back(newVertex);
		}

		for (unsigned int i = 0; i < mesh.GetIndexesSize(); ++i)
		{
			batch.indices.push_back(mesh.GetIndexes()[i] + baseVertex);
		}
	}

	void Renderer::Flush()
	{
		for (auto& [key, batch] : batching)
		{
			if (batch.vertices.empty())
				continue;

			if (batch.VAO == 0)
			{
				CreateBuffers(
					batch.vertices.data(),
					batch.vertices.size(),
					batch.indices.data(),
					batch.indices.size(),
					batch.VAO, batch.VBO, batch.EBO
				);
			}
			else
			{
				glBindVertexArray(batch.VAO);

				UpdateBuffer(batch.vertices.data(), batch.vertices.size(), batch.VBO);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.EBO);
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
					batch.indices.size() * sizeof(unsigned int),
					batch.indices.data());
			}

			DrawElement(
				batch.batchData.materialID,
				batch.indices.size(),
				batch.VAO
			);

			batch.vertices.clear();
			batch.indices.clear();
		}
	}

	void Renderer::Unload()
	{
		for (auto& renderData : batching)
			DeleteBuffers(renderData.second.VAO, renderData.second.VBO, renderData.second.EBO);
	}
}