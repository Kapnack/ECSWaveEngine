#pragma once

#include "Export.h"

#include <utility>

#include <assimp/scene.h>

#include "Mesh/MeshFactory/MeshFactory.h"

using namespace std;

namespace WaveEngine
{
	WAVEEXPORT class ModelImporter
	{
	private:

		unsigned int InitFromScene(string_view assetName, const aiScene* pScene);

		MeshFactory* GetMeshFactory();

		pair<unsigned int, unsigned int> GetVertexAndIndexSizes(const aiScene& pScene);

	public:

		WAVEEXPORT unsigned int LoadMesh(string_view assetName, const string_view filePath);
	};
}