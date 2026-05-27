#include "WaveObject.h"

#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine::Objects
{
	ComponentRegistry* WaveObject::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}

	const unsigned int WaveObject::GetID() const
	{
		return ID;
	}

	ECSTransform& WaveObject::GetTransform()
	{
		return GetComponentRegistry()->GetComponent<ECSTransform>(ID);
	}
}