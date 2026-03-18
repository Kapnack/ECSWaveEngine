#include "Mesh.h"

const unsigned int Mesh::NULL_MESH = 0;

Mesh::Mesh(VertexData*& vertexBuffer, const unsigned int& vertexSize, unsigned int*& indexes, const unsigned int& indexAmount, const string_view name, const unsigned int& ID)
{
	this->ID = ID;
	this->name = name;
	this->vertexBuffer = vertexBuffer;
	this->vertexSize = vertexSize;
	this->indexes = indexes;
	this->indexAmount = indexAmount;
}

Mesh::~Mesh()
{
}

const VertexData* Mesh::GetVertexBuffer()
{
	return vertexBuffer;
}

const unsigned int Mesh::GetVertexSize()
{
	return vertexSize;
}

string Mesh::GetName()
{
	return name;
}

const unsigned int* Mesh::GetIndexes()
{
	return indexes;
}

const unsigned int Mesh::GetIndexesSize()
{
	return indexAmount;
}
