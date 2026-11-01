#include "MaterialManager.h"

#include <utility>
#include <GL/glew.h>
#include <algorithm>
#include <string_view>
#include <unordered_map>

#include "Material.h"
#include "EventSystem/EventSystem.h"
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

		materials.clear();
	}

	unsigned int MaterialManager::GetMaterial(const string_view name)
	{
		if (!materialsIDByName.contains(name.data()))
			return Material::NULL_MATERIAL;

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

	void MaterialManager::Update()
	{
		for (unsigned int materialID : materialsToDestroy)
			DestroyImmediate(materialID);

		materialsToDestroy.clear();
	}

	Material* MaterialManager::GetMaterial(const unsigned int id)
	{
		return id != Material::NULL_MATERIAL ? materials[id] : nullptr;
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
