#pragma once

#include <string>

#include "VertexData.h"

class Mesh
{
private:

	unsigned int ID = NULL_MESH;
	string name;
	VertexData* vertexBuffer = nullptr;
	unsigned int vertexSize = 0;
	unsigned int* indexes = nullptr;
	unsigned int indexAmount = 0;

public:

	static const unsigned int NULL_MESH;

	Mesh(VertexData*& vertexBuffer, const unsigned int& vertexSize, unsigned int*& index, const unsigned int& indexAmount, const string_view name, const unsigned int& ID);
	~Mesh();

	const VertexData* GetVertexBuffer();
	const unsigned int GetVertexSize();
	string GetName();

	const unsigned int* GetIndexes();
	const unsigned int GetIndexesSize();
};