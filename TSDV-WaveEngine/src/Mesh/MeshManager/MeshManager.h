#pragma once

#include <string_view>
#include <vector>
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

		vector<Mesh*> meshByID;
		unordered_map<string, unsigned int> idByName;

		friend class MeshFactory;

		const unsigned int SaveMesh(Mesh* mesh);

	public:

		MeshManager();
		~MeshManager();

		Mesh* GetMesh(const unsigned int& ID);
		Mesh* GetMesh(const string_view name);

		unsigned int GetMeshID(const string_view name);

		vector<Mesh*>& GetMeshes();

		Mesh& Get(const unsigned int meshID);
	};
}