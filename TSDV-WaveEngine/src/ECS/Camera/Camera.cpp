#include "Camera.h"

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include "ServiceProvider/ServiceProvider.h"
#include "../Transform/ECSTransform.h"
#include <CameraManager/CameraManager.h>
#include <WaveMath/WaveMath/WaveMath.h>

namespace WaveEngine
{
	Camera::Camera(const unsigned int ID) : Component(ID)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::SetIsActive(bool isActive)
	{
		Component::SetIsActive(isActive);
		SetOrderIndex(orderIndex);
	}

	void Camera::SetOrderIndex(int orderIndex)
	{
		this->orderIndex = orderIndex;
		GetEventSystem()->Invoke<CameraChangeActiveStateEvent>(GetID(), orderIndex, GetIsActive());
	}

	void Camera::CalculateTRS()
	{
		shouldUpdateMatrix = true;
	}

	void Camera::SetOrthographic(const bool value)
	{
		orthografic = value;

		CalculateTRS();
	}

	void Camera::SetFarPlane(const float value)
	{
		farPlane = value;

		shouldUpdateMatrix = true;
	}

	void Camera::AddToFarPlane(const float value)
	{
		farPlane += value;

		CalculateTRS();
	}

	void Camera::SetNearPlane(const float value)
	{
		nearPlane = value;

		CalculateTRS();
	}

	void Camera::AddToNearPlane(const float value)
	{
		nearPlane += value;

		CalculateTRS();
	}

	void Camera::SetFovDegree(const float value)
	{
		fovDeg = value;

		CalculateTRS();
	}

	void Camera::SetOrthoSize(const float value)
	{
		orthoSize = value;
	}

	void Camera::AddToOrthoSize(const float value)
	{
		orthoSize += value;
	}

	Matrix4x4 Camera::GetView() const
	{
		return view;
	}

	Matrix4x4 Camera::GetProjection() const
	{
		return projection;
	}

	float Camera::GetFarPlane() const
	{
		return farPlane;
	}

	float Camera::GetNearPlane() const
	{
		return nearPlane;
	}

	float Camera::GetFovDegree() const
	{
		return fovDeg;
	}

	float Camera::GetMovementSpeed() const
	{
		return movementSpeed;
	}

	float Camera::GetOrthoSize() const
	{
		return orthoSize;
	}

	bool Camera::GetShouldUpdateMatrix() const
	{
		return shouldUpdateMatrix;
	}

	void Camera::CalculateMatrixes()
	{
		float aspect =
			static_cast<float>(GetWindow()->GetWidth()) /
			static_cast<float>(GetWindow()->GetHeight());

		ECSTransform& transform = GetTransform();

		Vector3 pos = transform.GetPosition();

		Matrix4x4 rotationMatrix = transform.GetGlobalModel().GetRotationMatrix();

		Vector3 forward = transform.GetForward();
		Vector3 up = transform.GetUp();

		float halfHeight = orthoSize;
		float halfWidth = orthoSize * aspect;

		view = Matrix4x4::CreateLookAt(pos, pos + forward, up);

		projection = orthografic ?
			Matrix4x4::CreateOrthographic(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane)
			:
			Matrix4x4::CreatePerspective(WaveMath::Deg2Rad(fovDeg), aspect, nearPlane, farPlane);

		ExtractFrustumPlanes();
		shouldUpdateMatrix = false;
	}

	Frustum Camera::GetFrustum() const
	{
		return frustum;
	}

	void Camera::ExtractFrustumPlanes()
	{
		Matrix4x4 vp = projection * view;

		frustum.planes[0] = Vector4(vp.m30 + vp.m00, vp.m31 + vp.m01, vp.m32 + vp.m02, vp.m33 + vp.m03); // Left
		frustum.planes[1] = Vector4(vp.m30 - vp.m00, vp.m31 - vp.m01, vp.m32 - vp.m02, vp.m33 - vp.m03); // Right
		frustum.planes[2] = Vector4(vp.m30 + vp.m10, vp.m31 + vp.m11, vp.m32 + vp.m12, vp.m33 + vp.m13); // Bottom
		frustum.planes[3] = Vector4(vp.m30 - vp.m10, vp.m31 - vp.m11, vp.m32 - vp.m12, vp.m33 - vp.m13); // Top
		frustum.planes[4] = Vector4(vp.m30 + vp.m20, vp.m31 + vp.m21, vp.m32 + vp.m22, vp.m33 + vp.m23); // Near
		frustum.planes[5] = Vector4(vp.m30 - vp.m20, vp.m31 - vp.m21, vp.m32 - vp.m22, vp.m33 - vp.m23); // Far

		for (Vector4& plane : frustum.planes)
			plane.Normalized();
	}

	bool Camera::IsInsideFrustum(const BoundingBox& box) const
	{
		Vector3 positive;

		for (const Vector4& plane : frustum.planes)
		{
			positive =
			{
				plane.x >= 0 ? box.GetMax().x : box.GetMin().x,
				plane.y >= 0 ? box.GetMax().y : box.GetMin().y,
				plane.z >= 0 ? box.GetMax().z : box.GetMin().z
			};

			if (Vector3::Dot(plane, positive) + plane.w < 0)
				return false;
		}

		return true;
	}

	Window* Camera::GetWindow() const
	{
		return ServiceProvider::Instance().Get<Window>();
	}

	EventSystem* Camera::GetEventSystem() const
	{
		return ServiceProvider::Instance().Get<EventSystem>();
	}
}