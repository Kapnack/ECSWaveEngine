#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include "ServiceProvider/ServiceProvider.h"
#include "../CompontRegistry/ComponentRegistry.h"
#include "../Transform/ECSTransform.h"

namespace WaveEngine
{
	Camera::Camera(const unsigned int& ID)
	{
		this->ID = ID;

		ComponentRegistry& componentRegistry = *ServiceProvider::Instance().Get<ComponentRegistry>();

		if (!componentRegistry.HasStorage<ECSTransform>())
			componentRegistry.AddComponent<ECSTransform>(ID);

		if (!componentRegistry.Has<ECSTransform>(ID))
			componentRegistry.AddComponent<ECSTransform>(ID);

		transform = &componentRegistry.Get<ECSTransform>(ID);
	}

	Camera::Camera()
	{
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

		ECSTransform& transform = ServiceProvider::Instance().Get<ComponentRegistry>()->Get<ECSTransform>(ID);

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

		shouldUpdateMatrix = false;
	}

	Window* Camera::GetWindow() const
	{
		return ServiceProvider::Instance().Get<Window>();
	}
}