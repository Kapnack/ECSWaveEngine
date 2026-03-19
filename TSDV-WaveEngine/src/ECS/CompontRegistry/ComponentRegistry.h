#pragma once

#include "ServiceProvider/Service.h"

#include <unordered_map>
#include <typeindex>

#include "ECS/ComponentContainer/ComponentContainer.h"

using namespace std;

namespace WaveEngine
{
	class ComponentRegistry : public Service
	{
	private:

		unordered_map<type_index, IStorage*> storages;

	public:

		ComponentRegistry() : Service()
		{
		}

		~ComponentRegistry()
		{
			for (unordered_map<type_index, IStorage*>::iterator storage = storages.begin(); storage != storages.end(); ++storage)
				delete storage->second;
		}

		template<typename T>
		void AddComponent(const int& entity, const T& component = T())
		{
			type_index typeIndex = typeid(T);

			if (!storages.contains(typeIndex))
				storages[typeIndex] = new Storage<T>();

			static_cast<Storage<T>*>(storages.at(typeIndex))->container.Add(entity, component);
		}

		template<typename T>
		bool HasStorage()
		{
			return storages.find(typeid(T)) != storages.end();
		}

		template<typename T>
		bool Has(const int& entity)
		{
			return GetComponentStorage<T>().Has(entity);
		}

		template<typename T>
		T& Get(const int& entity)
		{
			return GetComponentStorage<T>().Get(entity);
		}

		template<typename T>
		T* TryGet(const int& entity)
		{
			return GetComponentStorage<T>().TryGet(entity);
		}

		template<typename T>
		void RemoveComponent(const int& entity)
		{
			type_index typeIndex = typeid(T);

			if (!storages.contains(typeIndex))
				return;

			static_cast<Storage<T>*>(storages.at(typeIndex))->container.Remove(entity);
		}

		template<typename T>
		ComponentContainer<T>& GetComponentStorage()
		{
			return static_cast<Storage<T>*>(storages.at(typeid(T)))->container;
		}

		template<typename T>
		ComponentContainer<T>& CreateOrGetComponentStorage()
		{
			type_index typeIndex = typeid(T);

			if (!storages.contains(typeIndex))
			{
				Storage<T>* newStorage = new Storage<T>();
				storages[typeIndex] = newStorage;

				return newStorage->container;
			}

			return static_cast<Storage<T>*>(storages.at(typeid(T)))->container;
		}

		template<typename T>
		ComponentContainer<T>* TryGetComponentStorage()
		{
			type_index typeIndex = typeid(T);

			if (!storages.contains(typeIndex))
				return nullptr;

			return static_cast<Storage<T>*>(storages.at(typeIndex))->container;
		}

		template<typename T>
		T& GetComponent(const int& entity)
		{
			return GetComponentStorage<T>().Get(entity);
		}
	};
}