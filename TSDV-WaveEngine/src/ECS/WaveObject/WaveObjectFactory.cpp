#include "WaveObjectFactory.h"

#include <string>

#include "ECS/Transform/ECSTransform.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/BoundingBoxComp/BoundingBoxComp.h"
#include "ECS/OrientedBoundingBoxComp/OrientedBoundingBoxComp.h"

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
		newWaveObject->AddComponent<BoundingBoxComp>();
		newWaveObject->AddComponent<OrientedBoundingBoxComp>();

		GetWaveObjectRegistry()->AddObject(newWaveObject, "WaveObject: " + to_string(currentObjectID) + ".");

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
