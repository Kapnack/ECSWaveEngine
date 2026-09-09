#ifndef COMPONENT_CONTAINER
#define COMPONENT_CONTAINER

#include "ComponentContainer.h"

#include "ECS/WaveObject/WaveObject.h"
#include "ECS/WaveBehaviour/WaveBehaviour.h"

namespace WaveEngine
{
	template<typename T>
	void ComponentContainer<T>::Add(unsigned int entity)
	{
		if (entity >= componentByEntity.size())
		{
			size_t oldSize = componentByEntity.size();
			componentByEntity.resize(entity + 1);
			for (size_t i = oldSize; i < componentByEntity.size(); ++i)
				componentByEntity[i] = -1;
		}

		int index = components.size();

		components.emplace_back(entity);
		entities.push_back(entity);

		componentByEntity[entity] = index;

		T& component = Get(entity);

		component.SetIsActive(true);
		component.Init();
		component.LateInit();
	}

	template<typename T>
	bool ComponentContainer<T>::Has(unsigned int entity) const
	{
		if (entity >= componentByEntity.size())
			return false;

		return componentByEntity[entity] != -1;
	}

	template<typename T>
	void ComponentContainer<T>::Remove(unsigned int entity)
	{
		if (!Has(entity))
			return;

		int index = componentByEntity[entity];
		int lastIndex = components.size() - 1;

		if (index != lastIndex)
		{
			components[index] = components[lastIndex];
			entities[index] = entities[lastIndex];

			componentByEntity[entities[index]] = index;
		}

		components.pop_back();
		entities.pop_back();

		componentByEntity[entity] = -1;
	}

	template<typename T>
	T& ComponentContainer<T>::Get(unsigned int entity)
	{
		return components.at(componentByEntity.at(entity));
	}

	template<typename T>
	T& ComponentContainer<T>::GetFirst()
	{
		typename std::vector<T>::iterator it = components.begin();
		return *it;
	}

	template<typename T>
	T* ComponentContainer<T>::TryGet(unsigned int entity)
	{
		if (entity >= componentByEntity.size())
			return nullptr;

		const unsigned int index = componentByEntity[entity];

		if (index == -1)
			return nullptr;

		return &components[index];
	}

	template<typename T>
	vector<T>& ComponentContainer<T>::GetComponents()
	{
		return components;
	}

	template<typename T>
	const vector<unsigned int>& ComponentContainer<T>::GetEntities() const
	{
		return entities;
	}

	template<typename T>
	WaveBehaviour* ComponentContainer<T>::GetAsWaveBehaviour(unsigned int entity)
	{
		if constexpr (std::is_base_of_v<WaveBehaviour, T>)
		{
			if (Has(entity))
				return &Get(entity);
		}

		return nullptr;
	}

	template<typename T>
	T& ComponentContainer<T>::operator[](unsigned int entityID)
	{
		return Get(entityID);
	}
}

#endif