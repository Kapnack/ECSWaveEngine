#include "Component.h"

#include "ECS/WObject/WObject.h"
#include "ECS/WaveObject/WaveObject.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/BoundingBoxComp/BoundingBoxComp.h"
#include <ECS/Transform/ECSTransform.h>

namespace WaveEngine
{
	Component::Component()
	{
	}

	Component::~Component()
	{
	}

	void Component::Init()
	{
	}

	void Component::LateInit()
	{
	}

	void Component::Dispose()
	{
	}

	WaveObject& Component::GetWaveObject() const
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetWaveObject(GetID());
	}

	ECSTransform& Component::GetTransform() const
	{
		return GetWaveObject().GetTransform();
	}

	BoundingBoxComp& Component::GetBounds() const
	{
		return GetWaveObject().GetBounds();
	}

	void Component::SetActive(bool isActive)
	{
		this->isActive = isActive;
	}

	bool Component::GetIsActive() const
	{
		return isActive;
	}
}