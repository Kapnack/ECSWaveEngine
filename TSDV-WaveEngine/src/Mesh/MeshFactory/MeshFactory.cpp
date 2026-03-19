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
		Mesh* newMesh = new Mesh(vertexBuffer, vertexSize, index, indexSize, name);

		return GetMeshManager()->SaveMesh(newMesh);
	}

	MeshManager* MeshFactory::GetMeshManager()
	{
		return ServiceProvider::Instance().Get<MeshManager>();
	}
}