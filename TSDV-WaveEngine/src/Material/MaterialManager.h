#pragma once

#include "ServiceProvider/Service.h"

#include <set>
#include <string>
#include <string_view>
#include <unordered_map>

#include "Export.h"
#include "ECS/WObject/WObject.h"
#include "MaterialBehaviourConcept.h"
#include "WaveMaterialBehaviour/WaveMaterialBehaviour.h"

using namespace std;

namespace WaveEngine
{
	class Engine;
	class Material;
	class Renderer;
	class ImGuiClass;
	class EntityManager;
	class MaterialFactory;

	class MaterialManager final : public Service
	{
	private:

		unsigned int currentMaterialID = WObject::NULL_OBJECT;

		set<unsigned int> materialsToDestroy;
		unordered_map<unsigned int, Material*> materials;
		unordered_map<string, unsigned int> materialsIDByName;
		set<unsigned int> waveMaterialBehaviourToDestroy;

		unordered_map<unsigned int, WaveMaterialBehaviour*> materialsBehaviours;

		void SaveMaterial(Material*& material);

		template<MaterialBehaviourConcept T>
		void SetMaterialBehaviour(unsigned int materialID);

		void DestroyMaterialBehaviour(unsigned int materialID);

		void UpdateMaterials();
		void Update();

		MaterialManager();
		~MaterialManager();

		friend class Engine;
		friend class Material;
		friend class Renderer;
		friend class ImGuiClass;
		friend class EntityManager;
		friend class MaterialFactory;
		friend class ServiceProvider;

	public:

		Material& GetMaterial(const unsigned int id);

		unsigned int GetMaterial(const string_view name);

		void Destroy(Material& material);
		void Destroy(unsigned int ID);
		void DestroyImmediate(Material& material);
		void DestroyImmediate(unsigned int ID);

		void Destroy(WaveMaterialBehaviour& waveMaterialBehaviour);
		void DestroyBehaviour(unsigned int ID);
		void DestroyImmediate(WaveMaterialBehaviour& waveMaterialBehaviour);
		void DestroyImmediateBehaviour(unsigned int ID);

		unordered_map<unsigned int, Material*>& GetMaterials();
	};
}

#include "MaterialManager.tpp"