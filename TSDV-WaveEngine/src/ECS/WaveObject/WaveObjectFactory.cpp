#include "WaveObjectFactory.h"

#include <string>

#include "WaveObject.h"
#include "WaveObjectRegistry.h"
#include "ServiceProvider/Service.h"
#include "ECS/Transform/ECSTransform.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/BoundingBoxComp/BoundingBoxComp.h"
#include "ECS/OrientedBoundingBoxComp/OrientedBoundingBoxComp.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

namespace WaveEngine
{
	WaveObjectFactory::WaveObjectFactory() : Service()
	{

	}

	WaveObjectFactory::~WaveObjectFactory()
	{
	}

	WaveObject& WaveObjectFactory::Instantiate(const char* name)
	{
		WaveObject* newWaveObject = CreateNewWaveObject();

		GetWaveObjectRegistry()->AddObject(newWaveObject, name != nullptr ? name : "WaveObject: " + to_string(currentObjectID) + ".");

		return *newWaveObject;
	}

	WaveObject* WaveObjectFactory::CreateNewWaveObject()
	{
		WaveObject* newWaveObject = new WaveObject(++currentObjectID);

		AddDefaultComponents(*newWaveObject);

		return newWaveObject;
	}

	void WaveObjectFactory::AddDefaultComponents(WaveObject& waveObject)
	{
		waveObject.AddComponent<ECSTransform>();
		waveObject.AddComponent<BoundingBoxComp>();
		waveObject.AddComponent<OrientedBoundingBoxComp>();
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
