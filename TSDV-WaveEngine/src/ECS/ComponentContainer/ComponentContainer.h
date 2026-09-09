#pragma once

#include <vector>
#include <type_traits>

#include "IStorage.h"
#include "ECS/Component/TypeComponent.h"

using namespace std;

namespace WaveEngine
{
	class WaveBehaviour;

	template <TypeComponent T>
	class ComponentContainer : public IStorage
	{
	private:

		vector<T> components;
		vector<unsigned int> entities;
		vector<unsigned int> componentByEntity;

	public:

		void Add(unsigned int entity);

		bool Has(unsigned int entity) const;

		void Remove(unsigned int entity);

		T& Get(unsigned int entity);

		T& GetFirst();

		T* TryGet(unsigned int entity);

		vector<T>& GetComponents();

		const vector<unsigned int>& GetEntities() const;

		WaveBehaviour* GetAsWaveBehaviour(unsigned int entity) override;


		T& operator[](unsigned int entityID);
	};
}

#include "ComponentContainer.tpp"