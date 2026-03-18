#pragma once

#include "Export.h"
#include <glm/glm.hpp>
#include "ECS/Component/Component.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Vector2/Vector2.h"

using namespace std;

namespace WaveEngine
{
	class EntityFactory;
	class EntityManager;
	class EntitiesImGui;
	class MeshImGui;
	class BaseGame;
	class Renderer;

	WAVEEXPORT class ECSTransform : Component
	{
	private:

		Vector3 previousPosition;
		Vector3 position;

		bool shouldUpdateTRS = false;

		friend class EntityFactory;
		friend class EntityManager;
		friend class EntitiesImGui;
		friend class MeshImGui;
		friend class BaseGame;
		friend class Renderer;

		Vector3 scale = Vector3(1, 1, 1);
		Vector3 rotation;

		glm::mat4 model;

		virtual void CalculateTRS();

		virtual void UpdateCollider()
		{ }

		glm::mat4& GetModel();

	public:

		ECSTransform();

		virtual ~ECSTransform();

		WAVEEXPORT Vector3 GetPosition() const;
		WAVEEXPORT Vector3 GetScale() const;
		WAVEEXPORT Vector3 GetRotation() const;

		WAVEEXPORT Vector3 GetPreviousPos() const;
		WAVEEXPORT void GoToPreviousPos();

		WAVEEXPORT void SetPosition(const Vector3& vector);
		WAVEEXPORT void SetPosition(const Vector2& translation);
		WAVEEXPORT void SetPosition(const float& x, const float& y);
		WAVEEXPORT virtual void SetPosition(const float& x, const float& y, const float& z);

		WAVEEXPORT void Translate(const Vector3& translation);
		WAVEEXPORT void Translate(const Vector2& translation);
		WAVEEXPORT void Translate(const float& x, const float& y);
		WAVEEXPORT virtual void Translate(const float& x, const float& y, const float& z);

		WAVEEXPORT void SetScale(const Vector3& vector);
		WAVEEXPORT void SetScale(const Vector2& translation);
		WAVEEXPORT void SetScale(const float& x, const float& y);
		WAVEEXPORT virtual void SetScale(const float& x, const float& y, const float& z);

		WAVEEXPORT void Scale(const Vector3& vector);
		WAVEEXPORT void Scale(const Vector2& translation);
		WAVEEXPORT void Scale(const float& x, const float& y);
		WAVEEXPORT virtual void Scale(const float& x, const float& y, const float& z);

		WAVEEXPORT void SetRotation(const Vector3& vector);
		WAVEEXPORT void SetRotation(const Vector2& vector);
		WAVEEXPORT void SetRotation(const float& x, const float& y);
		WAVEEXPORT virtual void SetRotation(const float& x, const float& y, const float& z);

		WAVEEXPORT void Rotate(const Vector3& vector);
		WAVEEXPORT void Rotate(const Vector2& vector);
		WAVEEXPORT void Rotate(const float& x, const float& y);
		WAVEEXPORT virtual void Rotate(const float& x, const float& y, const float& z);

		WAVEEXPORT void FlipX();
		WAVEEXPORT void FlipY();
		WAVEEXPORT void FlipZ();
	};
}
