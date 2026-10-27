#pragma once

#include <vector>
#include <Window/Window.h>

#include "ECS/Camera/Camera.h"
#include "EventSystem/Event.h"
#include "ECS/Component/Component.h"
#include "ServiceProvider/Service.h"
#include "EventSystem/EventSystem.h"
#include "ECS/ComponentContainer/ComponentContainer.h"

namespace WaveEngine
{
	struct CameraChangeActiveStateEvent : public Event
	{
		unsigned int cameraID = Component::NULL_COMPONENT;
		int orderIndex = -1;
		bool isActive = false;

		CameraChangeActiveStateEvent() : Event()
		{
		}

		CameraChangeActiveStateEvent(unsigned int cameraID, int orderIndex, bool isActive) : Event()
		{
			this->cameraID = cameraID;
			this->orderIndex = orderIndex;
			this->isActive = isActive;
		}

		void Reset() override
		{
			cameraID = Component::NULL_COMPONENT;
			orderIndex = -1;
			isActive = false;
		}
	};

	class CameraManager final : public Service
	{
	private:

		ComponentContainer<Camera>& GetCameraContainer() const;

		EventSystem* GetEventSystem() const;

		Window* GetWindow() const;

		vector<unsigned int> activeCamerasOrder;
		vector<Camera*> usableCameras;

		void OnCameraActive(const CameraChangeActiveStateEvent& cameraActiveEvent);

		void RefreshOrderIndices(int from);

	public:

		void Init();
		void LateInit();
		void Update();
		const vector<Camera*>& GetActiveCameras();
	};
}