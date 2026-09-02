#pragma once

#include <vector>
#include <unordered_map>

#include "ServiceProvider/Service.h"
#include "WaveObject.h"
#include "EventSystem/Func.h"
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
		{
		}

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
		string newName = "";

		ObjectChangeName()
		{
		}

		ObjectChangeName(unsigned int entityID, string newName)
		{
			this->entityID = entityID;
			this->newName = newName;
		}

		void Reset() override
		{
			entityID = WaveObject::NULL_OBJECT;
			newName = "";
		}
	};

	enum class ObjectNameSearch
	{
		Exact,
		Contains,
		Starts,
		Ends
	};

	class WaveObjectRegistry : Service
	{
	private:

		vector<unsigned int> parentsWaveObjects;

		unordered_map<unsigned int, WaveObject*> waveObjects;
		unordered_map<string, unsigned int> waveObjectsIDByName;
		unordered_map<unsigned int, string> waveObjectsNamesByID;

		unordered_map<ObjectNameSearch, Func<bool, const string&, const string&>> objectNameSearchStrategy;

		friend class BaseGame;
		friend class ServiceProvider;

		void OnObjectBecameParent(const ObjectBecameParentEvent& objectBecameParentEvent);
		void OnObjectBecameChild(const ObjectBecameChildEvent& objectBecameChildEvent);
		void OnObjectChangesName(const ObjectChangeName& objectChangeNameEvent);

		EventSystem* GetEventSystem();

		bool HasExactName(const string& name, const string& objectName);
		bool ContainsInName(const string& name, const string& objectName);
		bool StartsWithName(const string& name, const string& objectName);

	public:

		WaveObjectRegistry();
		~WaveObjectRegistry();

		void Init();

		void AddObject(WaveObject*& newWaveObject, const string_view name);

		string GetObjectName(unsigned int ID);

		unordered_map<unsigned int, WaveObject*>& GetWaveObjects();

		vector<WaveObject*> GetParentWaveObjects();

		const vector<WaveObject*> GetWaveObject(const char* name, ObjectNameSearch objectNameSearch = ObjectNameSearch::Exact);

		WaveObject& GetWaveObject(unsigned int ID);
	};

}