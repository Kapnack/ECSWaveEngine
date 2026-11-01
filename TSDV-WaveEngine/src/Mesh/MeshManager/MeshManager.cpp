#include "MeshManager.h"

#include "Mesh/Mesh.h"
#include "ServiceProvider/Service.h"

namespace WaveEngine
{
	MeshManager::MeshManager() : Service()
	{
	}

	MeshManager::~MeshManager()
	{
		for (auto& [ID, mesh] : meshByID)
			delete mesh;
	}

	void MeshManager::Update()
	{
		for (unsigned int meshID : meshToDestroy)
			DestroyImmediate(meshID);

		meshToDestroy.clear();
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

	void MeshManager::Destroy(Mesh& mesh)
	{
		Destroy(mesh.ID);
	}

	void MeshManager::Destroy(unsigned int meshID)
	{
		meshToDestroy.insert(meshID);
	}

	void MeshManager::DestroyImmediate(Mesh& mesh)
	{
		DestroyImmediate(mesh.ID);
	}

	void MeshManager::DestroyImmediate(unsigned int meshID)
	{
		delete meshByID[meshID];
		meshByID.erase(meshID);
	}
}