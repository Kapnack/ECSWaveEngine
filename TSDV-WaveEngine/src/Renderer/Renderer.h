#pragma once

#include "ServiceProvider/Service.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <functional>

#include "Window/Window.h"
#include "TextureImporter/TextureImporter.h"
#include "VertexData.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include <unordered_map>
#include <Mesh/MeshManager/MeshManager.h>
#include <Material/MaterialManager.h>

using namespace std;

namespace WaveEngine
{
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


		struct RenderData
		{
			BatchData batchData;

			unsigned int VAO = 0;
			unsigned int VBO = 0;
			unsigned int EBO = 0;

			vector<VertexData> vertices;
			vector<unsigned int> indices;

			unsigned int indexOffset = 0;
		};

		unordered_map<size_t, RenderData> batching;

		unsigned int shapeShaders;
		unsigned int spriteShaders;

		unsigned int drawCalls = 0;

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

		Renderer();
		~Renderer();

		void CreateBuffers(const VertexData* vertex, const int& vertexSize, const unsigned int* indices, const int& indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO) const;

		void DeleteBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

		void UpdateBuffer(VertexData* vertex, int vertexSize, unsigned& VBO);

		void Clear();

		unsigned int GetDrawCalls() const;

		void DrawElement(const unsigned int& materialID, const unsigned int& indicesSize, const unsigned int& VAO);

		void Submit(const int& entityID);
		void Flush();
	};
}

