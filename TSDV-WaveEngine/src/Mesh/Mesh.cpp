#include "Mesh.h"

#include <string>

#include "VertexData.h"
#include "ECS/WObject/WObject.h"
#include "Material/Color/Color.h"
#include "WaveMath/Vector3/Vector3.h"

namespace WaveEngine
{

	bool Mesh::GetDirty() const
	{
		return isDirty;
	}

	Mesh::Mesh(VertexData* vertexBuffer, unsigned int vertexSize, unsigned int* indexes, unsigned int indexAmount, string_view name) : WObject()
	{
		this->name = name;
		this->vertexBuffer = vertexBuffer;
		this->vertexSize = vertexSize;
		this->indexes = indexes;
		this->indexAmount = indexAmount;
	}

	Mesh::~Mesh()
	{
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

	Vector3 Mesh::GetMin() const
	{
		return min;
	}

	Vector3 Mesh::GetMax() const
	{
		return max;
	}

	Vector3 Mesh::GetCenter() const
	{
		return (max + min) * 0.5f;
	}

	Vector3 Mesh::GetSize() const
	{
		return max - min;
	}

	Vector3 Mesh::GetExtends() const
	{
		return GetSize() * 0.5f;
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