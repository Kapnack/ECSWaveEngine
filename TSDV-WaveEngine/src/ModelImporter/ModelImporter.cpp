#include "ModelImporter.h"

namespace WaveEngine
{
	void ModelImporter::LoadMesh(const string_view filePath)
	{
		Assimp::Importer importer;

		const aiScene* pScene = importer.ReadFile(filePath.data(),
			aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs |
			aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);

		InitFromScene(pScene, filePath);
	}

	void ModelImporter::InitFromScene(const aiScene* pScene, const string_view filepath)
	{
	}
}