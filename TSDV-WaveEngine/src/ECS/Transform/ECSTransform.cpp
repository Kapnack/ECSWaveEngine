#include "ECSTransform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace WaveEngine
{
	ECSTransform::ECSTransform()
	{
		MarkDirty();
	}

	ECSTransform::~ECSTransform()
	{
	}

	Vector3 ECSTransform::GetPosition() const
	{
		return position;
	}

	Vector3 ECSTransform::GetScale() const
	{
		return scale;
	}

	Vector3 ECSTransform::GetRotation() const
	{
		return rotation;
	}

	Vector3 ECSTransform::GetPreviousPos() const
	{
		return previousPosition;
	}

	void ECSTransform::GoToPreviousPos()
	{
		SetPosition(previousPosition);
	}

	void ECSTransform::SetPosition(const Vector3& vector)
	{
		SetPosition(vector.x, vector.y, vector.z);
	}

	void ECSTransform::SetPosition(const Vector2& translation)
	{
		SetPosition(translation.x, translation.y);
	}

	void ECSTransform::SetPosition(const float& x, const float& y)
	{
		SetPosition(x, y, position.z);
	}

	void ECSTransform::SetPosition(const float& x, const float& y, const float& z)
	{
		position.x = x;
		position.y = y;
		position.z = z;

		previousPosition = position;

		MarkDirty();
	}

	void ECSTransform::Translate(const Vector3& translation)
	{
		Translate(translation.x, translation.y, translation.z);
	}

	void ECSTransform::Translate(const Vector2& translation)
	{
		Translate(translation.x, translation.y);
	}

	void ECSTransform::Translate(const float& x, const float& y)
	{
		Translate(x, y, 0);
	}

	void ECSTransform::Translate(const float& x, const float& y, const float& z)
	{
		previousPosition = position;

		position.x += x;
		position.y += y;
		position.z += z;

		MarkDirty();
	}

	void ECSTransform::SetScale(const Vector3& vector)
	{
		SetScale(vector.x, vector.y, vector.z);
	}

	void ECSTransform::SetScale(const Vector2& translation)
	{
		SetScale(translation.x, translation.y);
	}

	void ECSTransform::SetScale(const float& x, const float& y)
	{
		SetScale(x, y, scale.z);
	}

	void ECSTransform::SetScale(const float& x, const float& y, const float& z)
	{
		scale.x = x;
		scale.y = y;
		scale.z = z;

		MarkDirty();
	}

	void ECSTransform::Scale(const Vector3& vector)
	{
		Scale(vector.x, vector.y, vector.z);
	}

	void ECSTransform::Scale(const Vector2& translation)
	{
		Scale(translation.x, translation.y);
	}

	void ECSTransform::Scale(const float& x, const float& y)
	{
		Scale(x, y, 0.0f);
	}

	void ECSTransform::Scale(const float& x, const float& y, const float& z)
	{
		scale.x += x;
		scale.y += y;
		scale.z += z;

		MarkDirty();
	}

	void ECSTransform::SetRotation(const Vector3& vector)
	{
		SetRotation(vector.x, vector.y, vector.z);
	}

	void ECSTransform::SetRotation(const Vector2& vector)
	{
		SetRotation(vector.x, vector.y);
	}

	void ECSTransform::SetRotation(const float& x, const float& y)
	{
		SetRotation(x, y, rotation.z);
	}

	void ECSTransform::SetRotation(const float& x, const float& y, const float& z)
	{
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;

		MarkDirty();
	}

	void ECSTransform::Rotate(const Vector3& vector)
	{
		Rotate(vector.x, vector.y, vector.z);
	}

	void ECSTransform::Rotate(const Vector2& vector)
	{
		Rotate(vector.x, vector.y);
	}

	void ECSTransform::Rotate(const float& x, const float& y)
	{
		Rotate(x, y, 0);
	}

	void ECSTransform::Rotate(const float& x, const float& y, const float& z)
	{
		rotation.x += x;
		rotation.y += y;
		rotation.z += z;

		MarkDirty();
	}

	void ECSTransform::FlipX()
	{
		SetScale(-scale.x, scale.y, scale.z);
	}

	void ECSTransform::FlipY()
	{
		SetScale(scale.x, -scale.y, scale.z);
	}

	void ECSTransform::FlipZ()
	{
		SetScale(scale.x, scale.y, -scale.z);
	}

	void ECSTransform::CalculateTRS()
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
	}

	const glm::mat4& ECSTransform::GetModel() const
	{
		return model;
	}

	void ECSTransform::MarkDirty()
	{
		dirty = true;
	}

	const bool ECSTransform::IsDirty() const
	{
		return dirty;
	}
}