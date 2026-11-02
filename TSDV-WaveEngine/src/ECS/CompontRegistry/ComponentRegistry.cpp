#include "ComponentRegistry.h"

#include <vector>
#include <utility>
#include <algorithm>
#include <typeindex>
#include <unordered_map>

#include "ECS/Component/Component.h"
#include "ECS/WaveBehaviour/WaveBehaviour.h"
#include "ECS/ComponentContainer/ComponentContainer.h"

using namespace std;

namespace WaveEngine
{
	ComponentRegistry::ComponentRegistry()
	{
	}

	ComponentRegistry::~ComponentRegistry()
	{
		for (unordered_map<type_index, IStorage*>::iterator storage = storages.begin(); storage != storages.end(); ++storage)
			delete storage->second;
	}

	void ComponentRegistry::Update()
	{
		for (pair<unsigned int, type_index> componentToDestroy : componentsToRemovePerEntity)
			RemoveComponentImmediate(componentToDestroy.first, componentToDestroy.second);

		componentsToRemovePerEntity.clear();
	}

	vector<WaveBehaviour*> ComponentRegistry::GetBehaviours()
	{
		vector<WaveBehaviour*> waveBehavioursType;

		for (const pair<const unsigned int, vector<type_index>>& entry : waveBehavioursByEntityID)
		{
			unsigned int entity = entry.first;
			const vector<type_index>& typeIndices = entry.second;

			for (const type_index& typeIndex : typeIndices)
			{
				unordered_map<type_index, IStorage*>::iterator storageIt = storages.find(typeIndex);
				if (storageIt == storages.end())
					continue;

				if (WaveBehaviour* behaviour = storageIt->second->GetAsWaveBehaviour(entity))
					waveBehavioursType.push_back(behaviour);
			}
		}

		return waveBehavioursType;
	}

	vector<WaveBehaviour*> ComponentRegistry::GetWaveBehaviours(unsigned int entity)
	{
		vector<WaveBehaviour*> waveBehavioursType;

		for (type_index& waveObjectType : waveBehavioursByEntityID[entity])
		{
			unordered_map<type_index, IStorage*>::iterator storageIt = storages.find(waveObjectType);
			if (storageIt == storages.end())
				continue;

			if (WaveBehaviour* behaviour = storageIt->second->GetAsWaveBehaviour(entity))
				waveBehavioursType.push_back(behaviour);
		}

		return waveBehavioursType;
	}

	void ComponentRegistry::RemoveAllComponents(unsigned int entity)
	{
		if (!componentsPerEntity.contains(entity))
			return;

		for (type_index componentType : componentsPerEntity.at(entity))
			RemoveComponentImmediate(entity, componentType);

		componentsPerEntity.erase(entity);
	}

	vector<Component*> ComponentRegistry::GetAll(type_index typeIndex)
	{
		return GetComponentStorage(typeIndex).GetBaseComponents();
	}

	void ComponentRegistry::RemoveComponentImmediate(unsigned int entity, type_index typeIndex)
	{
		if (!storages.contains(typeIndex))
			return;

		static_cast<IStorage*>(storages.at(typeIndex))->Remove(entity);

		if (find(waveBehavioursType.begin(), waveBehavioursType.end(), typeIndex) != waveBehavioursType.end())
			entitiesPerComponents[typeid(WaveBehaviour)].erase(entity);

		vector<type_index>& behaviours = waveBehavioursByEntityID[entity];

		behaviours.erase(remove_if(behaviours.begin(), behaviours.end(), [typeIndex](type_index componentType) { return componentType == typeIndex; }), behaviours.end());
	}

	void ComponentRegistry::RemoveComponent(unsigned int entity, type_index typeIndex)
	{
		if (!storages.contains(typeIndex))
			return;

		pair<unsigned int, type_index> pairToInsert = pair<unsigned int, type_index>(entity, typeIndex);
		componentsToRemovePerEntity.insert(pairToInsert);
	}
}