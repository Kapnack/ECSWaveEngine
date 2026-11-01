#pragma once

#include "ServiceProvider/Service.h"

#include <set>
#include <string>
#include <string_view>
#include <unordered_map>

#include "Export.h"
#include "Material/Material.h"

using namespace std;

namespace WaveEngine
{
	class Engine;
	class Renderer;
	class ImGuiClass;
	class EntityManager;
	class MaterialFactory;

	class WAVEEXPORT MaterialManager final : public Service
	{
	private:

		unsigned int currentMaterialID = WObject::NULL_OBJECT;

		set<unsigned int> materialsToDestroy;
		unordered_map<unsigned int, Material*> materials;
		unordered_map<string, unsigned int> materialsIDByName;

		void SaveMaterial(Material*& material);

		void Update();

		MaterialManager();
		~MaterialManager();

		friend class Engine;
		friend class Renderer;
		friend class ImGuiClass;
		friend class EntityManager;
		friend class MaterialFactory;
		friend class ServiceProvider;

	public:

		Material* GetMaterial(const unsigned int id);

		unsigned int GetMaterial(const string_view name);

		void Destroy(Material& material);
		void Destroy(unsigned int ID);
		void DestroyImmediate(Material& material);
		void DestroyImmediate(unsigned int ID);

		unordered_map<unsigned int, Material*>& GetMaterials();
	};
}

