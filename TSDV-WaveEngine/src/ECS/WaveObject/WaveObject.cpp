#include "WaveObject.h"

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/Transform/ECSTransform.h"

namespace WaveEngine
{
	ComponentRegistry* WaveObject::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}

	WaveObject::WaveObject(const unsigned int& ID)
	{
		this->ID = ID;
	}

	WaveObject::~WaveObject()
	{
	}

	void WaveObject::SetName(const string& name)
	{
		this->name = name;
	}

	const string& WaveObject::GetName() const
	{
		return name;
	}

	const unsigned int& WaveObject::GetID() const
	{
		return ID;
	}

	ECSTransform& WaveObject::GetTransform()
	{
		return GetComponentRegistry()->GetComponent<ECSTransform>(ID);
	}
}