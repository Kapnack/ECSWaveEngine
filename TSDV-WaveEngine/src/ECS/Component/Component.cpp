#include "Component.h"

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	Component::Component(const unsigned int& ID)
	{
		ownerID = ID;
	}

	Component::~Component()
	{
	}

	WaveObject& Component::GetWaveObject() const
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetWaveObject(ownerID);
	}

	const unsigned int& Component::GetID() const
	{
		return ownerID;
	}
}