#include "WObject.h"

#include "ECS/WaveObject/WaveObject.h"
#include "ModelImporter/ModelImporter.h"
#include "ECS/WaveObject/WaveObjectFactory.h"
#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine
{
	WaveObject& WObject::Instantiate(const char* name)
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>()->Instantiate(name);
	}

	WaveObject& WObject::InstantiateModel(const char* modelDir, bool useAbsolutePath, const char* rootName)
	{
		ServiceProvider::Instance().Get<ModelImporter>()->LoadScene(modelDir, useAbsolutePath);
		return *ServiceProvider::Instance().Get<ModelImporter>()->IntantiateModel(rootName);
	}
}