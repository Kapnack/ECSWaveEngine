#pragma once

#include <string>

#include "WObject.h"
#include "EventSystem/EventSystem.h"
#include "ECS/Component/TypeComponent.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

using namespace std;

namespace WaveEngine
{
	class ECSTransform;
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
		T& AddComponent();

		template<TypeComponent T>
		T& GetComponent() const;

		template<TypeComponent T>
		T* TryGetComponent();

		template<TypeComponent T>
		void RemoveComponent();
	};
}

#include "WaveObject.tpp"