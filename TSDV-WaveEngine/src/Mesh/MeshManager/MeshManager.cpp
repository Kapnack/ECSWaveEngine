#include "MeshManager.h"
#include "Mesh/Mesh.h"

namespace WaveEngine
{
	MeshManager::MeshManager() : Service()
	{
	}

	MeshManager::~MeshManager()
	{
		for (auto& [id, mesh] : meshByID)
			delete mesh;
	}

	void MeshManager::SaveMesh(Mesh* mesh)
	{
		meshByID[mesh->GetID()] = mesh;
		idByName[mesh->GetName()] = mesh->GetID();
	}

	Mesh* MeshManager::GetMesh(const unsigned int ID)
	{
		return meshByID.at(ID);
	}

	Mesh* MeshManager::GetMesh(const char* name)
	{
		return meshByID.at(GetMeshID(name));
	}

	bool MeshManager::Has(const char* name)
	{
		return idByName.contains(name);
	}

	unsigned int MeshManager::GetMeshID(const char* name)
	{
		return idByName.at(name);
	}

	Mesh& MeshManager::Get(const unsigned int meshID)
	{
		return *meshByID.at(meshID);
	}
}