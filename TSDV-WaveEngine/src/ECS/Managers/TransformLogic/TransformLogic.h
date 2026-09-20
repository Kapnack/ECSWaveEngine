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

		void UpdateHierarchy(ECSTransform& transform, const Matrix4x4& parentMatrix = Matrix4x4::Identity());

	public:

		TransformLogic();
		~TransformLogic();

		void Init();

		void Update();

		ComponentRegistry* GetComponentRegistry();

	};
}