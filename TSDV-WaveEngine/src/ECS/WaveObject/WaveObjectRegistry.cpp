#include "WaveObjectRegistry.h"

#include <string>
#include <vector>
#include <unordered_map>

#include "EventSystem/EventSystem.h"
#include "WaveMath/WaveMath/WaveMath.h"
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

		objectNameSearchStrategy[ObjectNameSearch::Exact].Subscribe(this, &WaveObjectRegistry::HasExactName);
		objectNameSearchStrategy[ObjectNameSearch::Contains].Subscribe(this, &WaveObjectRegistry::ContainsInName);
		objectNameSearchStrategy[ObjectNameSearch::Starts].Subscribe(this, &WaveObjectRegistry::StartsWithName);
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

	unordered_map<unsigned int, WaveObject*>& WaveObjectRegistry::GetWaveObjects()
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

	const vector<WaveObject*> WaveObjectRegistry::GetWaveObject(const char* name, ObjectNameSearch objectNameSearch)
	{
		vector<WaveObject*> waveObjectsToReturn;

		for (unordered_map<string, unsigned int>::iterator iterator = waveObjectsIDByName.begin(); iterator != waveObjectsIDByName.end(); ++iterator)
			if (objectNameSearchStrategy[objectNameSearch].Invoke(name, iterator->first))
				waveObjectsToReturn.push_back(waveObjects[iterator->second]);

		return waveObjectsToReturn;
	}

	//TODO: This should be moved to its own static or service class.
	bool WaveObjectRegistry::HasExactName(const string& name, const string& objectName)
	{
		return name == objectName;
	}

	bool WaveObjectRegistry::ContainsInName(const string& name, const string& objectName)
	{
		int correctInARow = 0;

		for (int i = 0; i < objectName.size(); ++i)
		{
			if (correctInARow == name.size())
				return true;

			if (objectName[i] == name[correctInARow])
				++correctInARow;
			else
				correctInARow = 0;
		}

		return false;
	}

	bool WaveObjectRegistry::StartsWithName(const string& name, const string& objectName)
	{
		for (int i = 0; i < WaveMath::Min(name.size(), objectName.size()); ++i)
		{
			if (name[i] != objectName[i])
				return false;
		}

		return true;
	}

	WaveObject& WaveObjectRegistry::GetWaveObject(unsigned int ID) const
	{
		return *(waveObjects.at(ID));
	}

	WaveObject& WaveObjectRegistry::operator[](unsigned int ID) const
	{
		return GetWaveObject(ID);
	}

	WaveObjectRegistry::~WaveObjectRegistry()
	{
		for (unordered_map<unsigned int, WaveObject*>::iterator iterator = waveObjects.begin(); iterator != waveObjects.end(); ++iterator)
			delete iterator->second;
	}
}