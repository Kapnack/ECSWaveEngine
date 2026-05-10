#include "ModelImporter.h"

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/color4.h>
#include <assimp/mesh.h>

#include "ServiceProvider/ServiceProvider.h"
#include "VertexData.h"
#include "Mesh/Mesh.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Vector2/Vector2.h"

namespace WaveEngine
{
	unsigned int ModelImporter::LoadMesh(string_view assetName, const string_view filePath)
	{
		Assimp::Importer importer;

		const aiScene* pScene = importer.ReadFile(filePath.data(),
			aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs |
			aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);

		return InitFromScene(assetName, pScene);
	}

	unsigned int ModelImporter::InitFromScene(
		string_view assetName,
		const aiScene* pScene)
	{
		pair<int, int> count = GetVertexAndIndexSizes(*pScene);

		VertexData* vertexToSubmit = new VertexData[count.first];
		unsigned int* indicesToSubmit = new unsigned int[count.second];

		unsigned int vertexGlobalOffset = 0;
		unsigned int indexGlobalOffset = 0;

		for (unsigned int i = 0; i < pScene->mNumMeshes; ++i)
		{
			const aiMesh& mesh = *pScene->mMeshes[i];

			for (unsigned int j = 0; j < mesh.mNumVertices; ++j)
			{
				VertexData& currentVertex = vertexToSubmit[vertexGlobalOffset + j];

				currentVertex.position = Vector3(mesh.mVertices[j].x, mesh.mVertices[j].y, mesh.mVertices[j].z);

				currentVertex.normal = mesh.HasNormals()
					? Vector3(mesh.mNormals[j].x, mesh.mNormals[j].y, mesh.mNormals[j].z)
					: Vector3(0, 1, 0);

				currentVertex.textureCordinates = mesh.HasTextureCoords(0)
					? Vector2(mesh.mTextureCoords[0][j].x, mesh.mTextureCoords[0][j].y)
					: Vector2(0, 0);

				if (mesh.HasVertexColors(0)) 
				{
					aiColor4D color = mesh.mColors[0][j];
					currentVertex.color = Color(color.r, color.g, color.b, color.a);
				}
				else 
				{
					currentVertex.color = Color::White();
				}
			}

			for (unsigned int j = 0; j < mesh.mNumFaces; ++j)
			{
				const aiFace& face = mesh.mFaces[j];

				for (unsigned int k = 0; k < face.mNumIndices; ++k)
				{
					indicesToSubmit[indexGlobalOffset++] = face.mIndices[k] + vertexGlobalOffset;
				}
			}

			vertexGlobalOffset += mesh.mNumVertices;
		}

		return GetMeshFactory()->CreateMesh(
			assetName,
			vertexToSubmit,
			count.first,
			indicesToSubmit,
			count.second
		);
	}

	MeshFactory* ModelImporter::GetMeshFactory()
	{
		return ServiceProvider::Instance().Get<MeshFactory>();
	}

	pair<unsigned int, unsigned int> ModelImporter::GetVertexAndIndexSizes(const aiScene& pScene)
	{
		unsigned int totalVertices = 0;
		unsigned int totalIndices = 0;

		for (unsigned int i = 0; i < pScene.mNumMeshes; ++i)
		{
			totalVertices += pScene.mMeshes[i]->mNumVertices;

			for (unsigned int j = 0; j < pScene.mMeshes[i]->mNumFaces; ++j)
				totalIndices += pScene.mMeshes[i]->mFaces[j].mNumIndices;
		}

		return pair<int, int>(totalVertices, totalIndices);
	}
}