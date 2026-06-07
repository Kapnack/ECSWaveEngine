#include "WaveObjectRegistry.h"

namespace WaveEngine
{
	WaveObjectRegistry::WaveObjectRegistry() : Service()
	{
	}

	void WaveObjectRegistry::AddObject(WaveObject*& newWaveObject)
	{
		waveObjects[newWaveObject->GetID()] = newWaveObject;
	}

	map<unsigned int, WaveObject*>& WaveObjectRegistry::GetWaveObjects()
	{
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