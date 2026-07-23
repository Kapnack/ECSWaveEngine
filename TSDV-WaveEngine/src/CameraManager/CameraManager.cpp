#include "CameraManager.h"

#include <vector>

#include "ECS/ComponentContainer/ComponentContainer.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/Component/Component.h"
#include "EventSystem/EventSystem.h"
#include "ECS/Camera/Camera.h"
#include "EventSystem/Event.h"

namespace WaveEngine
{
	ComponentContainer<Camera>& CameraManager::GetCameraContainer() const
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>()->CreateOrGetComponentStorage<Camera>();
	}

	EventSystem* CameraManager::GetEventSystem() const
	{
		return ServiceProvider::Instance().Get<EventSystem>();
	}

	vector<Camera*> CameraManager::GetActiveCameras()
	{
		vector<Camera*> cameras;

		for (unsigned int cameraID : activeCamerasOrder)
			cameras.push_back(&GetCameraContainer().Get(cameraID));

		return cameras;
	}
}