#include "WObject.h"

#include "ECS/WaveObject/WaveObject.h"
#include "ModelImporter/ModelImporter.h"
#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine
{
	WaveObject& WObject::Instantiate(const char* modelDir, bool useAbsolutePath, const char* rootName)
	{
		ServiceProvider::Instance().Get<ModelImporter>()->LoadScene(modelDir, useAbsolutePath);
		return *ServiceProvider::Instance().Get<ModelImporter>()->IntantiateModel(rootName);
	}
}