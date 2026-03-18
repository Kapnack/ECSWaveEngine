#pragma once

#include "ServiceProvider/Service.h"

#include "Mesh/Mesh.h"

#include "VertexData.h"

#include "Mesh/MeshManager/MeshManager.h"

namespace WaveEngine
{
	class MeshFactory : public Service
	{
	private:

		unsigned int currentMeshID = Mesh::NULL_MESH;

		MeshManager* GetMeshManager();

	public:

		MeshFactory();
		~MeshFactory();

		unsigned int CreateMesh(const string_view name, VertexData* vertexBuffer, const unsigned int& vertexSize, unsigned int* index, const unsigned int& indexSize);
	};
}