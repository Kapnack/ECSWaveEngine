#pragma once

#include "ServiceProvider/Service.h"

#include <vector>
#include <utility>
#include <typeindex>
#include <unordered_map>

#include "ECS/ComponentContainer/IStorage.h"
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

		template<typename T>
		T& AddComponent(unsigned int entity);

		template<typename T>
		bool HasStorage();

		template<typename T>
		bool Has(unsigned int entity);

		template<typename T>
		T& Get(unsigned int entity);

		inline vector<WaveBehaviour*> GetBehaviours();

		template<typename T>
		T* TryGet(unsigned int entity);

		template<typename T>
		void RemoveComponent(unsigned int entity);

		template<typename T>
		ComponentContainer<T>& GetComponentStorage();

		template<typename T>
		ComponentContainer<T>& CreateOrGetComponentStorage();

		template<typename T>
		ComponentContainer<T>* TryGetComponentStorage();

		template<typename T>
		T& GetComponent(unsigned int entity);
	};
}