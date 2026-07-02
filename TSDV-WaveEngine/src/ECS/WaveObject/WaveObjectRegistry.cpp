#include "WaveObjectRegistry.h"

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

	EventSystem* WaveObjectRegistry::GetEventSystem()
	{
		return ServiceProvider::Instance().Get<EventSystem>();
	}

	void WaveObjectRegistry::AddObject(WaveObject*& newWaveObject)
	{
		waveObjects[newWaveObject->GetID()] = newWaveObject;
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

	WaveObject& WaveObjectRegistry::GetWaveObject(const unsigned int& ID)
	{
		return *waveObjects.at(ID);
	}

	WaveObjectRegistry::~WaveObjectRegistry()
	{
		for (map<unsigned int, WaveObject*>::iterator iterator = waveObjects.begin(); iterator != waveObjects.end(); ++iterator)
			delete iterator->second;
	}
}