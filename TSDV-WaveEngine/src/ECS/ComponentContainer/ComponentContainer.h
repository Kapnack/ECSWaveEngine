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
		vector<int> sparse;

	public:

		void Add(const int& entity, const T& component = T())
		{
			if (entity >= sparse.size())
				sparse.resize(entity + 1);

			int index = components.size();

			components.push_back(component);
			entities.push_back(entity);

			sparse[entity] = index;
		}

		bool Has(int entity) const
		{
			if (entity >= sparse.size())
				return false;

			int index = sparse[entity];

			return index < entities.size() && entities[index] == entity;
		}

		void Remove(int entity)
		{
			if (!Has(entity))
				return;

			int index = sparse[entity];
			int lastIndex = components.size() - 1;

			components[index] = components[lastIndex];
			entities[index] = entities[lastIndex];

			sparse[entities[index]] = index;

			components.pop_back();
			entities.pop_back();

			sparse[entity] = -1;
		}

		T& Get(const int& entity)
		{
			return components.at(sparse.at(entity));
		}

		T* TryGet(const int& entity)
		{
			if (!Has(entity))
				return nullptr;

			return &components.at(sparse.at(entity));
		}

		vector<T>& GetComponents()
		{
			return components;
		}
	};

	template <typename T>
	struct Storage : IStorage
	{
		ComponentContainer<T> container;
	};
}