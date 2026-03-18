#include "MeshFactory.h"

#include "ServiceProvider/ServiceProvider.h"

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
		++currentMeshID;

		Mesh* newMesh = new Mesh(vertexBuffer, vertexSize, index, indexSize, name, currentMeshID);

		GetMeshManager()->SaveMesh(newMesh, currentMeshID);

		return currentMeshID;
	}

	MeshManager* MeshFactory::GetMeshManager()
	{
		return ServiceProvider::Instance().Get<MeshManager>();
	}
}