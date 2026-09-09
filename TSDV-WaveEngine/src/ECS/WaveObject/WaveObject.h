#pragma once

#include <string>

#include "WObject.h"
#include "EventSystem/EventSystem.h"
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

		inline void SetName(const string& name);
		inline string GetName() const;

		inline unsigned int GetID() const;

		inline ECSTransform& GetTransform() const;

		template<typename T>
		T& AddComponent();

		template<typename T>
		T& GetComponent() const;

		template<typename T>
		T* TryGetComponent();

		template<typename T>
		void RemoveComponent();
	};
}

#include "WaveObject.tpp"