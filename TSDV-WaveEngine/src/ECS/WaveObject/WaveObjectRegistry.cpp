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

	WaveObjectRegistry::~WaveObjectRegistry()
	{
		for (map<unsigned int, WaveObject*>::iterator iterator = waveObjects.begin(); iterator != waveObjects.end(); ++iterator)
			delete iterator->second;
	}
}