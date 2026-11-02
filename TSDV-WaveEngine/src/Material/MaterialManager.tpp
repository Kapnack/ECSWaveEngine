#ifndef WAVE_ENGINE_MATERIAL_MANAGER
#define WAVE_ENGINE_MATERIAL_MANAGER

#include "MaterialManager.h"
#include "MaterialBehaviourConcept.h"

namespace WaveEngine
{
	template<MaterialBehaviourConcept T>
	void MaterialManager::SetMaterialBehaviour(unsigned int materialID)
	{
		if (materialsBehaviours.contains(materialID))
			delete materialsBehaviours[materialID];

		materialsBehaviours[materialID] = new T();
	}
}

#endif
