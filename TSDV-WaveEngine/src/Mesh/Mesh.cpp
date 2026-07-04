#include "Mesh.h"

namespace WaveEngine
{
	const unsigned int Mesh::NULL_MESH = 0;

	const bool Mesh::GetDirty() const
	{
		return isDirty;
	}

	Mesh::Mesh(VertexData* vertexBuffer, const unsigned int vertexSize, unsigned int* indexes, const unsigned int indexAmount, const string_view name, const unsigned int meshID)
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

	const unsigned int Mesh::GetVertexSize() const
	{
		return vertexSize;
	}

	string Mesh::GetName()
	{
		return name;
	}

	void Mesh::SetVertexColor(const Color& color)
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

	const unsigned int Mesh::GetIndexesSize() const
	{
		return indexAmount;
	}
}