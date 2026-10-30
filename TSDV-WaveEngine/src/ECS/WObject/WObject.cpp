#include "WObject.h"

#include "ECS/WaveObject/WaveObject.h"
#include "ModelImporter/ModelImporter.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"

namespace WaveEngine
{
	WaveObject& WObject::Instantiate(const char* modelDir, bool useAbsolutePath, const char* rootName)
	{
		ServiceProvider::Instance().Get<ModelImporter>()->LoadScene(modelDir, useAbsolutePath);
		return *ServiceProvider::Instance().Get<ModelImporter>()->IntantiateModel(rootName);
	}

	void WObject::Destroy(WaveObject* waveObject)
	{
		ServiceProvider::Instance().Get<WaveObjectRegistry>()->Destroy(waveObject);
	}
}