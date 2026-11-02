#ifndef WAVE_ENGINE_MATERIAL
#define WAVE_ENGINE_MATERIAL

#include "Material.h"
#include "MaterialManager.h"
#include "MaterialBehaviourConcept.h"
#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine
{
	template<MaterialBehaviourConcept T>
	void Material::SetBehaviour()
	{
		ServiceProvider::Instance().Get<MaterialManager>()->SetMaterialBehaviour<T>(GetID());
	}
}

#endif