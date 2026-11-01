#pragma once

#include <set>
#include <string>
#include <string_view>
#include <unordered_map>

#include "ServiceProvider/Service.h"
#include "Mesh/Mesh.h"

using namespace std;

namespace WaveEngine
{
	class Engine;
	class MeshFactory;

	class MeshManager : public Service
	{
	private:

		unordered_map<unsigned int, Mesh*> meshByID;
		unordered_map<string, unsigned int> idByName;
		set<unsigned int> meshToDestroy;

		friend class Engine;
		friend class MeshFactory;

		void Update();

		void SaveMesh(Mesh* mesh);

	public:

		MeshManager();
		~MeshManager();

		Mesh* GetMesh(const unsigned int ID);
		Mesh* GetMesh(const char* name);
		bool Has(const char* name);
		unsigned int GetMeshID(const const char* name);

		Mesh& Get(const unsigned int meshID);

		void Destroy(Mesh& mesh);
		void Destroy(unsigned int meshID);

		void DestroyImmediate(Mesh& mesh);
		void DestroyImmediate(unsigned int meshID);
	};
}