#ifndef WAVE_ENGINE_WAVE_OBJECT
#define WAVE_ENGINE_WAVE_OBJECT

#include "WaveObject.h"
#include "ECS/WObject/WObject.h"
#include "ECS/Component/TypeComponent.h"

namespace WaveEngine
{
	template<TypeComponent... T>
	WaveObject& WaveObject::Create(const char* name)
	{
		WaveObject* waveObject = new WaveObject(name);
		(waveObject->AddComponent<T>(), ...);
		return *waveObject;
	}

	template<TypeComponent T>
	T& WaveObject::AddComponent()
	{
		return GetComponentRegistry()->AddComponent<T>(GetID());
	}

	template<TypeComponent T>
	T& WaveObject::GetComponent() const
	{
		return GetComponentRegistry()->GetComponent<T>(GetID());
	}

	template<TypeComponent T>
	T* WaveObject::TryGetComponent()
	{
		return GetComponentRegistry()->TryGet<T>(GetID());
	}

	template<TypeComponent T>
	void WaveObject::RemoveComponent()
	{
		GetComponentRegistry()->RemoveComponentImmediate<T>(GetID());
	}
}

#endif