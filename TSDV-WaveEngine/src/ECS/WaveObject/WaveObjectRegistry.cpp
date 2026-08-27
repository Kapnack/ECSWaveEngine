#include "WaveObjectRegistry.h"

#include <string>
#include <vector>
#include <map>

#include "EventSystem/EventSystem.h"
#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine
{
	WaveObjectRegistry::WaveObjectRegistry() : Service()
	{
	}

	void WaveObjectRegistry::Init()
	{
		GetEventSystem()->Subscribe<ObjectBecameParentEvent>(this, &WaveObjectRegistry::OnObjectBecameParent);
		GetEventSystem()->Subscribe<ObjectBecameChildEvent>(this, &WaveObjectRegistry::OnObjectBecameChild);
		GetEventSystem()->Subscribe<ObjectChangeName>(this, &WaveObjectRegistry::OnObjectChangesName);

		//objectNameSearchStrategy[ObjectNameSearch::Exact].Subscribe(this, &WaveObjectRegistry::CheckObjecNameExact);
	}

	void WaveObjectRegistry::OnObjectBecameParent(const ObjectBecameParentEvent& objectBecameParentEvent)
	{
		for (unsigned int objectsID : parentsWaveObjects)
			if (objectsID == objectBecameParentEvent.waveObjectID)
				return;

		parentsWaveObjects.push_back(objectBecameParentEvent.waveObjectID);
	}

	void WaveObjectRegistry::OnObjectBecameChild(const ObjectBecameChildEvent& objectBecameChildEvent)
	{
		erase(parentsWaveObjects, objectBecameChildEvent.waveObjectID);
	}

	void WaveObjectRegistry::OnObjectChangesName(const ObjectChangeName& objectChangeNameEvent)
	{
		string newName = objectChangeNameEvent.newName;
		int attemps = 0;

		while (waveObjectsIDByName.contains(newName))
			newName = objectChangeNameEvent.newName + '_' + to_string(++attemps);

		waveObjectsIDByName.erase(waveObjectsNamesByID[objectChangeNameEvent.entityID]);

		waveObjectsIDByName[newName] = objectChangeNameEvent.entityID;
		waveObjectsNamesByID[objectChangeNameEvent.entityID] = newName;
	}

	EventSystem* WaveObjectRegistry::GetEventSystem()
	{
		return ServiceProvider::Instance().Get<EventSystem>();
	}

	bool WaveObjectRegistry::CheckObjecNameExact(const string_view name, const string_view lookingFor)
	{
		return (name.data() == lookingFor.data());
	}

	void WaveObjectRegistry::AddObject(WaveObject*& newWaveObject, const string_view name)
	{
		const int entityID = newWaveObject->GetID();

		waveObjects[entityID] = newWaveObject;

		const string entityName = name.data();

		waveObjectsIDByName[entityName] = entityID;
		waveObjectsNamesByID[entityID] = entityName;
	}

	string WaveObjectRegistry::GetObjectName(unsigned int ID)
	{
		return waveObjectsNamesByID[ID];
	}

	map<unsigned int, WaveObject*>& WaveObjectRegistry::GetWaveObjects()
	{
		return waveObjects;
	}

	vector<WaveObject*> WaveObjectRegistry::GetParentWaveObjects()
	{
		vector<WaveObject*> waveObjects;

		for (unsigned int waveObjectID : parentsWaveObjects)
			waveObjects.push_back(&GetWaveObject(waveObjectID));

		return waveObjects;
	}

	const vector<WaveObject*>& WaveObjectRegistry::GetWaveObject(const string_view name, ObjectNameSearch objectNameSearch)
	{
		vector<WaveObject*> waveObjectsToReturn;

		for (map<string, unsigned int>::iterator iterator = waveObjectsIDByName.begin(); iterator != waveObjectsIDByName.end(); ++iterator)
			//if (objectNameSearchStrategy[objectNameSearch].Invoke(iterator->first, name))
				waveObjectsToReturn.push_back(waveObjects[iterator->second]);

		return waveObjectsToReturn;
	}

	WaveObject& WaveObjectRegistry::GetWaveObject(unsigned int ID)
	{
		return *waveObjects.at(ID);
	}

	WaveObjectRegistry::~WaveObjectRegistry()
	{
		for (map<unsigned int, WaveObject*>::iterator iterator = waveObjects.begin(); iterator != waveObjects.end(); ++iterator)
			delete iterator->second;
	}
}