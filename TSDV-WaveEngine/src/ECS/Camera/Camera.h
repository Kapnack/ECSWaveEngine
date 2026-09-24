#pragma once

#include <glm/fwd.hpp>

#include "Export.h"
#include "ECS/Transform/ECSTransform.h"
#include "ECS/Component/Component.h"
#include "BoundingBox/BoundingBox.h"
#include "Window/Window.h"
#include "EventSystem/EventSystem.h"
#include "Square/Square.h"
#include <WaveMath/Matrix4x4/Matrix4x4.h>
#include <WaveMath/Vector4/Vector4.h>

namespace WaveEngine
{

	struct Frustum
	{
		Vector4 planes[6];
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

		Matrix4x4 view;
		Matrix4x4 projection;

		Window* GetWindow() const;

		EventSystem* GetEventSystem() const;

		friend class CameraManager;

	protected:

		void CalculateTRS();

	public:

		Square viewPortRes;

		Camera(unsigned int ID);
		~Camera();

		Matrix4x4 GetView() const;
		Matrix4x4 GetProjection() const;

		void CalculateMatrixes();

		Frustum GetFrustum() const;

		void ExtractFrustumPlanes();
		bool IsInsideFrustum(const BoundingBox& box) const;

		WAVEEXPORT void SetIsActive(bool isActive) override;
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