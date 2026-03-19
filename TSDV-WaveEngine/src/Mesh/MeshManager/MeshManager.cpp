#include "MeshManager.h"

namespace WaveEngine
{
	MeshManager::MeshManager() : Service()
	{
	}

	MeshManager::~MeshManager()
	{
		for (Mesh* mesh : meshByID)
			delete mesh;
	}

	const unsigned int MeshManager::SaveMesh(Mesh* mesh)
	{
		const unsigned int currentIndex = meshByID.size();
		idByName[mesh->GetName()] = currentIndex;
		meshByID.push_back(mesh);

		return currentIndex;
	}

	Mesh* MeshManager::GetMesh(const unsigned int& ID)
	{
		return meshByID.at(ID);
	}

	Mesh* MeshManager::GetMesh(const string_view name)
	{
		return meshByID.at(idByName.at(string(name)));
	}

	unsigned int MeshManager::GetMeshID(const string_view name)
	{
		return idByName.at(string(name));
	}

	Mesh& MeshManager::Get(const unsigned int meshID)
	{
		return *meshByID.at(meshID);
	}
}