#include "Renderer.h"

#include "ServiceProvider/ServiceProvider.h"
#include "VertexData.h"

#include "ECS/Camera/Camera.h"
#include "ECS/Transform/ECSTransform.h"
#include "ECS/Mesh/MeshID.h"
#include "ECS/MaterialID.h"
#include "ECS/WaveObject/WaveObject.h"
#include "Material/MaterialFactory.h"
#include "Material/Material.h"
#include "FileReader/FileReader.h"
#include "WaveMath/Vector4/Vector4.h"
#include "BoundingBox/BoundingBox.h"

#define MAX_INSTANCES 1000

using namespace std;

namespace WaveEngine
{
	DirLight Renderer::dirLight;
	SpotLight Renderer::flashLights[Renderer::Amount_Per_Light];
	PointLight Renderer::pointLight[Renderer::Amount_Per_Light];

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

	ComponentRegistry* Renderer::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}

	MaterialFactory* Renderer::GetMaterialFactory()
	{
		return ServiceProvider::Instance().Get<MaterialFactory>();
	}

	FileReader* Renderer::GetFileReader()
	{
		return ServiceProvider::Instance().Get<FileReader>();
	}

	void Renderer::Init()
	{
		glViewport(0, 0, GetWindow()->GetWidth(), GetWindow()->GetHeight());

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_CULL_FACE);

		debugMaterialID = GetMaterialFactory()->CreateMaterial("WireFrame", GetFileReader()->ReadFile("Shaders/WireFrame/WireFrame.vert"), GetFileReader()->ReadFile("Shaders/WireFrame/WireFrame.frag"));
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

		glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, tangent));
		glEnableVertexAttribArray(8);

		glBindVertexArray(0);
	}

	void Renderer::UpdateBuffer(const VertexData* vertex, int vertexSize, unsigned& VBO)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertexSize * sizeof(VertexData), vertex);
	}

	void Renderer::SubmitWireBox(const BoundingBox& box, const Color& color)
	{
		debugBoxes.push_back({ box, color });
	}

	void Renderer::DrawWireBoxImmediate(const BoundingBox& box, const Color& color)
	{
		glm::vec3 min(box.GetMin().x, box.GetMin().y, box.GetMin().z);
		glm::vec3 max(box.GetMax().x, box.GetMax().y, box.GetMax().z);

		std::vector<glm::vec3> vertices =
		{
			{ min.x, min.y, min.z },
			{ max.x, min.y, min.z },
			{ max.x, min.y, max.z },
			{ min.x, min.y, max.z },
			{ min.x, max.y, min.z },
			{ max.x, max.y, min.z },
			{ max.x, max.y, max.z },
			{ min.x, max.y, max.z }
		};

		const GLuint indices[] = {
			0, 1, 1, 2, 2, 3, 3, 0, // Bottom face
			4, 5, 5, 6, 6, 7, 7, 4, // Top face
			0, 4, 1, 5, 2, 6, 3, 7  // Vertical edges
		};

		GLuint VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		Camera& camera = GetComponentRegistry()->GetComponentStorage<Camera>().GetFirst();
		Material* mat = GetMaterialManager()->GetMaterial(debugMaterialID);

		if (!mat)
		{
			glBindVertexArray(0);
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
			return;
		}

		mat->Bind();
		mat->SetMat4("uView", camera.GetView());
		mat->SetMat4("uProj", camera.GetProjection());
		mat->SetMat4("uModel", glm::mat4(1.0f));
		mat->SetColor(color);

		glDrawElements(GL_LINES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		mat->UnBind();

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
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
		batch.instances.push_back({ transform.GetGlobalModel() });
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

			if (mesh.GetDirty())
			{
				UpdateBuffer(mesh.GetVertexBuffer(), mesh.GetVertexSize(), batch.VBO);
				mesh.UnDirt();
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
				GetMaterialManager()->GetMaterial(batch.batchData.materialID);

			if (!materialToUse)
				continue;

			materialToUse->Bind();

			Camera& camera = GetComponentRegistry()
				->GetComponentStorage<Camera>()
				.GetFirst();

			ECSTransform& cameraTransform = camera.GetWaveObject().GetTransform();

			glm::mat4 view = camera.GetView();
			glm::mat4 proj = camera.GetProjection();

			materialToUse->SetVec4("uColor", materialToUse->GetColor());
			materialToUse->SetMat4("uView", view);
			materialToUse->SetMat4("uProj", proj);

			materialToUse->SetVec3("dirLight.direction", dirLight.direction);
			materialToUse->SetVec3("dirLight.ambient", dirLight.ambient);
			materialToUse->SetVec3("dirLight.diffuse", dirLight.diffuse);
			materialToUse->SetVec3("dirLight.specular", dirLight.specular);

			for (int i = 0; i < Amount_Per_Light; ++i)
			{
				string base = "pointLights[" + std::to_string(i) + "]";

				materialToUse->SetVec3(base + ".position", pointLight[i].position);

				materialToUse->SetVec3(base + ".ambient", pointLight[i].ambient);
				materialToUse->SetVec3(base + ".diffuse", pointLight[i].diffuse);
				materialToUse->SetVec3(base + ".specular", pointLight[i].specular);

				materialToUse->SetFloat(base + ".constant", pointLight[i].constant);
				materialToUse->SetFloat(base + ".linear", pointLight[i].linear);
				materialToUse->SetFloat(base + ".quadratic", pointLight[i].quadratic);
			}

			materialToUse->SetVec3("viewPos", cameraTransform.position);

			for (int i = 0; i < Amount_Per_Light; ++i)
			{
				string base = "flashlights[" + std::to_string(i) + "]";

				materialToUse->SetVec3(base + ".position", flashLights[i].position);

				materialToUse->SetVec3(base + ".direction", flashLights[i].direction);

				materialToUse->SetVec3(base + ".ambient", flashLights[i].ambient);
				materialToUse->SetVec3(base + ".diffuse", flashLights[i].diffuse);
				materialToUse->SetVec3(base + ".specular", flashLights[i].specular);

				materialToUse->SetFloat(base + ".constant", flashLights[i].constant);
				materialToUse->SetFloat(base + ".linear", flashLights[i].linear);
				materialToUse->SetFloat(base + ".quadratic", flashLights[i].quadratic);

				materialToUse->SetFloat(base + ".cutOff", glm::cos(glm::radians(flashLights[i].cutOff)));
				materialToUse->SetFloat(base + ".outerCutOff", glm::cos(glm::radians(flashLights[i].outerCutOff)));
			}

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

	void Renderer::FlushDebug()
	{
		//glDisable(GL_DEPTH_TEST);

		for (std::pair<BoundingBox, Color> pair : debugBoxes)
			DrawWireBoxImmediate(pair.first, pair.second);

		//glEnable(GL_DEPTH_TEST);
		debugBoxes.clear();
	}

	void Renderer::Unload()
	{
		for (auto& renderData : batching)
			DeleteBuffers(renderData.second.VAO, renderData.second.VBO, renderData.second.EBO);
	}
}