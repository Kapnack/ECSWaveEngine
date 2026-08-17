#include "CameraManager.h"

#include <vector>

#include "ECS/ComponentContainer/ComponentContainer.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ServiceProvider/ServiceProvider.h"
#include "EventSystem/EventSystem.h"
#include "ECS/Camera/Camera.h"
#include <algorithm>
#include <iterator>

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

	Window* CameraManager::GetWindow() const
	{
		return ServiceProvider::Instance().Get<Window>();
	}

	void CameraManager::Init()
	{
		GetEventSystem()->Subscribe<CameraChangeActiveStateEvent>(this, &CameraManager::OnCameraActive);
	}

	void CameraManager::LateInit()
	{
	}

	void CameraManager::Update()
	{
		usableCameras.clear();

		Square camerasTotalRes;

		for (unsigned int cameraID : activeCamerasOrder)
		{
			Camera& camera = GetCameraContainer().Get(cameraID);

			camera.CalculateMatrixes();
			usableCameras.push_back(&camera);
			camerasTotalRes.Encapsulate(Square(camera.viewPortRes.GetCenter(), camera.viewPortRes.GetSize() * GetWindow()->GetSize()));

			if (camerasTotalRes.GetSize() >= GetWindow()->GetSize())
				break;
		}
	}

	void CameraManager::OnCameraActive(const CameraChangeActiveStateEvent& event)
	{
		if (!event.isActive)
		{
			const vector<unsigned int>::iterator it = find(activeCamerasOrder.begin(), activeCamerasOrder.end(), event.cameraID);

			if (it == activeCamerasOrder.end())
				return;

			const int index = static_cast<int>(distance(activeCamerasOrder.begin(), it));

			activeCamerasOrder.erase(it);
			RefreshOrderIndices(index);
			return;
		}

		if (find(activeCamerasOrder.begin(), activeCamerasOrder.end(), event.cameraID) != activeCamerasOrder.end())
			return;

		const int index = min<int>(event.orderIndex, activeCamerasOrder.size());
		activeCamerasOrder.insert(activeCamerasOrder.begin() + index, event.cameraID);
		RefreshOrderIndices(index);
	}

	void CameraManager::RefreshOrderIndices(int from)
	{
		for (int i = from; i < activeCamerasOrder.size(); ++i)
			GetCameraContainer().Get(activeCamerasOrder[i]).orderIndex = i;
	}

	const vector<Camera*>& CameraManager::GetActiveCameras()
	{
		return usableCameras;
	}
}