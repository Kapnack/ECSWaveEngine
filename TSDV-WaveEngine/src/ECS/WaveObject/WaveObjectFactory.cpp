#include "WaveObjectFactory.h"

#include <string>

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/Mesh/MeshID.h"

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
		newWaveObject->AddComponent<MeshID>();

		newWaveObject->name = "WaveObject: " + to_string(currentObjectID) + ".";

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
