#pragma once

#include <string>

#include "VertexData.h"

namespace WaveEngine
{
	class Renderer;
	class MeshFactory;

	class Mesh
	{
	private:

		unsigned int id = NULL_MESH;
		string name;
		VertexData* vertexBuffer = nullptr;
		unsigned int vertexSize = 0;
		unsigned int* indexes = nullptr;
		unsigned int indexAmount = 0;

		int minXVertexIndex;
		int maxXVertexIndex;

		int minYVertexIndex;
		int maxYVertexIndex;

		int minZVertexIndex;
		int maxZVertexIndex;

		bool isDirty = false;

		bool GetDirty() const;
		void UnDirt();

		friend class Renderer;
		friend class MeshFactory;

	public:

		static const unsigned int NULL_MESH;

		Mesh(VertexData* vertexBuffer, unsigned int vertexSize, unsigned int* index, unsigned int indexAmount, const string_view name, unsigned int meshID);
		~Mesh();

		unsigned int GetID();
		const VertexData* GetVertexBuffer() const;
		unsigned int GetVertexSize() const;
		string GetName();

		void SetVertexColor(Color color);

		VertexData GetXMinVertex() const;
		VertexData GetXMaxVertex() const;

		VertexData GetYMinVertex() const;
		VertexData GetYMaxVertex() const;

		VertexData GetZMinVertex() const;
		VertexData GetZMaxVertex() const;

		const unsigned int* GetIndexes() const;
		unsigned int GetIndexesSize() const;
	};
}