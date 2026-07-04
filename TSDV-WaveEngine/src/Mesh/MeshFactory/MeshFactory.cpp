#include "MeshFactory.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Mesh/MeshManager/MeshManager.h"
#include "Mesh/Mesh.h"

namespace WaveEngine
{
	MeshFactory::MeshFactory() : Service()
	{
	}

	MeshFactory::~MeshFactory()
	{
	}

	unsigned int MeshFactory::CreateMesh(const string_view name, VertexData* vertexBuffer, const unsigned int& vertexSize, unsigned int* index, const unsigned int& indexSize)
	{
		Mesh* newMesh = new Mesh(vertexBuffer, vertexSize, index, indexSize, name, ++currentMeshID);

		GetMeshManager()->SaveMesh(newMesh);

		return currentMeshID;
	}

	MeshManager* MeshFactory::GetMeshManager()
	{
		return ServiceProvider::Instance().Get<MeshManager>();
	}
}