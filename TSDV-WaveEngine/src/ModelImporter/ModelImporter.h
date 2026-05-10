#pragma once

#include "Export.h"

#include <filesystem>
#include <utility>

#include <assimp/scene.h>

#include "Mesh/MeshFactory/MeshFactory.h"

using namespace std;

namespace WaveEngine
{
	WAVEEXPORT class ModelImporter
	{
	private:

		unsigned int InitFromScene(const string_view filename, const aiScene*& pScene);

		MeshFactory* GetMeshFactory();

		pair<unsigned int, unsigned int> GetVertexAndIndexSizes(const aiScene& pScene);

	public:

		WAVEEXPORT unsigned int LoadMesh(filesystem::path filePath, const bool useAbsolutePath = true);
	};
}