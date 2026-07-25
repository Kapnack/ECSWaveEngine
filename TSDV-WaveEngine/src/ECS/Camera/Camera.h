#pragma once

#include <glm/fwd.hpp>

#include "Export.h"
#include "ECS/Transform/ECSTransform.h"
#include "ECS/Component/Component.h"
#include "BoundingBox/BoundingBox.h"
#include "Window/Window.h"
#include "EventSystem/EventSystem.h"
#include "Square/Square.h"

namespace WaveEngine
{

	struct Frustum
	{
		glm::vec4 planes[6];
	};

	class EntityManager;
	class EntityFactory;
	class Renderer;

	class Camera : public Component
	{
	private:

		int orderIndex = 0.0f;

		bool shouldUpdateMatrix = true;

		float fovDeg = 45.0f;
		float nearPlane = 0.1f;
		float farPlane = 100.0f;
		float orthoSize = 500.0f;

		float yaw = 0.0f;
		float pitch = 0.0f;

		float movementSpeed = 100.0f;
		float sensitivity = 100.0f;

		bool orthografic = false;

		Frustum frustum;

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		Square viewPortRes;

		Window* GetWindow() const;

		EventSystem* GetEventSystem() const;

		friend class CameraManager;

	protected:

		void CalculateTRS();

	public:

		glm::mat4 GetView() const;
		glm::mat4 GetProjection() const;

		void CalculateMatrixes();

		Frustum GetFrustum() const;

		void ExtractFrustumPlanes();
		bool IsInsideFrustum(const BoundingBox& box) const;

		void SetIsActive(bool isActive) override;

		Camera(unsigned int ID);
		WAVEEXPORT ~Camera();

		WAVEEXPORT void SetOrderIndex(int orderIndex);

		WAVEEXPORT void SetOrthographic(bool value);
		WAVEEXPORT void SetFarPlane(float value);
		WAVEEXPORT void AddToFarPlane(float value);
		WAVEEXPORT void SetNearPlane(float value);
		WAVEEXPORT void AddToNearPlane(float value);
		WAVEEXPORT void SetFovDegree(float value);
		WAVEEXPORT void SetOrthoSize(float value);
		WAVEEXPORT void AddToOrthoSize(float value);

		WAVEEXPORT float GetFarPlane() const;
		WAVEEXPORT float GetNearPlane() const;
		WAVEEXPORT float GetFovDegree() const;
		WAVEEXPORT float GetMovementSpeed() const;
		WAVEEXPORT float GetOrthoSize() const;

		WAVEEXPORT bool GetShouldUpdateMatrix() const;
	};
}