#pragma once

#include "ServiceProvider/Service.h"

#include <set>
#include <vector>
#include <utility>
#include <typeindex>
#include <algorithm>
#include <type_traits>
#include <unordered_set>
#include <unordered_map>

#include "ECS/Component/Component.h"
#include "ECS/Component/TypeComponent.h"
#include "ECS/ComponentContainer/ComponentContainer.h"

using namespace std;

namespace WaveEngine
{
	class WaveBehaviour;

	class ComponentRegistry : public Service
	{
	private:

		unordered_map<type_index, IStorage*> storages;
		unordered_map<unsigned int, unordered_set<type_index>> componentsPerEntity;
		set<pair<unsigned int, type_index>> componentsToRemovePerEntity;
		unordered_map<unsigned int, vector<type_index>> waveBehavioursByEntityID;
		unordered_map<type_index, set<unsigned int>> entitiesPerComponents;
		vector<type_index> waveBehavioursType;

	public:

		ComponentRegistry();
		~ComponentRegistry();

		void Update();

		template<TypeComponent... T>
		tuple<T&...> AddComponents(unsigned int entity)
		{
			return tuple<T&...>{AddComponent<T>(entity)...};
		}

		template<TypeComponent T>
		T& AddComponent(unsigned int entity)
		{
			type_index typeIndex = typeid(T);

			if constexpr (is_base_of_v<WaveBehaviour, T>)
			{
				waveBehavioursByEntityID[entity].push_back(typeIndex);
				entitiesPerComponents[typeid(WaveBehaviour)].insert(entity);

				if (find(waveBehavioursType.begin(), waveBehavioursType.end(), typeIndex) == waveBehavioursType.end())
					waveBehavioursType.push_back(typeIndex);
			}

			componentsPerEntity[entity].insert(typeIndex);
			entitiesPerComponents[typeIndex].insert(entity);

			if (!storages.contains(typeIndex))
				storages[typeIndex] = new ComponentContainer<T>();

			static_cast<ComponentContainer<T>*>(storages.at(typeIndex))->Add(entity);

			return static_cast<ComponentContainer<T>*>(storages.at(typeIndex))->Get(entity);
		}

		template<TypeComponent T>
		bool HasStorage()
		{
			return storages.find(typeid(T)) != storages.end();
		}

		template<TypeComponent T>
		bool Has(unsigned int entity)
		{
			return GetComponentStorage<T>().Has(entity);
		}

		template<TypeComponent T>
		T& Get(unsigned int entity)
		{
			return GetComponentStorage<T>().Get(entity);
		}

		vector<WaveBehaviour*> GetBehaviours();

		vector<WaveBehaviour*> GetWaveBehaviours(unsigned int entity);

		void RemoveAllComponents(unsigned int entity);

		template<TypeComponent T>
		bool TryGet(unsigned int entity, T*& component)
		{
			return GetComponentStorage<T>().TryGet(entity, component);
		}

		template<TypeComponent T>
		T* TryGet(unsigned int entity)
		{
			return GetComponentStorage<T>().TryGet(entity);
		}

		vector<Component*> GetAll(type_index typeIndex);

		template<TypeComponent T>
		void RemoveComponentImmediate(unsigned int entity)
		{
			RemoveComponentImmediate(entity, typeid(T));
		}

		void RemoveComponentImmediate(unsigned int entity, type_index typeIndex);

		template<TypeComponent T>
		void RemoveComponent(unsigned int entity)
		{
			RemoveComponent(entity, typeid(T));
		}

		void RemoveComponent(unsigned int entity, type_index typeIndex);

		template<TypeComponent T>
		ComponentContainer<T>& GetComponentStorage()
		{
			return static_cast<ComponentContainer<T>&>(GetComponentStorage(typeid(T)));
		}

		IStorage& GetComponentStorage(type_index typeIndex)
		{
			return *static_cast<IStorage*>(storages.at(typeIndex));
		}

		template<TypeComponent T>
		ComponentContainer<T>& CreateOrGetComponentStorage()
		{
			type_index typeIndex = typeid(T);

			if (!storages.contains(typeIndex))
			{
				ComponentContainer<T>* newStorage = new ComponentContainer<T>();
				storages[typeIndex] = newStorage;

				return *newStorage;
			}

			return *static_cast<ComponentContainer<T>*>(storages.at(typeid(T)));
		}

		template<TypeComponent T>
		ComponentContainer<T>* TryGetComponentStorage()
		{
			type_index typeIndex = typeid(T);

			if (!storages.contains(typeIndex))
				return nullptr;

			return static_cast<ComponentContainer<T>*>(storages.at(typeIndex));
		}

		template<TypeComponent T>
		T& GetComponent(unsigned int entity)
		{
			return GetComponentStorage<T>().Get(entity);
		}

		Component& GetComponent(unsigned int entity, type_index typeIndex)
		{
			return GetComponentStorage(typeIndex).GetBase(entity);
		}
	};
}