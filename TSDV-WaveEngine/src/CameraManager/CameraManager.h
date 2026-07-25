#pragma once

#include <vector>

#include "ServiceProvider/Service.h"
#include "ECS/ComponentContainer/ComponentContainer.h"
#include "EventSystem/EventSystem.h"
#include "ECS/Camera/Camera.h"

namespace WaveEngine
{
	struct CameraChangeActiveStateEvent : public Event
	{
		unsigned int cameraID = Component::NULL_COMPONENT;
		int orderIndex = -1;
		bool isActive = false;

		CameraChangeActiveStateEvent(unsigned int cameraID, int orderIndex, bool isActive)
		{
			this->cameraID = cameraID;
			this->orderIndex = orderIndex;
			this->isActive = isActive;
		}
	};

	class CameraManager final : public Service
	{
	private:

		ComponentContainer<Camera>& GetCameraContainer() const;

		EventSystem* GetEventSystem() const;

		vector<unsigned int> activeCamerasOrder;

		void OnCameraActive(const CameraChangeActiveStateEvent& cameraActiveEvent);

		void RefreshOrderIndices(int from);

	public:

		void Init();
		void LateInit();
		vector<Camera*> GetActiveCameras();
	};
}