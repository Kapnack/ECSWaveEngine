#include "ECSTransform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <cmath>
#include <glm/fwd.hpp>

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ECS/WaveObject/WaveObject.h"
#include <ECS/WaveObject/WaveObjectRegistry.h>

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

	Vector3 ECSTransform::WorldToLocal(const Vector3& worldPoint) const
	{
		glm::vec4 local = glm::inverse(globalModel) * glm::vec4(worldPoint.x, worldPoint.y, worldPoint.z, 1.0f);
		return Vector3(local.x, local.y, local.z);
	}

	void ECSTransform::LookAt(const Vector3& target)
	{
		glm::vec3 pos(position.x, position.y, position.z);
		glm::vec3 tgt(target.x, target.y, target.z);

		glm::vec3 forward = glm::normalize(tgt - pos);

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
		glm::vec3 forward = normalize(glm::vec3(-globalModel[2]));
		return Vector3(forward.x, forward.y, forward.z);
	}

	Vector3 ECSTransform::GetBack() const
	{
		return -GetForward();
	}

	Vector3 ECSTransform::GetRight() const
	{
		glm::vec3 right = glm::normalize(glm::vec3(globalModel[0]));
		return Vector3(right.x, right.y, right.z);
	}

	Vector3 ECSTransform::GetLeft() const
	{
		return -GetRight();
	}

	Vector3 ECSTransform::GetUp() const
	{
		glm::vec3 up = glm::normalize(glm::vec3(globalModel[1]));
		return Vector3(up.x, up.y, up.z);
	}

	Vector3 ECSTransform::GetDown() const
	{
		return -GetUp();
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

	WaveObject& ECSTransform::GetChild(const unsigned int index)
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetWaveObject(children[index]);
	}

	WaveObject& ECSTransform::GetParent()
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetWaveObject(parentID);
	}

	void ECSTransform::SetParent(unsigned int id)
	{
		if (id != WaveObject::NULL_OBJECT)
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

		UnDirty();
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
		MarkHasChildDirty();

		for (int childID : children)
		{
			ECSTransform* child = ServiceProvider::Instance().Get<ComponentRegistry>()->TryGet<ECSTransform>(childID);

			if (child)
				child->MarkDirty();
		}

		if (parentID != WaveObject::NULL_OBJECT)
		{
			ECSTransform* parent = ServiceProvider::Instance().Get<ComponentRegistry>()->TryGet<ECSTransform>(parentID);

			if (parent)
				parent->HasChildDirty();
		}
	}

	void ECSTransform::MarkHasChildDirty()
	{
		if (hasChildDirty)
			return;

		hasChildDirty = true;

		if (parentID == WaveObject::NULL_OBJECT)
			return;

		GetParent().GetTransform().MarkHasChildDirty();
	}

	void ECSTransform::UnDirty()
	{
		dirty = false;
	}

	void ECSTransform::ClearDirtFlags()
	{
		UnDirty();
		UnMarkChildDirty();
	}

	const bool ECSTransform::IsDirty() const
	{
		return dirty;
	}

	const bool ECSTransform::HasChildDirty() const
	{
		return hasChildDirty;
	}

	void ECSTransform::UnMarkChildDirty()
	{
		hasChildDirty = false;
	}
}