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

	Vector3 ECSTransform::GetPosition() const
	{
		return globalModel.GetTranslate();
	}

	Vector3 ECSTransform::GetScale() const
	{
		return globalModel.GetScale();
	}

	Quaternion ECSTransform::GetRotation() const
	{
		return globalModel.GetRotation();
	}

	Vector3 ECSTransform::GetEulerRotation() const
	{
		return rotation;
	}

	Vector3 ECSTransform::GetLocalPosition() const
	{
		return localModel.GetTranslate();
	}

	Vector3 ECSTransform::GetLocalScale() const
	{
		return localModel.GetScale();
	}

	Quaternion ECSTransform::GetLocalRotation() const
	{
		return localModel.GetRotation();
	}

	Vector3 ECSTransform::GetLocalEulerRotation() const
	{
		return GetLocalRotation().ToEuler();
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
		Vector3 local = (Matrix4x4::Inversed(globalModel) * Matrix4x4::CreateTranslate(worldPoint)).GetTranslate();
		return local;
	}

	void ECSTransform::LookAt(const Vector3& target)
	{
		rotation = Quaternion::LookAt(target).ToEuler();

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
		return globalModel.GetFoward();
	}

	Vector3 ECSTransform::GetBack() const
	{
		return globalModel.GetBack();
	}

	Vector3 ECSTransform::GetRight() const
	{
		return globalModel.GetRight();
	}

	Vector3 ECSTransform::GetLeft() const
	{
		return globalModel.GetLeft();
	}

	Vector3 ECSTransform::GetUp() const
	{
		return globalModel.GetUP();
	}

	Vector3 ECSTransform::GetDown() const
	{
		return globalModel.GetDown();
	}

	const Matrix4x4& ECSTransform::GetLocalModel() const
	{
		return localModel;
	}

	const Matrix4x4& ECSTransform::GetGlobalModel() const
	{
		return globalModel;
	}

	void ECSTransform::SetGlobalModel(const Matrix4x4& m)
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
		localModel = Matrix4x4::TRS(Matrix4x4::CreateTranslate(position), Matrix4x4::CreateRotation(Quaternion::Euler(rotation)), Matrix4x4::CreateScale(scale));

		UnDirty();
	}

	const Matrix4x4& ECSTransform::GetModel() const
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