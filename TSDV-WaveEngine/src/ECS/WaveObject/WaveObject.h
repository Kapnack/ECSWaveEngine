#pragma once

#include <string>

#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ECS/Transform/ECSTransform.h"
#include "EventSystem/EventSystem.h"

using namespace std;

namespace WaveEngine
{
	class WaveObjectFactory;
	class WaveObjectRegistry;

	class WaveObject
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

		template<typename T>
		T& AddComponent()
		{
			return GetComponentRegistry()->AddComponent<T>(ID);
		}

		template<typename T>
		T& GetComponent() const
		{
			return GetComponentRegistry()->GetComponent<T>(ID);
		}

		template<typename T>
		T* TryGetComponent()
		{
			return GetComponentRegistry()->TryGet<T>(ID);
		}


		template<typename T>
		void RemoveComponent()
		{
			GetComponentRegistry()->RemoveComponent<T>(ID);
		}
	};
}