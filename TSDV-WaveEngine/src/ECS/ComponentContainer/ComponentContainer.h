#pragma once

#include <vector>

using namespace std;

namespace WaveEngine
{
	struct IStorage
	{

	};

	template <typename T>
	class ComponentContainer
	{
	private:

		vector<T> components;
		vector<int> entities;
		vector<int> componentByEntity;

	public:

		void Add(const int& entity, const T& component = T())
		{
			if (entity >= componentByEntity.size())
			{
				size_t oldSize = componentByEntity.size();
				componentByEntity.resize(entity + 1);
				for (size_t i = oldSize; i < componentByEntity.size(); ++i)
					componentByEntity[i] = -1;
			}

			int index = components.size();

			components.push_back(component);
			entities.push_back(entity);

			componentByEntity[entity] = index;
		}

		bool Has(int entity) const
		{
			if (entity >= componentByEntity.size())
				return false;

			return componentByEntity[entity] != -1;
		}

		void Remove(int entity)
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

		T& Get(const int& entity)
		{
			return components.at(componentByEntity.at(entity));
		}

		T* TryGet(int entity)
		{
			if (entity >= componentByEntity.size())
				return nullptr;

			int index = componentByEntity[entity];

			if (index == -1)
				return nullptr;

			return &components[index];
		}

		vector<T>& GetComponents()
		{
			return components;
		}

		const vector<int>& GetEntities() const
		{
			return entities;
		}
	};

	template <typename T>
	struct Storage : IStorage
	{
		ComponentContainer<T> container;
	};
}