#pragma once


#include "Export.h"
#include "Window/Window.h"
#include "Square/Square.h"
#include "BoundingBox/BoundingBox.h"
#include "ECS/Component/Component.h"
#include "EventSystem/EventSystem.h"
#include "WaveMath/Vector4/Vector4.h"
#include "WaveMath/Matrix4x4/Matrix4x4.h"

namespace WaveEngine
{
	struct WAVEEXPORT Frustum
	{
		Vector4 planes[6];
	};

	class EntityManager;
	class EntityFactory;
	class Renderer;

	class WAVEEXPORT Camera : public Component
	{
	private:

		int orderIndex = 0;

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
		bool IsOrthografic() const;

		void SetIsActive(bool isActive) override;
		void SetOrderIndex(int orderIndex);

		void SetOrthographic(bool value);
		void SetFarPlane(float value);
		void AddToFarPlane(float value);
		void SetNearPlane(float value);
		void AddToNearPlane(float value);
		void SetFovDegree(float value);
		void SetOrthoSize(float value);
		void AddToOrthoSize(float value);

		float GetFarPlane() const;
		float GetNearPlane() const;
		float GetFovDegree() const;
		float GetMovementSpeed() const;
		float GetOrthoSize() const;

		bool GetShouldUpdateMatrix() const;
	};
}