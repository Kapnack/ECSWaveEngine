#pragma once

#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "Renderer/Renderer.h"
#include "ECS/Camera/Camera.h"
#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	class DrawLogic
	{
	private:

		ComponentRegistry* GetComponentRegistry();

		Renderer* GetRenderer();

		void CheckChildsAreInFrustum(WaveObject& waveObject, Camera& camera);

	public:

		DrawLogic();
		~DrawLogic();

		void Init();

		void Update();
	};
}