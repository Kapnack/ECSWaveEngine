#pragma once

#include "ServiceProvider/Service.h"

#include <vector>
#include <utility>
#include <typeindex>
#include <unordered_map>

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
		unordered_map<unsigned int, vector<type_index>> waveBehavioursByEntityID;

	public:

		ComponentRegistry();
		~ComponentRegistry();

		template<TypeComponent T>
		T& AddComponent(unsigned int entity);

		template<TypeComponent T>
		bool HasStorage();
		template<TypeComponent T>
		bool Has(unsigned int entity);
		template<TypeComponent T>
		T& Get(unsigned int entity);

		vector<WaveBehaviour*> GetBehaviours();

		template<TypeComponent T>
		T* TryGet(unsigned int entity);
		template<TypeComponent T>
		void RemoveComponent(unsigned int entity);

		template<TypeComponent T>
		ComponentContainer<T>& GetComponentStorage();
		template<TypeComponent T>
		ComponentContainer<T>& CreateOrGetComponentStorage();

		template<TypeComponent T>
		ComponentContainer<T>* TryGetComponentStorage();

		template<TypeComponent T>
		T& GetComponent(unsigned int entity);
	};
}