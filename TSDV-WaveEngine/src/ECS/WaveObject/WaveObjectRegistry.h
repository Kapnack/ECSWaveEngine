#pragma once

#include <vector>
#include <unordered_map>

#include "ServiceProvider/Service.h"
#include "ServiceProvider/ServiceProvider.h"
#include "WaveObject.h"
#include "EventSystem/Func.h"
#include "EventSystem/Event.h"
#include <EventSystem/EventSystem.h>
#include "Events/ObjectBecameParentEvent.h"
#include "Events/ObjectChangeName.h"
#include "Events/ObjectBecameChildEvent.h"

using namespace std;

class BaseGame;
class ServiceProvider;

namespace WaveEngine
{
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

		friend class Engine;
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

		static WaveObjectRegistry& Get();

		void AddObject(WaveObject*& newWaveObject, const string_view name);

		string GetObjectName(unsigned int ID);

		unordered_map<unsigned int, WaveObject*>& GetWaveObjects();

		vector<WaveObject*> GetParentWaveObjects();

		const vector<WaveObject*> GetWaveObject(const char* name, ObjectNameSearch objectNameSearch = ObjectNameSearch::Exact);

		WaveObject& GetWaveObject(unsigned int ID) const;

		WaveObject& operator[](unsigned int ID) const;
	};

}