#include "Mesh.h"

namespace WaveEngine
{
	const unsigned int Mesh::NULL_MESH = 0;

	bool Mesh::GetDirty() const
	{
		return isDirty;
	}

	Mesh::Mesh(VertexData* vertexBuffer, unsigned int vertexSize, unsigned int* indexes, unsigned int indexAmount, string_view name, unsigned int meshID)
	{
		this->name = name;
		this->vertexBuffer = vertexBuffer;
		this->vertexSize = vertexSize;
		this->indexes = indexes;
		this->indexAmount = indexAmount;
		this->id = meshID;
	}

	Mesh::~Mesh()
	{
	}

	unsigned int Mesh::GetID()
	{
		return id;
	}

	const VertexData* Mesh::GetVertexBuffer() const
	{
		return vertexBuffer;
	}

	unsigned int Mesh::GetVertexSize() const
	{
		return vertexSize;
	}

	string Mesh::GetName()
	{
		return name;
	}

	void Mesh::SetVertexColor(Color color)
	{
		for (unsigned i = 0; i < vertexSize; ++i)
			vertexBuffer[i].color = color;

		isDirty = true;
	}

	void Mesh::UnDirt()
	{
		isDirty = false;
	}

	const unsigned int* Mesh::GetIndexes() const
	{
		return indexes;
	}

	unsigned int Mesh::GetIndexesSize() const
	{
		return indexAmount;
	}
}