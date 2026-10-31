#include "WObject.h"

#include <typeindex>

#include "ECS/Component/Component.h"
#include "ECS/WaveObject/WaveObject.h"
#include "ModelImporter/ModelImporter.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

namespace WaveEngine
{
	WObject::WObject()
	{
	}

	WObject::~WObject()
	{
	}

	WaveObject& WObject::Instantiate(const char* modelDir, bool useAbsolutePath, const char* rootName)
	{
		ServiceProvider::Instance().Get<ModelImporter>()->LoadScene(modelDir, useAbsolutePath);
		return *ServiceProvider::Instance().Get<ModelImporter>()->IntantiateModel(rootName);
	}

	void WObject::Destroy(WObject* wObject)
	{
		if (!wObject)
			return;

		if (Component* component = dynamic_cast<Component*>(wObject))
			Destroy(component);
		else if (WaveObject* waveObject = dynamic_cast<WaveObject*>(wObject))
			Destroy(waveObject);
	}

	void WObject::Destroy(Component* component)
	{
		if (!component)
			return;

		ServiceProvider::Instance().Get<ComponentRegistry>()->RemoveComponent(component->GetID(), typeid(*component));
	}

	void WObject::Destroy(WaveObject* waveObject)
	{
		if (!waveObject)
			return;

		ServiceProvider::Instance().Get<WaveObjectRegistry>()->Destroy(waveObject);
	}
}