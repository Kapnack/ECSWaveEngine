#pragma once

#include <string_view>
#include <unordered_map>
#include <string>

#include "ServiceProvider/Service.h"
#include "Mesh/Mesh.h"

using namespace std;

namespace WaveEngine
{
	class MeshFactory;

	class MeshManager : public Service
	{
	private:

		unordered_map<unsigned int, Mesh*> meshByID;
		unordered_map<string, unsigned int> idByName;

		friend class MeshFactory;

		void SaveMesh(Mesh* mesh);

	public:

		MeshManager();
		~MeshManager();

		Mesh* GetMesh(const unsigned int ID);
		Mesh* GetMesh(const string_view name);

		unsigned int GetMeshID(const string_view name);

		Mesh& Get(const unsigned int meshID);
	};
}