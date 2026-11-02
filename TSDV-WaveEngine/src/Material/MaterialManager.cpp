#include "MaterialManager.h"

#include <utility>
#include <GL/glew.h>
#include <algorithm>
#include <string_view>
#include <unordered_map>

#include "Material.h"
#include "EventSystem/EventSystem.h"
#include "MaterialBehaviourConcept.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Material/Event/MaterialDelition.h"

namespace WaveEngine
{
	MaterialManager::MaterialManager()
	{
	}

	MaterialManager::~MaterialManager()
	{
		for (unordered_map<unsigned int, Material*>::iterator it = materials.begin(); it != materials.end(); ++it)
			delete it->second;

		for (unordered_map<unsigned int, WaveMaterialBehaviour*>::iterator it = materialsBehaviours.begin(); it != materialsBehaviours.end(); ++it)
			delete it->second;

		materials.clear();
		materialsBehaviours.clear();
	}

	unsigned int MaterialManager::GetMaterial(const string_view name)
	{
		if (!materialsIDByName.contains(name.data()))
			return WObject::NULL_OBJECT;

		return materialsIDByName[name.data()];
	}

	void MaterialManager::Destroy(Material& material)
	{
		Destroy(material.ID);
	}

	void MaterialManager::Destroy(unsigned int ID)
	{
		materialsToDestroy.insert(ID);
	}

	void MaterialManager::SaveMaterial(Material*& material)
	{
		materials[material->GetID()] = material;
		materialsIDByName[material->GetName()] = material->GetID();
	}

	void MaterialManager::DestroyMaterialBehaviour(unsigned int materialID)
	{
		delete materialsBehaviours[materialID];
		materialsBehaviours.erase(materialID);
	}

	void MaterialManager::Update()
	{
		for (unsigned int materialID : materialsToDestroy)
			DestroyImmediate(materialID);

		materialsToDestroy.clear();
	}

	Material& MaterialManager::GetMaterial(const unsigned int id)
	{
		return *materials.at(id);
	}

	unordered_map<unsigned int, Material*>& MaterialManager::GetMaterials()
	{
		return materials;
	}

	void MaterialManager::DestroyImmediate(Material& material)
	{
		DestroyImmediate(material.ID);
	}

	void MaterialManager::DestroyImmediate(unsigned int ID)
	{
		Material* it = materials[ID];

		if (it == nullptr)
			return;

		ServiceProvider::Instance().Get<EventSystem>()->Invoke<MaterialDelition>(ID);

		glDeleteProgram(*it);
		delete it;
		materials.erase(ID);
	}
}
