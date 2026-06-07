#include "ECSTransform.h"

#include <glm/gtc/matrix_transform.hpp>
#include "ServiceProvider/ServiceProvider.h"
#include <ECS/CompontRegistry/ComponentRegistry.h>
#include <glm/gtc/quaternion.hpp>
#include <cmath>

namespace WaveEngine
{
	ECSTransform::ECSTransform(const unsigned int& ID) : Component(ID)
	{
		MarkDirty();
	}

	ECSTransform::~ECSTransform()
	{
	}

	const Vector3& ECSTransform::GetPosition() const
	{
		return position;
	}

	const Vector3& ECSTransform::GetScale() const
	{
		return scale;
	}

	const Vector3& ECSTransform::GetRotation() const
	{
		return rotation;
	}

	const Vector3& ECSTransform::GetPreviousPos() const
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
		previousPosition = position;

		position.x = x;
		position.y = y;
		position.z = z;

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

	void ECSTransform::LookAt(const Vector3& target)
	{
		glm::vec3 pos(position.x, position.y, position.z);
		glm::vec3 tgt(target.x, target.y, target.z);

		glm::vec3 forward = glm::normalize(pos - tgt);

		glm::quat rot = glm::quatLookAt(forward, glm::vec3(0, 1, 0));

		glm::vec3 euler = glm::degrees(glm::eulerAngles(rot));

		rotation.x = euler.x;
		rotation.y = euler.y;
		rotation.z = euler.z;

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

	Vector3 ECSTransform::GetForward() const
	{
		glm::vec3 vector = GetForwardGLM(globalModel);
		return Vector3(vector.x, vector.y, vector.z).Normalized();
	}

	Vector3 ECSTransform::GetRight() const
	{
		glm::vec3 vector = GetRightGLM(globalModel);
		return Vector3(vector.x, vector.y, vector.z).Normalized();
	}

	Vector3 ECSTransform::GetUp() const
	{
		glm::vec3 vector = GetUpGLM(globalModel);
		return Vector3(vector.x, vector.y, vector.z).Normalized();
	}

	const glm::mat4& ECSTransform::GetLocalModel() const
	{
		return localModel;
	}

	const glm::mat4& ECSTransform::GetGlobalModel() const
	{
		return globalModel;
	}

	void ECSTransform::SetGlobalModel(const glm::mat4& m)
	{
		globalModel = m;
	}

	void ECSTransform::SetParent(int id)
	{
		if (id != 0)
			SetScale(1, 1, 1);

		parentID = id;
	}

	void ECSTransform::AddChild(unsigned int id)
	{
		for (int i = 0; i < children.size(); ++i)
			if (children[i] == id)
				return;

		children.push_back(id);
	}

	void ECSTransform::CalculateTRS()
	{
		localModel = glm::mat4(1.0f);
		localModel = glm::translate(localModel, glm::vec3(position.x, position.y, position.z));
		localModel = glm::rotate(localModel, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		localModel = glm::rotate(localModel, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		localModel = glm::rotate(localModel, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		localModel = glm::scale(localModel, glm::vec3(scale.x, scale.y, scale.z));

		dirty = false;
	}

	const glm::mat4& ECSTransform::GetModel() const
	{
		return globalModel;
	}

	void ECSTransform::MarkDirty()
	{
		if (dirty)
			return;

		dirty = true;

		for (int childID : children)
		{
			ECSTransform* child = ServiceProvider::Instance().Get<ComponentRegistry>()->TryGet<ECSTransform>(childID);

			if (child)
				child->MarkDirty();
		}
	}

	const bool ECSTransform::IsDirty() const
	{
		return dirty;
	}
}