#pragma once

#include "ServiceProvider/Service.h"

#include <unordered_map>

#include "Export.h"
#include "Material/Material.h"
#include "ServiceProvider/ServiceProvider.h"

using namespace std;

namespace WaveEngine
{
	class Renderer;
	class MaterialFactory;
	class EntityManager;
	class BaseGame;
	class EntitiesImGui;
	class MaterialsImGui;

	WAVEEXPORT class MaterialManager final : public Service
	{
	private:

		unsigned int currentMaterialID = Material::NULL_MATERIAL;

		unordered_map<unsigned int, Material*> materials;

		void SaveMaterial(const unsigned int& ID, Material* material);

		Material* GetMaterial(const unsigned int id);

		unordered_map<unsigned int, Material*>& GetMaterials();

		MaterialManager();
		~MaterialManager();

		friend class Renderer;
		friend class MaterialFactory;
		friend class EntityManager;
		friend class BaseGame;
		friend class ServiceProvider;
		friend class EntitiesImGui;
		friend class MaterialsImGui;

	public:

		WAVEEXPORT unsigned int GetMaterial(const string_view name);

		WAVEEXPORT void DeleteMaterial(const string_view name);

		WAVEEXPORT void DeleteMaterial(const unsigned int& ID);
	};
}

