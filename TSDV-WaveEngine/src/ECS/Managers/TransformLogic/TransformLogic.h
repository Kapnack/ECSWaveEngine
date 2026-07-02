#pragma once

#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/Transform/ECSTransform.h"

#include <glm/fwd.hpp>

namespace WaveEngine
{
	class TransformLogic
	{
	private:

		WaveObjectRegistry* GetWaveObjectRegistry();

		void UpdateHierarchy(ECSTransform& transform, const glm::mat4& parentMatrix = glm::mat4(1.0f));

	public:

		TransformLogic();
		~TransformLogic();

		void Init();

		void Update();

		ComponentRegistry* GetComponentRegistry();

	};
}