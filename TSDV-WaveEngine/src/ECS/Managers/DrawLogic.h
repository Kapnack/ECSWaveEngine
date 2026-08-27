#pragma once

#include "Renderer/Renderer.h"
#include "ECS/Camera/Camera.h"
#include "ECS/WaveObject/WaveObject.h"
#include "CameraManager/CameraManager.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "BinarySpacePartition/BinarySpacePartition.h"

namespace WaveEngine
{
	class DrawLogic
	{
	private:

		ComponentRegistry* GetComponentRegistry();

		Renderer* GetRenderer() const;

		void CheckChildsAreInFrustum(WaveObject& waveObject, Camera& camera);

		CameraManager* GetCameraManager() const;

		BinarySpacePartition* GetBinarySpacePartition() const;

	public:

		DrawLogic();
		~DrawLogic();

		void Init();

		void Update();
	};
}