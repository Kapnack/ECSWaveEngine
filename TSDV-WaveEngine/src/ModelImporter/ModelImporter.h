#pragma once

#include "Export.h"

#include <filesystem>
#include <utility>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include "Mesh/MeshFactory/MeshFactory.h"
#include <TextureImporter/Texture.h>
#include <TextureImporter/TextureImporter.h>
#include <Material/MaterialFactory.h>
#include <Material/MaterialManager.h>
#include <FileReader/FileReader.h>
#include <ECS/WaveObject/WaveObjectRegistry.h>
#include <ECS/WaveObject/WaveObjectFactory.h>

using namespace std;

namespace WaveEngine
{
	WAVEEXPORT class ModelImporter
	{
	private:

		Assimp::Importer importer;
		const aiScene* pScene;
		filesystem::path directory;
		string filename;

		MeshFactory* GetMeshFactory();
		TextureImporter* GetTextureImporter();
		FileReader* GetFileReader();
		MaterialFactory* GetMaterialFactory();
		MaterialManager* GetMaterialManager();
		TextureManager* GetTextureManager();
		WaveObjectRegistry* GetWaveObjectRegistry();
		WaveObjectFactory* GetWaveObjectFactory();

		vector<unsigned int> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);

		pair<unsigned int, unsigned int> GetVertexAndIndexSizes(const aiScene& pScene);

	public:

		WAVEEXPORT void LoadScene(filesystem::path filePath, const bool useAbsolutePath = true);
		WAVEEXPORT unsigned int LoadMesh();
		WAVEEXPORT unsigned int LoadMaterial();
	};
}