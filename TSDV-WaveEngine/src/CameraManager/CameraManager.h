#pragma once

#include <vector>

#include "ServiceProvider/Service.h"
#include "ECS/ComponentContainer/ComponentContainer.h"
#include "EventSystem/EventSystem.h"
#include "ECS/Camera/Camera.h"

namespace WaveEngine
{
	class CameraManager final : public Service
	{
	private:

		ComponentContainer<Camera>& GetCameraContainer() const;

		EventSystem* GetEventSystem() const;

		vector<unsigned int> activeCamerasOrder;

	public:

		void Init();
		void LateInit();
		vector<Camera*> GetActiveCameras();
		void Dispose();
	};
}