#pragma once

#include <glm/fwd.hpp>

#include "Export.h"
#include "ECS/Transform/ECSTransform.h"
#include "ECS/Component/Component.h"
#include "BoundingBox/BoundingBox.h"
#include "Window/Window.h"

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

		bool shouldUpdateMatrix = true;

		float fovDeg = 45.0f;
		float nearPlane = 0.1f;
		float farPlane = 100.0f;
		float orthoSize = 500.0f;

		float yaw;
		float pitch;

		float movementSpeed = 100.0f;
		float sensitivity = 100.0f;

		bool orthografic = false;

		Frustum frustum;

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		Window* GetWindow() const;

		ECSTransform* transform;

	protected:

		void CalculateTRS();

	public:

		glm::mat4 GetView() const;
		glm::mat4 GetProjection() const;

		void CalculateMatrixes();

		Frustum GetFrustum() const;

		void ExtractFrustumPlanes();
		bool IsInsideFrustum(const BoundingBox& box) const;

		Camera(const unsigned& ID);
		WAVEEXPORT	Camera();
		WAVEEXPORT	~Camera();

		WAVEEXPORT	void SetOrthographic(const bool& value);
		WAVEEXPORT	void SetFarPlane(const float& value);
		WAVEEXPORT	void AddToFarPlane(const float& value);
		WAVEEXPORT	void SetNearPlane(const float& value);
		WAVEEXPORT	void AddToNearPlane(const float& value);
		WAVEEXPORT	void SetFovDegree(const float& value);
		WAVEEXPORT	void SetOrthoSize(const float& value);
		WAVEEXPORT	void AddToOrthoSize(const float& value);

		WAVEEXPORT	float GetFarPlane() const;
		WAVEEXPORT	float GetNearPlane() const;
		WAVEEXPORT	float GetFovDegree() const;
		WAVEEXPORT	float GetMovementSpeed() const;
		WAVEEXPORT	float GetOrthoSize() const;

		WAVEEXPORT	bool GetShouldUpdateMatrix() const;
	};
}