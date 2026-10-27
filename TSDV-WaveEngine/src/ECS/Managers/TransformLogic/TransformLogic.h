#pragma once

#include "ECS/Transform/ECSTransform.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include <WaveMath/Matrix4x4/Matrix4x4.h>

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