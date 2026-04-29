#pragma once

#include "ServiceProvider/Service.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <functional>
#include <unordered_map>

#include "Window/Window.h"
#include "TextureImporter/TextureImporter.h"
#include "VertexData.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "Mesh/MeshManager/MeshManager.h"
#include "Material/MaterialManager.h"
#include "ECS/MaterialID.h"
#include "ECS/Mesh/MeshID.h"
#include "ECS/Transform/ECSTransform.h"

using namespace std;

namespace WaveEngine
{
	struct DirLight
	{
		Vector3 direction = { -0.41f, -0.82f, -0.39f };

		Vector3 ambient = { 0.06f, 0.06f, 0.06f };
		Vector3 diffuse = { 0.45f, 0.42f, 0.40f };
		Vector3 specular = { 0.50f, 0.50f, 0.50f };
	};

	struct PointLight
	{
		Vector3 position = { 3.8f, 1.6f, -2.9f };

		Vector3 ambient = { 0.04f, 0.04f, 0.04f };
		Vector3 diffuse = { 0.90f, 0.70f, 0.60f };
		Vector3 specular = { 1.00f, 1.00f, 1.00f };

		float constant = 1.0f;
		float linear = 0.07f;
		float quadratic = 0.017f;
	};

	struct SpotLight
	{
		Vector3 position = { 0.0f, 0.0f, 0.0f };
		Vector3 direction = { 0.0f, 0.0f, -1.0f };

		Vector3 ambient = { 0.00f, 0.00f, 0.00f };
		Vector3 diffuse = { 1.00f, 0.95f, 0.85f };
		Vector3 specular = { 1.00f, 1.00f, 1.00f };

		float constant = 1.0f;
		float linear = 0.09f;
		float quadratic = 0.032f;

		float cutOff = 0.976f; // cos(12.5°)
		float outerCutOff = 0.953f; // cos(17.5°)
	};

	struct BatchData
	{
		unsigned int materialID = 0;
		unsigned int meshID = 0;

		bool operator==(const BatchData& other) const
		{
			return materialID == other.materialID &&
				meshID == other.meshID;
		}
	};

	class Renderer final : public Service
	{
	private:

		struct InstanceData
		{
			glm::mat4 model;
			glm::vec4 uvOffsetScale;
		};

		struct RenderData
		{
			BatchData batchData;

			unsigned int VAO = 0;
			unsigned int VBO = 0;
			unsigned int EBO = 0;

			unsigned int instanceVBO = 0;

			vector<InstanceData> instances;

			int instanceCapacity = 0;

			unsigned int indexOffset = 0;

			Vector4 uvOffsetScale;
		};

		unordered_map<size_t, RenderData> batching;

		unsigned int shapeShaders;
		unsigned int spriteShaders;

		unsigned int drawCalls = 0;
		unsigned int batchCalls = 0;

		void Init();
		void Unload();

		unsigned int defualtTextureID = 0;

		const unsigned int ReturnWorkingMaterial(const unsigned int& materialIDToTry, const unsigned int& materialIDfallBack);

		Window* GetWindow();

		MaterialManager* GetMaterialManager();

		MeshManager* GetMeshManager();

		TextureManager* GetTextureManager();

		Texture* ChooseTextureToUse(const unsigned int& ID);

		ComponentRegistry* GetComponentRegistry();

	public:

		static DirLight dirLight;
		static PointLight pointLight[4];
		static SpotLight flashLight;

		Renderer();
		~Renderer();

		void CreateBuffers(
			const VertexData* vertex,
			const int& vertexSize,
			const unsigned int* indices,
			const int& indicesSize,
			unsigned& VAO,
			unsigned& VBO,
			unsigned& EBO,
			unsigned& instanceVBO
		) const;

		void DeleteBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

		void UpdateBuffer(VertexData* vertex, int vertexSize, unsigned& VBO);

		void Clear();

		unsigned int GetDrawCalls() const;
		unsigned int GetBatchCalls() const;

		void DrawElement(const unsigned int& materialID, const unsigned int& indicesSize, const unsigned int& VAO);

		void Submit(const ECSTransform& transform, const MeshID& meshComp, const MeshRenderer& matComp);
		void Flush();
	};
}

