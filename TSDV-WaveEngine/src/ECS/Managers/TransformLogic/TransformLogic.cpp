#include "TransformLogic.h"

#include <vector>
#include <glm/fwd.hpp>

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/Transform/ECSTransform.h"
#include "ECS/ComponentContainer/ComponentContainer.h"
#include "ECS/WaveObject/WaveObject.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"

namespace WaveEngine
{
	TransformLogic::TransformLogic()
	{
	}

	TransformLogic::~TransformLogic()
	{
	}

	WaveObjectRegistry* TransformLogic::GetWaveObjectRegistry()
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
	}

	void TransformLogic::Init()
	{
	}

	void TransformLogic::Update()
	{
		vector<ECSTransform>& transformComponents =
			GetComponentRegistry()->CreateOrGetComponentStorage<ECSTransform>().GetComponents();

		for (ECSTransform& transform : transformComponents)
		{
			if (!transform.IsDirty())
				continue;

			transform.CalculateTRS();
		}

		for (WaveObject* waveObject : GetWaveObjectRegistry()->GetParentWaveObjects())
			UpdateHierarchy(waveObject->GetTransform());
	}

	void TransformLogic::UpdateHierarchy(ECSTransform& transform,const glm::mat4& parentMatrix)
	{
		glm::mat4 global = parentMatrix * transform.GetLocalModel();

		transform.SetGlobalModel(global);

		for (WaveObject* childWaveObject : transform.GetChilds())
			UpdateHierarchy(childWaveObject->GetTransform(), global);
	}

	ComponentRegistry* TransformLogic::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}
}