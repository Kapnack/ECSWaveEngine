#pragma once

#include "ServiceProvider/Service.h"

#include <string>
#include <string_view>
#include <unordered_map>

#include "Export.h"
#include "Material/Material.h"

using namespace std;

namespace WaveEngine
{
	class Renderer;
	class MaterialFactory;
	class EntityManager;
	class Engine;
	class ImGuiClass;

	class WAVEEXPORT MaterialManager final : public Service
	{
	private:

		unsigned int currentMaterialID = Material::NULL_MATERIAL;

		unordered_map<unsigned int, Material*> materials;
		unordered_map<string, unsigned int> materialsIDByName;

		void SaveMaterial(Material*& material);

		MaterialManager();
		~MaterialManager();

		friend class Renderer;
		friend class MaterialFactory;
		friend class EntityManager;
		friend class Engine;
		friend class ServiceProvider;
		friend class ImGuiClass;

	public:

		Material* GetMaterial(const unsigned int id);

		unsigned int GetMaterial(const string_view name);

		void DeleteMaterial(const string_view name);

		void DeleteMaterial(const unsigned int& ID);

		unordered_map<unsigned int, Material*>& GetMaterials();
	};
}

