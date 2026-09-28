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

		Vector3 min;
		Vector3 max;

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

		Vector3 GetMin() const;
		Vector3 GetMax() const;

		const unsigned int* GetIndexes() const;
		unsigned int GetIndexesSize() const;
	};
}