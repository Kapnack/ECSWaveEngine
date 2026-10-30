#pragma once

#include <string>
#include <typeindex>
#include <unordered_set>

#include "Export.h"
#include "ECS/WObject/WObject.h"
#include "EventSystem/EventSystem.h"
#include "ECS/Transform/ECSTransform.h"
#include "ECS/Component/TypeComponent.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

using namespace std;

namespace WaveEngine
{
	class BoundingBoxComp;
	class WaveObjectFactory;
	class WaveObjectRegistry;

	class WAVEEXPORT WaveObject : public WObject
	{
	private:

		unsigned int ID = NULL_OBJECT;

		bool isStatic = false;

		unordered_set<type_index> componentsTypes;

		ComponentRegistry* GetComponentRegistry() const;
		EventSystem* GetEventSystem() const;
		WaveObjectRegistry* GetWaveObjectRegistry() const;
		WaveObjectFactory* GetWaveObjectFactory() const;

		friend class WaveObjectFactory;
		friend class WaveObjectRegistry;

	public:

		static const unsigned int NULL_OBJECT = 0;

		WaveObject(const char* name = nullptr);
		WaveObject(unsigned int ID);
		~WaveObject();

		void SetName(const string& name);
		string GetName() const;

		void SetStatic(bool isStatic);
		bool IsStatic() const;

		unsigned int GetID() const;

		ECSTransform& GetTransform() const;
		BoundingBoxComp& GetBounds() const;

		template<TypeComponent T>
		T& AddComponent()
		{
			componentsTypes.insert(typeid(T));
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