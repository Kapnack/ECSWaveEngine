#pragma once

#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "Renderer/Renderer.h"

namespace WaveEngine
{
	class DrawLogic
	{
	private:

		ComponentRegistry* GetComponentRegistry();

		Renderer* GetRenderer();

	public:

		DrawLogic();
		~DrawLogic();

		void Init();

		void Update();
	};
}