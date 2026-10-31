#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "EventSystem/Func.h"
#include "ServiceProvider/Service.h"
#include "EventSystem/EventSystem.h"
#include "Events/ObjectChangeName.h"
#include "ECS/Component/Component.h"
#include "Events/ObjectBecameChildEvent.h"
#include "Events/ObjectBecameParentEvent.h"

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

	class WaveObject;

	class WaveObjectRegistry : Service
	{
	private:

		vector<unsigned int> parentsWaveObjects;
		unordered_set<unsigned int> toDestroy;

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

		void Update();

		void ToDestroy(WaveObject* waveObject);
		void Destroy(WaveObject* waveObject);

		WaveObject& operator[](unsigned int ID) const;
	};

}