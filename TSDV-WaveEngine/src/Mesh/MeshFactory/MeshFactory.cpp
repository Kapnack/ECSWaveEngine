#include "MeshFactory.h"

#include "Mesh/Mesh.h"
#include "ServiceProvider/Service.h"
#include "WaveMath/Vector3/Vector3.h"
#include "Mesh/MeshManager/MeshManager.h"
#include "ServiceProvider/ServiceProvider.h"
#include <cfloat>

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

		int minXIndex = 0;
		float minX = FLT_MAX;

		int maxXIndex = 0;
		float maxX = -FLT_MAX;

		int minYIndex = 0;
		float minY = FLT_MAX;

		int maxYIndex = 0;
		float maxY = -FLT_MAX;

		int minZIndex = 0;
		float minZ = FLT_MAX;

		int maxZIndex = 0;
		float maxZ = -FLT_MAX;

		for (int i = 0; i < newMesh.GetVertexSize(); i++)
		{
			currentVertex = newMesh.GetVertexBuffer()[i];

			if (minX > currentVertex.position.x)
			{
				minXIndex = i;
				minX = currentVertex.position.x;
			}

			if (maxX < currentVertex.position.x)
			{
				maxXIndex = i;
				maxX = currentVertex.position.x;
			}

			if (minY > currentVertex.position.y)
			{
				minYIndex = i;
				minY = currentVertex.position.y;
			}

			if (maxY < currentVertex.position.y)
			{
				maxYIndex = i;
				maxY = currentVertex.position.y;
			}

			if (minZ > currentVertex.position.z)
			{
				minZIndex = i;
				minZ = currentVertex.position.z;
			}

			if (maxZ < currentVertex.position.z)
			{
				maxZIndex = i;
				maxZ = currentVertex.position.z;
			}
		}

		newMesh.min = Vector3(minX, minY, minZ);
		newMesh.max = Vector3(maxX, maxY, maxZ);
	}

	MeshManager* MeshFactory::GetMeshManager()
	{
		return ServiceProvider::Instance().Get<MeshManager>();
	}
}