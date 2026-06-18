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
	class ImGuiClass;

	WAVEEXPORT class MaterialManager final : public Service
	{
	private:

		unsigned int currentMaterialID = Material::NULL_MATERIAL;

		unordered_map<unsigned int, Material*> materials;

		void SaveMaterial(Material*& material);

		MaterialManager();
		~MaterialManager();

		friend class Renderer;
		friend class MaterialFactory;
		friend class EntityManager;
		friend class BaseGame;
		friend class ServiceProvider;
		friend class ImGuiClass;

	public:

		WAVEEXPORT Material* GetMaterial(const unsigned int id);

		WAVEEXPORT unsigned int GetMaterial(const string_view name);

		WAVEEXPORT void DeleteMaterial(const string_view name);

		WAVEEXPORT void DeleteMaterial(const unsigned int& ID);

		unordered_map<unsigned int, Material*>& GetMaterials();
	};
}

