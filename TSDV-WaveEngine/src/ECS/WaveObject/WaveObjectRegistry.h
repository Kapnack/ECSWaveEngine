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

	class WaveObjectRegistry : Service
	{
	private:

		vector<unsigned int> parentsWaveObjects;

		map<unsigned int, WaveObject*> waveObjects;

		friend class BaseGame;
		friend class ServiceProvider;

		void OnObjectBecameParent(const ObjectBecameParentEvent& objectBecameParentEvent);
		void OnObjectBecameChild(const ObjectBecameChildEvent& objectBecameChildEvent);

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