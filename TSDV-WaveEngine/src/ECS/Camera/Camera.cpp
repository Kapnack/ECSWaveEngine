#include "Camera.h"

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include "ServiceProvider/ServiceProvider.h"
#include "../CompontRegistry/ComponentRegistry.h"
#include "../Transform/ECSTransform.h"
#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	Camera::Camera(const unsigned int& ID) : Component(ID)
	{
		ComponentRegistry& componentRegistry = *ServiceProvider::Instance().Get<ComponentRegistry>();

		if (!componentRegistry.HasStorage<ECSTransform>())
			componentRegistry.AddComponent<ECSTransform>(ID);

		if (!componentRegistry.Has<ECSTransform>(ID))
			componentRegistry.AddComponent<ECSTransform>(ID);

		transform = &componentRegistry.Get<ECSTransform>(ID);
	}

	Camera::~Camera()
	{
	}

	void Camera::CalculateTRS()
	{
		shouldUpdateMatrix = true;
	}

	void Camera::SetOrthographic(const bool& value)
	{
		orthografic = value;

		CalculateTRS();
	}

	void Camera::SetFarPlane(const float& value)
	{
		farPlane = value;

		shouldUpdateMatrix = true;
	}

	void Camera::AddToFarPlane(const float& value)
	{
		farPlane += value;

		CalculateTRS();
	}

	void Camera::SetNearPlane(const float& value)
	{
		nearPlane = value;

		CalculateTRS();
	}

	void Camera::AddToNearPlane(const float& value)
	{
		nearPlane += value;

		CalculateTRS();
	}

	void Camera::SetFovDegree(const float& value)
	{
		fovDeg = value;

		CalculateTRS();
	}

	void Camera::SetOrthoSize(const float& value)
	{
		orthoSize = value;
	}

	void Camera::AddToOrthoSize(const float& value)
	{
		orthoSize += value;
	}

	glm::mat4 Camera::GetView() const
	{
		return view;
	}

	glm::mat4 Camera::GetProjection() const
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

		ECSTransform& transform = GetWaveObject().GetTransform();

		glm::vec3 pos = glm::vec3(transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z);

		glm::mat4 rotationMatrix = glm::yawPitchRoll
		(
			glm::radians(transform.GetRotation().y),
			glm::radians(transform.GetRotation().x),
			glm::radians(transform.GetRotation().z)
		);

		glm::vec3 forward = glm::vec3(rotationMatrix * glm::vec4(0, 0, -1, 0));
		glm::vec3 up = glm::vec3(rotationMatrix * glm::vec4(0, 1, 0, 0));

		float halfHeight = orthoSize;
		float halfWidth = orthoSize * aspect;

		view = glm::lookAt(pos, pos + forward, up);

		projection = orthografic ?
			glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane)
			:
			glm::perspective(glm::radians(fovDeg), aspect, nearPlane, farPlane);

		ExtractFrustumPlanes();
		shouldUpdateMatrix = false;
	}

	Frustum Camera::GetFrustum() const
	{
		return frustum;
	}

	void Camera::ExtractFrustumPlanes()
	{
		glm::mat4 vp = projection * view;

		frustum.planes[0] = glm::vec4(vp[0][3] + vp[0][0], vp[1][3] + vp[1][0], vp[2][3] + vp[2][0], vp[3][3] + vp[3][0]); // Left
		frustum.planes[1] = glm::vec4(vp[0][3] - vp[0][0], vp[1][3] - vp[1][0], vp[2][3] - vp[2][0], vp[3][3] - vp[3][0]); // Right
		frustum.planes[2] = glm::vec4(vp[0][3] + vp[0][1], vp[1][3] + vp[1][1], vp[2][3] + vp[2][1], vp[3][3] + vp[3][1]); // Bottom
		frustum.planes[3] = glm::vec4(vp[0][3] - vp[0][1], vp[1][3] - vp[1][1], vp[2][3] - vp[2][1], vp[3][3] - vp[3][1]); // Top
		frustum.planes[4] = glm::vec4(vp[0][3] + vp[0][2], vp[1][3] + vp[1][2], vp[2][3] + vp[2][2], vp[3][3] + vp[3][2]); // Near
		frustum.planes[5] = glm::vec4(vp[0][3] - vp[0][2], vp[1][3] - vp[1][2], vp[2][3] - vp[2][2], vp[3][3] - vp[3][2]); // Far

		for (glm::vec4& plane : frustum.planes)
			plane /= glm::length(glm::vec3(plane));
	}

	bool Camera::IsInsideFrustum(const BoundingBox& box) const
	{
		glm::vec3 positive;

		for (const glm::vec4& plane : frustum.planes)
		{
			positive =
			{
				plane.x >= 0 ? box.GetMax().x : box.GetMin().x,
				plane.y >= 0 ? box.GetMax().y : box.GetMin().y,
				plane.z >= 0 ? box.GetMax().z : box.GetMin().z
			};

			if (glm::dot(glm::vec3(plane), positive) + plane.w < 0)
				return false;
		}

		return true;
	}

	Window* Camera::GetWindow() const
	{
		return ServiceProvider::Instance().Get<Window>();
	}
}