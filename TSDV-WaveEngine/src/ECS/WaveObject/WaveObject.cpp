#include "WaveObject.h"

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/Transform/ECSTransform.h"
#include "WaveObjectRegistry.h"

namespace WaveEngine
{
	ComponentRegistry* WaveObject::GetComponentRegistry() const
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}

	EventSystem* WaveObject::GetEventSystem() const
	{
		return ServiceProvider::Instance().Get<EventSystem>();
	}

	WaveObject::WaveObject(unsigned int ID)
	{
		this->ID = ID;
	}

	WaveObject::~WaveObject()
	{
	}

	void WaveObject::SetName(const string& name)
	{
		GetEventSystem()->Invoke<ObjectChangeName>(ID, this->name, name);
	}

	const string& WaveObject::GetName() const
	{
		return name;
	}

	unsigned int WaveObject::GetID() const
	{
		return ID;
	}

	ECSTransform& WaveObject::GetTransform() const
	{
		return GetComponentRegistry()->GetComponent<ECSTransform>(ID);
	}
}