#include "MeshManager.h"

namespace WaveEngine
{
	MeshManager::MeshManager() : Service()
	{
	}

	MeshManager::~MeshManager()
	{
	}

	void MeshManager::SaveMesh(Mesh* mesh, const unsigned& ID)
	{
		meshByID[ID] = mesh;
	}

	Mesh* MeshManager::GetMesh(const unsigned int& ID)
	{
		return meshByID.at(ID);
	}

	Mesh* MeshManager::GetMesh(const string_view name)
	{
		unordered_map<unsigned int, Mesh*>::iterator it = find_if(meshByID.begin(), meshByID.end(),
			[&name](const pair<const unsigned int, Mesh*>& it)
			{
				return it.second && it.second->GetName() == name;
			});

		if (it == meshByID.end())
			return nullptr;

		return it->second;
	}

	unsigned int MeshManager::GetMeshID(const string_view name)
	{
		unordered_map<unsigned int, Mesh*>::iterator it = find_if(meshByID.begin(), meshByID.end(),
			[&name](const pair<const unsigned int, Mesh*>& it)
			{
				return it.second && it.second->GetName() == name;
			});

		if (it == meshByID.end())
			return Mesh::NULL_MESH;

		return it->first;
	}

	Mesh& MeshManager::Get(const unsigned int meshID)
	{
		return *meshByID.at(meshID);
	}
}