#include "WaveObjectFactory.h"

#include <string>

#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine
{
	WaveObjectFactory::WaveObjectFactory() : Service()
	{

	}

	WaveObjectFactory::~WaveObjectFactory()
	{
	}

	WaveObject& WaveObjectFactory::Instantiate()
	{
		WaveObject* newWaveObject = new WaveObject(++currentObjectID);

		newWaveObject->AddComponent<ECSTransform>();

		newWaveObject->SetName("WaveObject: " + to_string(currentObjectID) + ".");
		 
		GetWaveObjectRegistry()->AddObject(newWaveObject);

		return *newWaveObject;
	}

	ComponentRegistry* WaveObjectFactory::GetComponenetRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}

	WaveObjectRegistry* WaveObjectFactory::GetWaveObjectRegistry()
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
	}
}
