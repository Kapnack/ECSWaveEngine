#pragma once

#include <vector>
#include <string>

#include "Export.h"
#include "ObjectNameSearch.h"
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

		bool isStatic = false;

		ComponentRegistry* GetComponentRegistry() const;
		EventSystem* GetEventSystem() const;
		WaveObjectRegistry* GetWaveObjectRegistry() const;
		WaveObjectFactory* GetWaveObjectFactory() const;

		WaveObject();

		friend class WObject;
		friend class WaveObjectFactory;
		friend class WaveObjectRegistry;

	public:

		template<TypeComponent... T>
		static WaveObject& Create(const char* name = nullptr);

		static WaveObject& Find(const char* name, ObjectNameSearch objectNamerSearch = ObjectNameSearch::Exact);
		static bool TryFind(const char* name, WaveObject*& waveObject, ObjectNameSearch objectNamerSearch = ObjectNameSearch::Exact);
		static WaveObject* TryFind(const char* name, ObjectNameSearch objectNamerSearch = ObjectNameSearch::Exact);
		static vector<WaveObject*> FindAll(const char* name, ObjectNameSearch objectNamerSearch = ObjectNameSearch::Contains);

		WaveObject(const char* name);
		~WaveObject();

		void SetName(const char* name);
		string GetName() const;

		void SetStatic(bool isStatic);
		bool IsStatic() const;

		ECSTransform& GetTransform() const;
		BoundingBoxComp& GetBounds() const;

		template<TypeComponent T>
		T& AddComponent();

		template<TypeComponent T>
		T& GetComponent() const;

		template<TypeComponent T>
		bool TryGetComponent(T*& component);

		template<TypeComponent T>
		T* TryGetComponent();

		template<TypeComponent T>
		void RemoveComponent();
	};
}

#include "WaveObject.tpp"