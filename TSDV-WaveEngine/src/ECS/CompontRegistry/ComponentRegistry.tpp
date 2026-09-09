#ifndef COMPONENT_REGISTRY
#define COMPONENT_REGISTRY

#include "ComponentRegistry.h"
#include "ECS/WaveBehaviour/WaveBehaviour.h"

namespace WaveEngine
{
	ComponentRegistry::ComponentRegistry() : Service()
	{
	}

	ComponentRegistry::~ComponentRegistry()
	{
		for (unordered_map<type_index, IStorage*>::iterator storage = storages.begin(); storage != storages.end(); ++storage)
			delete storage->second;
	}

	template<typename T>
	T& ComponentRegistry::AddComponent(unsigned int entity)
	{
		type_index typeIndex = typeid(T);

		if constexpr (std::is_base_of_v<WaveBehaviour, T>)
			waveBehavioursByEntityID[entity].push_back(typeIndex);

		if (!storages.contains(typeIndex))
			storages[typeIndex] = new ComponentContainer<T>();

		static_cast<ComponentContainer<T>*>(storages.at(typeIndex))->Add(entity);

		return static_cast<ComponentContainer<T>*>(storages.at(typeIndex))->Get(entity);
	}

	template<typename T>
	bool ComponentRegistry::HasStorage()
	{
		return storages.find(typeid(T)) != storages.end();
	}

	template<typename T>
	bool ComponentRegistry::Has(unsigned int entity)
	{
		return GetComponentStorage<T>().Has(entity);
	}

	template<typename T>
	T& ComponentRegistry::Get(unsigned int entity)
	{
		return GetComponentStorage<T>().Get(entity);
	}

	vector<WaveBehaviour*> ComponentRegistry::GetBehaviours()
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

	template<typename T>
	T* ComponentRegistry::TryGet(unsigned int entity)
	{
		return GetComponentStorage<T>().TryGet(entity);
	}

	template<typename T>
	void ComponentRegistry::RemoveComponent(unsigned int entity)
	{
		type_index typeIndex = typeid(T);

		if (!storages.contains(typeIndex))
			return;

		static_cast<ComponentContainer<T>*>(storages.at(typeIndex))->Remove(entity);
	}

	template<typename T>
	ComponentContainer<T>& ComponentRegistry::GetComponentStorage()
	{
		return *static_cast<ComponentContainer<T>*>(storages.at(typeid(T)));
	}

	template<typename T>
	ComponentContainer<T>& ComponentRegistry::CreateOrGetComponentStorage()
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

	template<typename T>
	ComponentContainer<T>* ComponentRegistry::TryGetComponentStorage()
	{
		type_index typeIndex = typeid(T);

		if (!storages.contains(typeIndex))
			return nullptr;

		return static_cast<ComponentContainer<T>*>(storages.at(typeIndex));
	}

	template<typename T>
	T& ComponentRegistry::GetComponent(unsigned int entity)
	{
		return GetComponentStorage<T>().Get(entity);
	}
}
#endif