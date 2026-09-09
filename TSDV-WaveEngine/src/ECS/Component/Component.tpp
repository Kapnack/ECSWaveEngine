#ifndef WAVEENGINE_COMPONENT_TPP
#define WAVEENGINE_COMPONENT_TPP

#include "Component.h"

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

	template<typename T>
	T& Component::AddComponent()
	{
		return GetWaveObject().AddComponent<T>();
	}

	template<typename T>
	T& Component::GetComponent() const
	{
		return GetWaveObject().GetComponent<T>();
	}

	template<typename T>
	T* Component::TryGetComponent()
	{
		return GetWaveObject().TryGetComponent<T>();
	}

	template<typename T>
	void Component::RemoveComponent()
	{
		GetWaveObject().RemoveComponent<T>();
	}
}
#endif