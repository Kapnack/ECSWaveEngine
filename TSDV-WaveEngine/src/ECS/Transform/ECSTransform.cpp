#include "ECSTransform.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/fwd.hpp>

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ECS/WaveObject/WaveObject.h"
#include <ECS/WaveObject/WaveObjectRegistry.h>
#include "ObjectTransformDirtifyEvent.h"
#include <vector>

namespace WaveEngine
{
	ECSTransform::ECSTransform(const unsigned int& ID) : Component(ID)
	{
		SetParent(WaveObject::NULL_OBJECT);
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

	Vector3 ECSTransform::GetWorldPosition() const
	{
		glm::vec3 worldPos = glm::vec3(globalModel[3]);
		return Vector3(worldPos.x, worldPos.y, worldPos.z);
	}

	Vector3 ECSTransform::GetWorldRotation() const
	{
		glm::vec3 scaleOut, translationOut, skewOut;
		glm::vec4 perspectiveOut;
		glm::quat rotationOut;

		glm::decompose(globalModel, scaleOut, rotationOut, translationOut, skewOut, perspectiveOut);

		glm::vec3 euler = glm::degrees(glm::eulerAngles(rotationOut));
		return Vector3(euler.x, euler.y, euler.z);
	}

	Vector3 ECSTransform::GetWorldScale() const
	{
		glm::vec3 scaleOut, translationOut, skewOut;
		glm::vec4 perspectiveOut;
		glm::quat rotationOut;

		glm::decompose(globalModel, scaleOut, rotationOut, translationOut, skewOut, perspectiveOut);

		return Vector3(scaleOut.x, scaleOut.y, scaleOut.z);
	}

	void ECSTransform::SetWorldPosition(const Vector3& worldPosition)
	{
		if (parentID == WaveObject::NULL_OBJECT)
		{
			SetPosition(worldPosition);
			return;
		}

		const glm::mat4& parentGlobal = GetParent().GetTransform().GetGlobalModel();
		glm::vec4 localPos = glm::inverse(parentGlobal) *
			glm::vec4(worldPosition.x, worldPosition.y, worldPosition.z, 1.0f);

		SetPosition(localPos.x, localPos.y, localPos.z);
	}

	void ECSTransform::SetWorldRotation(const Vector3& worldRotation)
	{
		if (parentID == WaveObject::NULL_OBJECT)
		{
			SetRotation(worldRotation);
			return;
		}

		ECSTransform& parentTransform = GetParent().GetTransform();

		glm::quat worldQuat = glm::quat(glm::radians(
			glm::vec3(worldRotation.x, worldRotation.y, worldRotation.z)));

		Vector3 parentWorldRot = parentTransform.GetWorldRotation();
		glm::quat parentQuat = glm::quat(glm::radians(
			glm::vec3(parentWorldRot.x, parentWorldRot.y, parentWorldRot.z)));

		glm::quat localQuat = glm::inverse(parentQuat) * worldQuat;
		glm::vec3 localEuler = glm::degrees(glm::eulerAngles(localQuat));

		SetRotation(localEuler.x, localEuler.y, localEuler.z);
	}

	void ECSTransform::SetWorldScale(const Vector3& worldScale)
	{
		if (parentID == WaveObject::NULL_OBJECT)
		{
			SetScale(worldScale);
			return;
		}

		Vector3 parentWorldScale = GetParent().GetTransform().GetWorldScale();

		SetScale(
			worldScale.x / parentWorldScale.x,
			worldScale.y / parentWorldScale.y,
			worldScale.z / parentWorldScale.z
		);
	}

	void ECSTransform::TranslateWorld(const Vector3& worldDelta)
	{
		Vector3 currentWorldPos = GetWorldPosition();

		SetWorldPosition(Vector3(
			currentWorldPos.x + worldDelta.x,
			currentWorldPos.y + worldDelta.y,
			currentWorldPos.z + worldDelta.z
		));
	}

	void ECSTransform::RotateWorld(const Vector3& worldScale)
	{
		Vector3 currentWorldRotate = GetWorldRotation();

		SetWorldRotation(Vector3(
			currentWorldRotate.x + worldScale.x,
			currentWorldRotate.y + worldScale.y,
			currentWorldRotate.z + worldScale.z
		));
	}

	void ECSTransform::ScaleWorld(const Vector3& worldDelta)
	{
		Vector3 currentWorldScale = GetWorldScale();

		SetWorldPosition(Vector3(
			currentWorldScale.x + worldDelta.x,
			currentWorldScale.y + worldDelta.y,
			currentWorldScale.z + worldDelta.z
		));
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

	vector<WaveObject*> ECSTransform::GetChilds()
	{
		vector<WaveObject*> childsObjects;

		for (unsigned int childID : children)
			childsObjects.push_back(&ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetWaveObject(childID));

		return childsObjects;
	}

	WaveObject& ECSTransform::GetParent()
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetWaveObject(parentID);
	}

	void ECSTransform::SetParent(unsigned int id)
	{
		if (id != WaveObject::NULL_OBJECT)
		{
			SetScale(1, 1, 1);
			GetEventSystem()->Invoke<ObjectBecameChildEvent>(GetID());
		}
		else
			GetEventSystem()->Invoke<ObjectBecameParentEvent>(GetID());

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

		GetEventSystem()->Invoke<ObjectTransformDirtifyEvent>(GetID());

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


	EventSystem* ECSTransform::GetEventSystem()
	{
		return ServiceProvider::Instance().Get<EventSystem>();
	}
}