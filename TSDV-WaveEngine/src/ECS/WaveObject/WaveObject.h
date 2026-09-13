#pragma once

#include <string>

#include "ECS/WObject/WObject.h"
#include "EventSystem/EventSystem.h"
#include "ECS/Transform/ECSTransform.h"
#include "ECS/Component/TypeComponent.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

using namespace std;

namespace WaveEngine
{
	class WaveObjectFactory;
	class WaveObjectRegistry;

	class WaveObject : public WObject
	{
	private:

		unsigned int ID = NULL_OBJECT;

		ComponentRegistry* GetComponentRegistry() const;
		EventSystem* GetEventSystem() const;
		WaveObjectRegistry* GetWaveObjectRegistry() const;

		friend class WaveObjectFactory;
		friend class WaveObjectRegistry;

	public:

		static const unsigned int NULL_OBJECT = 0;

		WaveObject(unsigned int ID);
		~WaveObject();

		void SetName(const string& name);
		string GetName() const;

		unsigned int GetID() const;

		ECSTransform& GetTransform() const;

		template<TypeComponent T>
		T& AddComponent()
		{
			return GetComponentRegistry()->AddComponent<T>(ID);
		}

		template<TypeComponent T>
		T& GetComponent() const
		{
			return GetComponentRegistry()->GetComponent<T>(ID);
		}

		template<TypeComponent T>
		T* TryGetComponent()
		{
			return GetComponentRegistry()->TryGet<T>(ID);
		}

		template<TypeComponent T>
		void RemoveComponent()
		{
			GetComponentRegistry()->RemoveComponent<T>(ID);
		}
	};
}