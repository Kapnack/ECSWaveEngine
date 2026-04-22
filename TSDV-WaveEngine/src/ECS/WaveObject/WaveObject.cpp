#include "WaveObject.h"

#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine::Objects
{
	unsigned int WaveObject::currentID = NULL_OBJECT;

	ComponentRegistry* WaveObject::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}

	const unsigned int WaveObject::GetID() const
	{
		return ID;
	}
}