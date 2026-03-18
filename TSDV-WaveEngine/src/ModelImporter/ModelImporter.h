#pragma once

#include "Export.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <string>

using namespace std;

namespace WaveEngine
{
	WAVEEXPORT class ModelImporter
	{
	private:

		void InitFromScene(const aiScene* pScene, const string_view filepath);

	public:

		WAVEEXPORT void LoadMesh(const string_view filePath);
	};
}