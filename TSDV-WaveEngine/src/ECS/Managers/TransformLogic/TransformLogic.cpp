#include "TransformLogic.h"

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/Transform/ECSTransform.h"

namespace WaveEngine
{
	TransformLogic::TransformLogic()
	{
	}

	TransformLogic::~TransformLogic()
	{
	}

	void TransformLogic::Init()
	{
	}

	void TransformLogic::Update()
	{
		ComponentContainer<ECSTransform>& transforStorage = GetComponentRegistry()->CreateOrGetComponentStorage<ECSTransform>();
		vector<ECSTransform>& transformComponents = transforStorage.GetComponents();

		for (ECSTransform& transform : transformComponents)
		{
			if (!transform.IsMarkAsDirty())
				continue;

			transform.CalculateTRS();
		}
	}

	ComponentRegistry* TransformLogic::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}
}