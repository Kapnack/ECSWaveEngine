#pragma once

#include <vector>
#include <map>

#include "ServiceProvider/Service.h"
#include "WaveObject.h"
#include "EventSystem/Event.h"
#include <EventSystem/EventSystem.h>

using namespace std;

class BaseGame;
class ServiceProvider;

namespace WaveEngine
{
	struct ObjectBecameParentEvent : Event
	{
		unsigned int waveObjectID = 0;

		ObjectBecameParentEvent()
		{ }

		ObjectBecameParentEvent(unsigned int waveObjectID)
		{
			this->waveObjectID = waveObjectID;
		}

		void Reset() override
		{
			waveObjectID = 0;
		}
	};

	struct ObjectBecameChildEvent : Event
	{
		unsigned int waveObjectID = 0;

		ObjectBecameChildEvent()
		{
		}

		ObjectBecameChildEvent(unsigned int waveObjectID)
		{
			this->waveObjectID = waveObjectID;
		}

		void Reset() override
		{
			waveObjectID = 0;
		}
	};

	struct ObjectChangeName : Event
	{
		unsigned int entityID = WaveObject::NULL_OBJECT;
		string oldName = "";
		string newName = "";

		ObjectChangeName()
		{
		}

		ObjectChangeName(unsigned int entityID, string oldName, string newName)
		{
			this->entityID = entityID;
			this->oldName = oldName;
			this->newName = newName;
		}

		void Reset() override
		{
			entityID = WaveObject::NULL_OBJECT;
			oldName = "";
			newName = "";
		}
	};

	class WaveObjectRegistry : Service
	{
	private:

		vector<unsigned int> parentsWaveObjects;

		map<unsigned int, WaveObject*> waveObjects;
		map<string, unsigned int> waveObjectsIDByName;

		friend class BaseGame;
		friend class ServiceProvider;

		void OnObjectBecameParent(const ObjectBecameParentEvent& objectBecameParentEvent);
		void OnObjectBecameChild(const ObjectBecameChildEvent& objectBecameChildEvent);
		void OnObjectChangesName(const ObjectChangeName& objectChangeNameEvent);

		EventSystem* GetEventSystem();

	public:

		WaveObjectRegistry();
		~WaveObjectRegistry();

		void Init();

		void AddObject(WaveObject*& newWaveObject);

		map<unsigned int, WaveObject*>& GetWaveObjects();

		vector<WaveObject*> GetParentWaveObjects();

		WaveObject& GetWaveObject(const unsigned int& ID);
	};

}