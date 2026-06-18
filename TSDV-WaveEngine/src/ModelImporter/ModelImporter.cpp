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
#include <ECS/MaterialID.h>
#include <ECS/Mesh/MeshID.h>
#include "ECS/Transform/ECSTransform.h"
#include <glm/gtc/quaternion.hpp>

namespace WaveEngine
{
	void ModelImporter::LoadScene(filesystem::path filePath, const bool useAbsolutePath)
	{
		filePath = useAbsolutePath ? std::filesystem::absolute(filePath) : filePath;

		directory = filePath.parent_path();

		pScene = importer.ReadFile(filePath.string().c_str(),
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_JoinIdenticalVertices |
			aiProcess_CalcTangentSpace |
			aiProcess_CalcTangentSpace);

		filename = filePath.filename().string().c_str();
	}

	WaveObject* ModelImporter::IntantiateModel()
	{
		if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
			return nullptr;

		WaveObject& root = GetWaveObjectFactory()->Instantiate();
		root.SetName(filename);

		ProcessNode(pScene->mRootNode, root);

		return &root;
	}

	void ModelImporter::ProcessNode(aiNode* node, WaveObject& waveObject)
	{
		std::cout << "Node: " << node->mName.C_Str()
			<< " | Meshes: " << node->mNumMeshes
			<< " | Children: " << node->mNumChildren
			<< std::endl;

		ApplyNodeTransform(waveObject.GetTransform(), node);

		for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = pScene->mMeshes[node->mMeshes[i]];

			waveObject.SetName(mesh->mName.C_Str());

			ProcessMesh(mesh, waveObject);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			WaveObject& childObject = GetWaveObjectFactory()->Instantiate();

			waveObject.GetTransform().AddChild(childObject.GetID());
			childObject.GetTransform().SetParent(waveObject.GetID());

			ProcessNode(node->mChildren[i], childObject);
		}
	}

	//void ModelImporter::ProcessNode(aiNode* node, WaveObject& waveObject)
	//{
	//	std::cout << "Node: " << node->mName.C_Str()
	//		<< " | Meshes: " << node->mNumMeshes
	//		<< " | Children: " << node->mNumChildren
	//		<< std::endl;
	//
	//	ApplyNodeTransform(waveObject.GetTransform(), node);
	//
	//	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	//	{
	//		aiMesh* mesh = pScene->mMeshes[node->mMeshes[i]];
	//
	//		WaveObject& meshObject = GetWaveObjectFactory()->Instantiate();
	//
	//		meshObject.SetName(mesh->mName.C_Str());
	//
	//		waveObject.GetTransform().AddChild(meshObject.GetID());
	//		meshObject.GetTransform().SetParent(waveObject.GetID());
	//
	//		ProcessMesh(mesh, meshObject);
	//	}
	//
	//	for (unsigned int i = 0; i < node->mNumChildren; i++)
	//	{
	//		WaveObject& childObject = GetWaveObjectFactory()->Instantiate();
	//
	//		waveObject.GetTransform().AddChild(childObject.GetID());
	//		childObject.GetTransform().SetParent(waveObject.GetID());
	//
	//		ProcessNode(node->mChildren[i], childObject);
	//	}
	//}

	void ModelImporter::ProcessMesh(aiMesh* mesh, WaveObject& meshWaveObject)
	{
		VertexData* vertices = new VertexData[mesh->mNumVertices];
		std::vector<unsigned int> indices;

		VertexData vertexData;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			vertexData.position = Vector3(
				mesh->mVertices[i].x,
				mesh->mVertices[i].y,
				mesh->mVertices[i].z
			);

			if (mesh->HasNormals())
			{
				vertexData.normal = Vector3(
					mesh->mNormals[i].x,
					mesh->mNormals[i].y,
					mesh->mNormals[i].z
				);
			}
			else
				vertexData.normal = Vector3::Up();

			if (mesh->mTextureCoords[0])
			{
				vertexData.textureCordinates = Vector2(
					mesh->mTextureCoords[0][i].x,
					mesh->mTextureCoords[0][i].y
				);
			}
			else
				vertexData.textureCordinates = Vector2::Zero();

			if (mesh->HasVertexColors(0))
			{
				aiColor4D color = mesh->mColors[0][i];
				vertexData.color = Color(color.r, color.g, color.b, color.a);
			}
			else
				vertexData.color = Color::White();

			vertexData.tangent =
			{
				mesh->mTangents[i].x,
				mesh->mTangents[i].y,
				mesh->mTangents[i].z
			};

			vertices[i] = vertexData;
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			const aiFace& face = mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		unsigned int* indexBuffer = new unsigned int[indices.size()];
		for (unsigned int i = 0; i < indices.size(); ++i)
			indexBuffer[i] = indices[i];

		unsigned int meshID = GetMeshFactory()->CreateMesh(
			filename,
			vertices,
			mesh->mNumVertices,
			indexBuffer,
			indices.size()
		);

		meshWaveObject.AddComponent<MeshID>().meshID = meshID;

		aiMaterial* material = pScene->mMaterials[mesh->mMaterialIndex];

		unsigned int materialID = ProcessMaterial(material);

		meshWaveObject.AddComponent<MeshRenderer>().materialID = materialID;
	}

	unsigned int ModelImporter::ProcessMaterial(aiMaterial* mat)
	{
		if (!mat)
			return Material::NULL_MATERIAL;

		unsigned int albedoIDs = LoadMaterialTextures(mat, aiTextureType_DIFFUSE);
		unsigned int roughnessMap = LoadMaterialTextures(mat, aiTextureType_DIFFUSE_ROUGHNESS);
		unsigned int normalMap = LoadMaterialTextures(mat, aiTextureType_NORMALS);
		unsigned int metallicMap = LoadMaterialTextures(mat, aiTextureType_METALNESS);
		unsigned int aoMap = LoadMaterialTextures(mat, aiTextureType_LIGHTMAP);
		unsigned int emissiveMap = LoadMaterialTextures(mat, aiTextureType_EMISSIVE);
		unsigned int heightMap = LoadMaterialTextures(mat, aiTextureType_HEIGHT);

		unsigned int materialID = GetMaterialFactory()->CreateMaterial(
			"ImportedMaterial",
			GetFileReader()->ReadFile("Shaders/ECS/newShader.vert"),
			GetFileReader()->ReadFile("Shaders/ECS/newShader.frag")
		);

		Material* newMaterial = GetMaterialManager()->GetMaterial(materialID);

		aiColor4D diffuseColor(1, 1, 1, 1);

		if (AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor))
		{
			newMaterial->SetColor(Color(
				diffuseColor.r,
				diffuseColor.g,
				diffuseColor.b,
				diffuseColor.a
			));
		}

		float roughnessFactor = 0.0f;
		if (mat->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughnessFactor) == AI_SUCCESS)
			newMaterial->SetRoughness(roughnessFactor);

		float metallicFactor = 0.0f;
		if (mat->Get(AI_MATKEY_METALLIC_FACTOR, metallicFactor) == AI_SUCCESS)
			newMaterial->SetMetallic(metallicFactor);

		if (albedoIDs)
			newMaterial->AddAlbedoTexture(albedoIDs);

		if (normalMap)
			newMaterial->SetTexture("uNormalMap", normalMap);

		if (roughnessMap)
			newMaterial->SetTexture("uRoughnessMap", roughnessMap);

		if (metallicMap)
			newMaterial->SetTexture("uMetallicMap", metallicMap);

		if (aoMap)
			newMaterial->SetTexture("uAOMap", aoMap);

		if (emissiveMap)
			newMaterial->SetTexture("uEmissiveMap", emissiveMap);

		return materialID;
	}

	void ModelImporter::ApplyNodeTransform(ECSTransform& transform, const aiNode* node)
	{
		aiVector3D pos, scale;
		aiQuaternion aiQuat;

		node->mTransformation.Decompose(scale, aiQuat, pos);

		transform.SetPosition(pos.x, pos.y, pos.z);
		transform.SetScale(scale.x, scale.y, scale.z);

		glm::quat glmQuat = glm::quat(aiQuat.w, aiQuat.x, aiQuat.y, aiQuat.z);
		glm::vec3 euler = glm::degrees(glm::eulerAngles(glmQuat));

		transform.SetRotation(euler.x, euler.y, euler.z);
	}

	std::filesystem::path ModelImporter::FindTexture(const std::filesystem::path& modelDirectory, const std::string& textureName)
	{
		// Strip to just the filename in case Assimp gave a relative path
		std::string filename = std::filesystem::path(textureName).filename().string();

		for (auto& entry : std::filesystem::recursive_directory_iterator(modelDirectory))
		{
			if (!entry.is_regular_file())
				continue;

			if (entry.path().filename().string() == filename)
				return entry.path();
		}

		return {}; // not found
	}

	unsigned int ModelImporter::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
	{
		unsigned int textureGPUID = 0;
		unsigned int count = mat->GetTextureCount(type);
		int index = 0;
		unsigned int textureID = 0;
		aiString str;
		string path;

		for (unsigned int i = 0; i < count; ++i)
		{
			if (mat->GetTexture(type, i, &str) != AI_SUCCESS)
				continue;

			path = str.C_Str();

			textureID = 0;

			if (!path.empty() && path[0] == '*')
			{
				index = stoi(path.substr(1));
				const aiTexture& tex = *pScene->mTextures[index];

				if (tex.mHeight == 0)
				{
					// Compressed (PNG, JPG, etc.)
					textureID = GetTextureImporter()->LoadTextureFromMemory(
						reinterpret_cast<const unsigned char*>(tex.pcData),
						tex.mWidth);
				}
				else
				{
					// Raw ARGB8888 pixels
					textureID = GetTextureImporter()->LoadTextureFromPixels(
						reinterpret_cast<const unsigned char*>(tex.pcData),
						tex.mWidth,
						tex.mHeight);
				}
			}
			else
			{
				std::filesystem::path fullPath = directory / path;

				// If the direct path doesn't exist, search recursively
				if (!std::filesystem::exists(fullPath))
					fullPath = FindTexture(directory, path);

				if (!fullPath.empty())
					textureID = GetTextureImporter()->LoadTexture(fullPath.string());
			}

			if (textureID != Texture::NULL_TEXTURE)
				textureGPUID = GetTextureManager()->GetTexture(textureID)->GetGPUID();
		}

		return textureGPUID;
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

	WaveObjectRegistry* ModelImporter::GetWaveObjectRegistry()
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
	}

	WaveObjectFactory* ModelImporter::GetWaveObjectFactory()
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>();
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