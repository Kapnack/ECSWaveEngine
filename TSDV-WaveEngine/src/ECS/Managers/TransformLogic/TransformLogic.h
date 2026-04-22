#pragma once

#include "ECS/CompontRegistry/ComponentRegistry.h"
#include <ECS/ComponentContainer/ComponentContainer.h>
#include <glm/fwd.hpp>
#include <ECS/Transform/ECSTransform.h>

namespace WaveEngine
{
	class TransformLogic
	{
	public:

		TransformLogic();
		~TransformLogic();

		void Init();

		void Update();

		ComponentRegistry* GetComponentRegistry();

		void UpdateHierarchy(
			ComponentContainer<ECSTransform>& storage,
			ECSTransform& transform,
			const glm::mat4& parentMatrix);
	};
}