#include "WaveObject.h"

#include "WaveObjectFactory.h"
#include "WaveObjectRegistry.h"
#include "ECS/WObject/WObject.h"
#include "EventSystem/EventSystem.h"
#include "ECS/Transform/ECSTransform.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/BoundingBoxComp/BoundingBoxComp.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include <string>
#include "Events/ObjectChangeName.h"

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

	WaveObjectRegistry* WaveObject::GetWaveObjectRegistry() const
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
	}

	WaveObjectFactory* WaveObject::GetWaveObjectFactory() const
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>();
	}

	WaveObject::WaveObject(unsigned int ID) : WObject()
	{
		this->ID = ID;
	}

	WaveObject::WaveObject(const char* name)
	{
		*this = GetWaveObjectFactory()->Instantiate(name);
	}

	WaveObject::~WaveObject()
	{
	}

	void WaveObject::SetName(const string& name)
	{
		GetEventSystem()->Invoke<ObjectChangeName>(ID, name);
	}

	string WaveObject::GetName() const
	{
		return GetWaveObjectRegistry()->GetObjectName(ID);
	}

	void WaveObject::SetStatic(bool isStatic)
	{
		this->isStatic = isStatic;
	}

	bool WaveObject::IsStatic() const
	{
		return isStatic;
	}

	unsigned int WaveObject::GetID() const
	{
		return ID;
	}

	ECSTransform& WaveObject::GetTransform() const
	{
		return GetComponentRegistry()->GetComponent<ECSTransform>(ID);
	}

	BoundingBoxComp& WaveObject::GetBounds() const
	{
		return GetComponentRegistry()->GetComponent<BoundingBoxComp>(ID);
	}
}