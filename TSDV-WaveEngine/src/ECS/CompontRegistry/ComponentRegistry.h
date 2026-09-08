#pragma once

#include "ServiceProvider/Service.h"

#include <vector>
#include <typeindex>
#include <unordered_map>

#include "ECS/ComponentContainer/ComponentContainer.h"
#include <utility>

using namespace std;

namespace WaveEngine
{
	class WaveBehaviour;

	class ComponentRegistry : public Service
	{
	private:

		unordered_map<type_index, IStorage*> storages;
		unordered_map<unsigned int, vector<type_index>> waveBehavioursByEntityID;

	public:

		ComponentRegistry() : Service()
		{
		}

		~ComponentRegistry()
		{
			for (unordered_map<type_index, IStorage*>::iterator storage = storages.begin(); storage != storages.end(); ++storage)
				delete storage->second;
		}

		template<TypeComponent T>
		T& AddComponent(unsigned int entity)
		{
			type_index typeIndex = typeid(T);

			if constexpr (std::is_base_of_v<WaveBehaviour, T>)
				waveBehavioursByEntityID[entity].push_back(typeIndex);

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

		vector<WaveBehaviour*> GetBehaviours()
		{
			vector<WaveBehaviour*> waveBehaviours;

			for (const pair<const unsigned int, vector<type_index>>& entry : waveBehavioursByEntityID)
			{
				unsigned int entity = entry.first;
				const vector<type_index>& typeIndices = entry.second;

				for (const type_index& typeIndex : typeIndices)
				{
					auto storageIt = storages.find(typeIndex);
					if (storageIt == storages.end())
						continue;

					if (WaveBehaviour* behaviour = storageIt->second->GetAsWaveBehaviour(entity))
						waveBehaviours.push_back(behaviour);
				}
			}

			return waveBehaviours;
		}

		template<TypeComponent T>
		T* TryGet(unsigned int entity)
		{
			return GetComponentStorage<T>().TryGet(entity);
		}

		template<TypeComponent T>
		void RemoveComponent(unsigned int entity)
		{
			type_index typeIndex = typeid(T);

			if (!storages.contains(typeIndex))
				return;

			static_cast<ComponentContainer<T>*>(storages.at(typeIndex))->Remove(entity);
		}

		template<TypeComponent T>
		ComponentContainer<T>& GetComponentStorage()
		{
			return *static_cast<ComponentContainer<T>*>(storages.at(typeid(T)));
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
		T& GetComponent(const unsigned int& entity)
		{
			return GetComponentStorage<T>().Get(entity);
		}
	};
}