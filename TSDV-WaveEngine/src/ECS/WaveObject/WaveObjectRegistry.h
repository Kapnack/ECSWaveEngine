#pragma once

#include <vector>
#include <map>

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

		map<unsigned int, WaveObject*> waveObjects;
		map<string, unsigned int> waveObjectsIDByName;
		map<unsigned int, string> waveObjectsNamesByID;

		map<ObjectNameSearch, Func<bool, const string_view, const string_view>> objectNameSearchStrategy;

		friend class BaseGame;
		friend class ServiceProvider;

		void OnObjectBecameParent(const ObjectBecameParentEvent& objectBecameParentEvent);
		void OnObjectBecameChild(const ObjectBecameChildEvent& objectBecameChildEvent);
		void OnObjectChangesName(const ObjectChangeName& objectChangeNameEvent);

		EventSystem* GetEventSystem();

		bool CheckObjecNameExact(const string_view name, const string_view lookingFor);

	public:

		WaveObjectRegistry();
		~WaveObjectRegistry();

		void Init();

		void AddObject(WaveObject*& newWaveObject, const string_view name);

		string GetObjectName(unsigned int ID);

		map<unsigned int, WaveObject*>& GetWaveObjects();

		vector<WaveObject*> GetParentWaveObjects();

		const vector<WaveObject*>& GetWaveObject(const string_view name, ObjectNameSearch objectNameSearch = ObjectNameSearch::Exact);

		WaveObject& GetWaveObject(unsigned int ID);
	};

}