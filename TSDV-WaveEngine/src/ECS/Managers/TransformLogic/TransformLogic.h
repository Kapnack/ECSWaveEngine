#pragma once

#include "ECS/CompontRegistry/ComponentRegistry.h"

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
	};
}