#include "Component.h"

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	Component::Component(unsigned int ID)
	{
		ownerID = ID;
	}

	Component::~Component()
	{
	}

	void Component::Init()
	{
	}

	void Component::LateInit()
	{
	}

	WaveObject& Component::GetWaveObject() const
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetWaveObject(ownerID);
	}

	ECSTransform& Component::GetTransform() const
	{
		return GetWaveObject().GetTransform();
	}

	unsigned int Component::GetID() const
	{
		return ownerID;
	}

	void Component::SetIsActive(bool isActive)
	{
		this->isActive = isActive;
	}

	bool Component::GetIsActive() const
	{
		return isActive;
	}
}