#pragma once

#include "Renderer/Renderer.h"
#include "ECS/Camera/Camera.h"
#include "ECS/WaveObject/WaveObject.h"
#include "CameraManager/CameraManager.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

namespace WaveEngine
{
	class DrawLogic
	{
	private:

		ComponentRegistry* GetComponentRegistry();

		Renderer* GetRenderer();

		void CheckChildsAreInFrustum(WaveObject& waveObject, Camera& camera);

		CameraManager* GetCameraManager() const;

	public:

		DrawLogic();
		~DrawLogic();

		void Init();

		void Update();
	};
}