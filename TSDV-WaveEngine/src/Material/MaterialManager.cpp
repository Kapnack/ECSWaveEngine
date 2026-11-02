#include "MaterialManager.h"

#include <utility>
#include <GL/glew.h>
#include <string_view>
#include <unordered_map>

#include "Material.h"
#include "EventSystem/EventSystem.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Material/Event/MaterialDelition.h"
#include "WaveMaterialBehaviour/WaveMaterialBehaviour.h"

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

	void MaterialManager::UpdateMaterials()
	{
		for (unordered_map<unsigned int, WaveMaterialBehaviour*>::iterator it = materialsBehaviours.begin(); it != materialsBehaviours.end(); ++it)
			it->second->Update();
	}

	void MaterialManager::Update()
	{
		for (unsigned int waveMaterialBehaviourID : waveMaterialBehaviourToDestroy)
			DestroyImmediateBehaviour(waveMaterialBehaviourID);

		for (unsigned int materialID : materialsToDestroy)
			DestroyImmediate(materialID);

		waveMaterialBehaviourToDestroy.clear();
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
		ServiceProvider::Instance().Get<EventSystem>()->Invoke<MaterialDelition>(ID);

		if (materialsBehaviours.contains(ID))
			DestroyImmediateBehaviour(ID);

		glDeleteProgram(*materials[ID]);
		delete materials[ID];
		materials.erase(ID);
	}

	void MaterialManager::Destroy(WaveMaterialBehaviour& waveMaterialBehaviour)
	{
		DestroyBehaviour(waveMaterialBehaviour.GetID());
	}

	void MaterialManager::DestroyBehaviour(unsigned int ID)
	{
		waveMaterialBehaviourToDestroy.insert(ID);
	}

	void MaterialManager::DestroyImmediate(WaveMaterialBehaviour& waveMaterialBehaviour)
	{
		DestroyImmediateBehaviour(waveMaterialBehaviour.GetID());
	}

	void MaterialManager::DestroyImmediateBehaviour(unsigned int ID)
	{
		materialsBehaviours[ID]->Dispose();
		delete materialsBehaviours[ID];
		materialsBehaviours.erase(ID);
	}
}
