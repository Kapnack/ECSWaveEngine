#include "MeshFactory.h"

#include "Mesh/Mesh.h"
#include "ServiceProvider/Service.h"
#include "WaveMath/Vector3/Vector3.h"
#include "Mesh/MeshManager/MeshManager.h"
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
		Mesh* newMesh = new Mesh(vertexBuffer, vertexSize, index, indexSize, name, ++currentMeshID);

		CalculateMinMaxVertex(*newMesh);

		GetMeshManager()->SaveMesh(newMesh);

		return currentMeshID;
	}

	void MeshFactory::CalculateMinMaxVertex(Mesh& newMesh) const
	{
		VertexData currentVertex;

		Vector3 min = Vector3::Max();
		Vector3 max = Vector3::NMax();

		for (int i = 0; i < newMesh.GetVertexSize(); i++)
		{
			currentVertex = newMesh.GetVertexBuffer()[i];

			if (min.x > currentVertex.position.x)
				min.x = currentVertex.position.x;

			if (max.x < currentVertex.position.x)
				max.x = currentVertex.position.x;

			if (min.y > currentVertex.position.y)
				min.y = currentVertex.position.y;

			if (max.y < currentVertex.position.y)
				max.y = currentVertex.position.y;

			if (min.z > currentVertex.position.z)
				min.z = currentVertex.position.z;

			if (max.z < currentVertex.position.z)
				max.z = currentVertex.position.z;
		}

		newMesh.min = min;
		newMesh.max = max;
	}

	MeshManager* MeshFactory::GetMeshManager()
	{
		return ServiceProvider::Instance().Get<MeshManager>();
	}
}