#pragma once

#include "Export.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Mesh/MeshFactory/MeshFactory.h"

#include <string>

using namespace std;

namespace WaveEngine
{
	WAVEEXPORT class ModelImporter
	{
	private:

		unsigned int InitFromScene(string_view assetName, const aiScene* pScene, const string_view filepath);

		MeshFactory* GetMeshFactory();

	public:

		WAVEEXPORT unsigned int LoadMesh(string_view assetName, const string_view filePath);
	};
}