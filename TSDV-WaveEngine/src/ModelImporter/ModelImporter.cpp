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
#include <Material/Material.h>

namespace WaveEngine
{
	void ModelImporter::LoadScene(filesystem::path filePath, const bool useAbsolutePath)
	{
		filePath = useAbsolutePath ? std::filesystem::absolute(filePath) : filePath;

		directory = filePath.parent_path();

		pScene = importer.ReadFile(filePath.string().c_str(),
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_FlipUVs |
			aiProcess_JoinIdenticalVertices |
			aiProcess_CalcTangentSpace);

		filename = filePath.filename().string().c_str();
	}

	unsigned int ModelImporter::LoadMesh()
	{
		if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
			return Mesh::NULL_MESH;

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

				if (mesh.GetNumUVChannels() > 0 &&
					mesh.mTextureCoords[0] != nullptr)
				{
					const aiVector3D& uv = mesh.mTextureCoords[0][j];
					currentVertex.textureCordinates = Vector2(uv.x, uv.y);
				}
				else
					currentVertex.textureCordinates = Vector2(0, 0);
				

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
					indicesToSubmit[indexGlobalOffset++] = face.mIndices[k] + vertexGlobalOffset;

			}

			vertexGlobalOffset += mesh.mNumVertices;
		}

		return GetMeshFactory()->CreateMesh(
			filename,
			vertexToSubmit,
			count.first,
			indicesToSubmit,
			count.second
		);
	}

	unsigned int ModelImporter::LoadMaterial()
	{
		if (!pScene || !pScene->HasMaterials())
			return Material::NULL_MATERIAL;

		aiMaterial* material = pScene->mMaterials[0];

		std::vector<unsigned int> albedoIDs = LoadMaterialTextures(material, aiTextureType_DIFFUSE);

		if (albedoIDs.empty())
			return Material::NULL_MATERIAL;

		const unsigned int newMaterialID = GetMaterialFactory()->CreateMaterial(
			filename,
			GetFileReader()->ReadFile("Shaders/ECS/newShader.vert"),
			GetFileReader()->ReadFile("Shaders/ECS/newShader.frag")
		);

		Material* newMaterial = GetMaterialManager()->GetMaterial(newMaterialID);

		for (size_t i = 0; i < albedoIDs.size() && i < Material::MAX_ALBEDO; ++i)
			newMaterial->AddAlbedoTexture(albedoIDs[i]);

		return newMaterialID;
	}

	std::vector<unsigned int> ModelImporter::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
	{
		std::vector<unsigned int> textures;
		unsigned int count = mat->GetTextureCount(type);

		for (unsigned int i = 0; i < count; i++)
		{
			aiString str;
			if (mat->GetTexture(type, i, &str) != AI_SUCCESS)
				continue;

			std::string path = str.C_Str();

			unsigned int textureID = 0;

			if (!path.empty() && path[0] == '*')
			{
				int index = std::stoi(path.substr(1));
				const aiTexture* tex = pScene->mTextures[index];

				if (tex->mHeight == 0)
				{
					textureID = GetTextureImporter()->LoadTextureFromMemory(
						reinterpret_cast<const unsigned char*>(tex->pcData),
						tex->mWidth);
				}
			}
			else
			{
				std::filesystem::path fullPath = directory / path;
				textureID = GetTextureImporter()->LoadTexture(fullPath.string());
			}

			if (textureID != 0)
			{
				unsigned int gpuID = GetTextureManager()->GetTexture(textureID)->GetGPUID();
				textures.push_back(gpuID);
			}
		}
		return textures;
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

	MeshFactory* ModelImporter::GetMeshFactory()
	{
		return ServiceProvider::Instance().Get<MeshFactory>();
	}

	TextureImporter* ModelImporter::GetTextureImporter()
	{
		return ServiceProvider::Instance().Get<TextureImporter>();
	}

	TextureManager* ModelImporter::GetTextureManager()
	{
		return ServiceProvider::Instance().Get<TextureManager>();
	}

	MaterialFactory* ModelImporter::GetMaterialFactory()
	{
		return ServiceProvider::Instance().Get<MaterialFactory>();
	}

	MaterialManager* ModelImporter::GetMaterialManager()
	{
		return ServiceProvider::Instance().Get<MaterialManager>();
	}

	FileReader* ModelImporter::GetFileReader()
	{
		return ServiceProvider::Instance().Get<FileReader>();
	}
}