#pragma once

#include <vector>
#include <type_traits>

#include "ECS/Component/TypeComponent.h"

using namespace std;

namespace WaveEngine
{
	class WaveBehaviour;

	class IStorage
	{
	public:

		IStorage()
		{ }

		~IStorage()
		{ }

		virtual WaveBehaviour* GetAsWaveBehaviour(unsigned int entity) { return nullptr; }
	};

	template <TypeComponent T>
	class ComponentContainer : public IStorage
	{
	private:

		vector<T> components;
		vector<unsigned int> entities;
		vector<unsigned int> componentByEntity;

	public:

		void Add(unsigned int entity)
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

		bool Has(unsigned int entity) const
		{
			if (entity >= componentByEntity.size())
				return false;

			return componentByEntity[entity] != -1;
		}

		void Remove(unsigned int entity)
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

		T& Get(unsigned int entity)
		{
			return components.at(componentByEntity.at(entity));
		}

		T& GetFirst()
		{
			typename std::vector<T>::iterator it = components.begin();
			return *it;
		}

		T* TryGet(unsigned int entity)
		{
			if (entity >= componentByEntity.size())
				return nullptr;

			const unsigned int index = componentByEntity[entity];

			if (index == -1)
				return nullptr;

			return &components[index];
		}

		vector<T>& GetComponents()
		{
			return components;
		}

		const vector<unsigned int>& GetEntities() const
		{
			return entities;
		}

		WaveBehaviour* GetAsWaveBehaviour(unsigned int entity) override
		{
			if constexpr (std::is_base_of_v<WaveBehaviour, T>)
			{
				if (Has(entity))
					return &Get(entity);
			}

			return nullptr;
		}

		T& operator[](unsigned int entityID)
		{
			return Get(entityID);
		}
	};
}