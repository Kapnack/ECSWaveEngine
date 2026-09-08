#ifndef COMPONENT
#define COMPONENT

#include "Component.h"

#include "TypeComponent.h"
#include "ECS/WaveObject/WObject.h"
#include "ECS/WaveObject/WaveObject.h"
#include "ECS/Transform/ECSTransform.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"

namespace WaveEngine
{
	Component::Component(unsigned int ID) : WObject()
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

	template<TypeComponent T>
	T& Component::AddComponent()
	{
		return GetWaveObject().AddComponent<T>(ownerID);
	}

	template<TypeComponent T>
	T& Component::GetComponent() const
	{
		return GetWaveObject().GetComponent<T>(ownerID);
	}

	template<TypeComponent T>
	T* Component::TryGetComponent()
	{
		return GetWaveObject().TryGetComponent<T>(ownerID);
	}

	template<TypeComponent T>
	void Component::RemoveComponent()
	{
		GetWaveObject().RemoveComponent<T>(ownerID);
	}
}
#endif