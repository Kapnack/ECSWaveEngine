#pragma once

#include <string>

#include "Export.h"
#include "VertexData.h"
#include "ECS/WObject/WObject.h"
#include "Material/Color/Color.h"
#include "WaveMath/Vector3/Vector3.h"

namespace WaveEngine
{
	class Renderer;
	class MeshFactory;
	class MeshManager;

	class WAVEEXPORT Mesh final : public WObject
	{
	private:

		unsigned int ID = NULL_MESH;
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

		Mesh(VertexData* vertexBuffer, unsigned int vertexSize, unsigned int* index, unsigned int indexAmount, const string_view name, unsigned int meshID);
		~Mesh();

		friend class Renderer;
		friend class MeshFactory;
		friend class MeshManager;

	public:

		static const unsigned int NULL_MESH;

		unsigned int GetID();
		const VertexData* GetVertexBuffer() const;
		unsigned int GetVertexSize() const;
		string GetName();

		void SetVertexColor(Color color);

		Vector3 GetMin() const;
		Vector3 GetMax() const;
		Vector3 GetCenter() const;
		Vector3 GetSize() const;
		Vector3 GetExtends() const;

		const unsigned int* GetIndexes() const;
		unsigned int GetIndexesSize() const;
	};
}