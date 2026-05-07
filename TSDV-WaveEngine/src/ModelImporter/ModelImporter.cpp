#include "ModelImporter.h"
#include <Mesh/Mesh.h>
#include <ServiceProvider/ServiceProvider.h>

namespace WaveEngine
{
	unsigned int ModelImporter::LoadMesh(string_view assetName, const string_view filePath)
	{
		Assimp::Importer importer;

		const aiScene* pScene = importer.ReadFile(filePath.data(),
			aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs |
			aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);

		return InitFromScene(assetName, pScene, filePath);
	}

    unsigned int ModelImporter::InitFromScene(
        string_view assetName,
        const aiScene* pScene,
        const string_view filepath)
    {
        vector<VertexData> vertices;
        vector<unsigned int> indices;

        unsigned int vertexOffset = 0;

        for (unsigned int i = 0; i < pScene->mNumMeshes; ++i)
        {
            const aiMesh* mesh = pScene->mMeshes[i];

            for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
            {
                VertexData vertex{};

                vertex.position = Vector3(
                    mesh->mVertices[j].x,
                    mesh->mVertices[j].y,
                    mesh->mVertices[j].z
                );

                if (mesh->HasNormals())
                {
                    vertex.normal = Vector3(
                        mesh->mNormals[j].x,
                        mesh->mNormals[j].y,
                        mesh->mNormals[j].z
                    );
                }
                else
                {
                    vertex.normal = Vector3(0, 1, 0);
                }

                if (mesh->HasTextureCoords(0))
                {
                    vertex.textureCordinates = Vector2(
                        mesh->mTextureCoords[0][j].x,
                        mesh->mTextureCoords[0][j].y
                    );
                }
                else
                {
                    vertex.textureCordinates = Vector2(0, 0);
                }

                if (mesh->HasVertexColors(0))
                {
                    aiColor4D color = mesh->mColors[0][j];

                    vertex.color = Vector4(
                        color.r,
                        color.g,
                        color.b,
                        color.a
                    );
                }
                else
                {
                    vertex.color = Vector4(1, 1, 1, 1);
                }

                vertices.push_back(vertex);
            }

            for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
            {
                const aiFace& face = mesh->mFaces[j];

                for (unsigned int k = 0; k < face.mNumIndices; ++k)
                {
                    indices.push_back(
                        face.mIndices[k] + vertexOffset
                    );
                }
            }

            vertexOffset += mesh->mNumVertices;
        }

        VertexData* vertexToSubmit = new VertexData[vertices.size()];
        unsigned int* indicesToSubmit = new unsigned int[indices.size()];

        for (int j = 0; j < vertices.size(); ++j)
            vertexToSubmit[j] = vertices[j];
        
        for (int j = 0; j < indices.size(); ++j)
            indicesToSubmit[j] = indices[j];

        return GetMeshFactory()->CreateMesh(
            assetName,
            vertexToSubmit,
            vertices.size(),
            indicesToSubmit,
            indices.size()
        );
    }

	MeshFactory* ModelImporter::GetMeshFactory()
	{
		return ServiceProvider::Instance().Get<MeshFactory>();
	}
}