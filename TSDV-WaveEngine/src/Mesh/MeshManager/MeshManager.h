#pragma once

#include "ServiceProvider/Service.h"

#include <unordered_map>

#include "Mesh/Mesh.h"
#include <string_view>

using namespace std;

namespace WaveEngine
{
	class MeshFactory;

	class MeshManager : public Service
	{
	private:

		unordered_map<unsigned int, Mesh*> meshByID;

		friend class MeshFactory;

		void SaveMesh(Mesh* mesh, const unsigned& ID);

	public:

		MeshManager();
		~MeshManager();

		Mesh* GetMesh(const unsigned int& ID);
		Mesh* GetMesh(const string_view name);

		unsigned int GetMeshID(const string_view name);

		Mesh& Get(const unsigned int meshID);
	};
}