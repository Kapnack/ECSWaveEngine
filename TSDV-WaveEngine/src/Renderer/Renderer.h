#pragma once

#include "ServiceProvider/Service.h"

#include <glm/glm.hpp>

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
#include "WaveMath/Vector3/Vector3.h"
#include "BoundingBox/BoundingBox.h"
#include "WaveMath/Vector4/Vector4.h"
#include "Material/Material.h"
#include "FileReader/FileReader.h"
#include "Material/MaterialFactory.h"
#include "Material/Color/Color.h"
#include <utility>

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
		Vector3 position = { 96, 64.0f, 0.0f };
		Vector3 direction = Vector3::Down();

		Vector3 ambient = Vector3::One() * 0.1f;
		Vector3 diffuse = Vector3::One();
		Vector3 specular = Vector3::One();

		float constant = 1.0f;
		float linear = 0.00032f;
		float quadratic = 0.00032f;

		float cutOff = 12.5f;
		float outerCutOff = 15.5f;
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
		};

		unordered_map<size_t, RenderData> batching;

		vector<pair<BoundingBox, Color>> debugBoxes;

		unsigned int drawCalls = 0;
		unsigned int batchCalls = 0;

		unsigned int debugMaterialID = Material::NULL_MATERIAL;

		void Init();
		void Unload();

		const unsigned int ReturnWorkingMaterial(const unsigned int& materialIDToTry, const unsigned int& materialIDfallBack);

		Window* GetWindow();

		MaterialManager* GetMaterialManager();

		MeshManager* GetMeshManager();

		TextureManager* GetTextureManager();

		void UpdateBuffer(VertexData* vertex, int vertexSize, unsigned& VBO);

		ComponentRegistry* GetComponentRegistry();

		MaterialFactory* GetMaterialFactory();

		FileReader* GetFileReader();

	public:

		static const int Amount_Per_Light = 2;

		static DirLight dirLight;
		static PointLight pointLight[Amount_Per_Light];
		static SpotLight flashLights[Amount_Per_Light];

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

		void UpdateBuffer(const VertexData* vertex, int vertexSize, unsigned& VBO);

		void SubmitWireBox(const BoundingBox& box, const Color& color = Color::Red());
		void DrawWireBoxImmediate(const BoundingBox& box, const Color& color);

		void Clear();

		unsigned int GetDrawCalls() const;
		unsigned int GetBatchCalls() const;

		void Submit(const ECSTransform& transform, const MeshID& meshComp, const MeshRenderer& matComp);
		void Flush();
		void FlushDebug();
	};
}

