#include "MaterialManager.h"

#include <GL/glew.h>
#include <algorithm>

#include "EventSystem/EventSystem.h"
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
		unordered_map<unsigned int, Material*>::iterator it = find_if(materials.begin(), materials.end(),
			[&name](const pair<const unsigned int, Material*>& entry)
			{
				return entry.second &&
					entry.second->GetName() == name;
			});

		if (it == materials.end())
			return 0;

		return it->first;
	}

	void MaterialManager::SaveMaterial(const unsigned int& ID, Material* material)
	{
		materials[ID] = material;
	}

	Material* MaterialManager::GetMaterial(const unsigned int id)
	{
		return id != Material::NULL_MATERIAL ? materials[id] : nullptr;
	}

	unordered_map<unsigned int, Material*>& MaterialManager::GetMaterials()
	{
		return materials;
	}

	void MaterialManager::DeleteMaterial(const string_view name)
	{
		unordered_map<unsigned int, Material*>::iterator it = find_if(materials.begin(), materials.end(),
			[&name](const pair<const unsigned int, Material*>& entry)
			{
				return entry.second &&
					entry.second->GetName() == name;
			});


		if (it == materials.end())
			return;

		ServiceProvider::Instance().Get<EventSystem>()->Invoke<MaterialDelition>(it->first);

		delete it->second;
		materials.erase(it);
	}

	void MaterialManager::DeleteMaterial(const unsigned int& ID)
	{
		if (ID == Material::NULL_MATERIAL)
			return;

		Material* it = materials[ID];

		if (it == nullptr)
			return;

		ServiceProvider::Instance().Get<EventSystem>()->Invoke<MaterialDelition>(ID);

		delete it;
		materials.erase(ID);
	}
}
