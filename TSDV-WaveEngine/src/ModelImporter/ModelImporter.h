#pragma once

#include <string>
#include <filesystem>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/material.h>
#include <assimp/Importer.hpp>

#include "Material/Material.h"
#include "FileReader/FileReader.h"
#include "ServiceProvider/Service.h"
#include "Material/MaterialFactory.h"
#include "Material/MaterialManager.h"
#include "ECS/Transform/ECSTransform.h"
#include "Mesh/MeshFactory/MeshFactory.h"
#include "Mesh/MeshManager/MeshManager.h"
#include "TextureImporter/TextureManager.h"
#include "TextureImporter/TextureImporter.h"
#include "ECS/WaveObject/WaveObjectFactory.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"

using namespace std;

namespace WaveEngine
{
	class WaveObject;

	class ModelImporter final : public Service
	{
	private:

		const aiScene* pScene = nullptr;
		Assimp::Importer importer;
		filesystem::path directory;
		string filename = "";

		MeshFactory* GetMeshFactory();
		MeshManager* GetMeshManager();
		TextureImporter* GetTextureImporter();
		FileReader* GetFileReader();
		MaterialFactory* GetMaterialFactory();
		MaterialManager* GetMaterialManager();
		TextureManager* GetTextureManager();
		WaveObjectRegistry* GetWaveObjectRegistry();
		WaveObjectFactory* GetWaveObjectFactory();

		unsigned int LoadMaterialTextures(aiMaterial* mat, aiTextureType type);

		void ProcessNode(aiNode* node, WaveObject& waveObject);
		void ProcessMesh(aiMesh* meshRenderer, WaveObject& meshWaveObject);
		Material* ProcessMaterial(aiMaterial* aiMaterial);
		void ApplyNodeTransform(ECSTransform& transform, const aiNode* node);

		std::filesystem::path FindTexture(
			const std::filesystem::path& modelDirectory,
			const std::string& textureName);

	public:

		void LoadScene(filesystem::path filePath, const bool useAbsolutePath = true);
		WaveObject* IntantiateModel(const char* rootName = nullptr);
	};
}