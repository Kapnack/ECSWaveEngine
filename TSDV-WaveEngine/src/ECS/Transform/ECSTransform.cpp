#include "ECSTransform.h"

#include <memory>
#include <vector>

#include "EventSystem/EventSystem.h"
#include "ECS/Component/Component.h"
#include "WaveMath/Vector2/Vector2.h"
#include "WaveMath/Vector3/Vector3.h"
#include "ECS/WaveObject/WaveObject.h"
#include "ObjectTransformDirtifyEvent.h"
#include "WaveMath/Matrix4x4/Matrix4x4.h"
#include "WaveMath/Quaternion/Quaternion.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ECS/WaveObject/Events/ObjectBecameChildEvent.h"
#include "ECS/WaveObject/Events/ObjectBecameParentEvent.h"

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
		return worldModel.GetTranslate();
	}

	Vector3 ECSTransform::GetScale() const
	{
		return worldModel.GetScale();
	}

	Quaternion ECSTransform::GetRotation() const
	{
		return worldModel.GetRotation();
	}

	Vector3 ECSTransform::GetEulerRotation() const
	{
		return worldModel.GetRotation().ToEuler();
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

	void ECSTransform::SetPosition(Vector3 vector)
	{
		SetPosition(vector.x, vector.y, vector.z);
	}

	void ECSTransform::SetPosition(Vector2 translation)
	{
		SetPosition(translation.x, translation.y);
	}

	void ECSTransform::SetPosition(float x, float y)
	{
		SetPosition(x, y, worldModel.m32);
	}

	void ECSTransform::SetPosition(float x, float y, float z)
	{
		if (parentID == WaveObject::NULL_OBJECT)
		{
			SetLocalPosition(x, y, z);
			return;
		}

		const Matrix4x4& parentWorld = GetParent().GetTransform().GetWorldMatrix();

		Vector3 local = (Matrix4x4::Inversed(parentWorld) * Matrix4x4::CreateTranslate(Vector3(x, y, z))).GetTranslate();

		SetLocalPosition(local);
	}

	void ECSTransform::Translate(Vector3 translation)
	{
		Translate(translation.x, translation.y, translation.z);
	}

	void ECSTransform::Translate(Vector2 translation)
	{
		Translate(translation.x, translation.y);
	}

	void ECSTransform::Translate(float x, float y)
	{
		Translate(x, y, 0.0f);
	}

	void ECSTransform::Translate(float x, float y, float z)
	{
		if (parentID == WaveObject::NULL_OBJECT)
		{
			LocalTranslate(x, y, z);
			return;
		}

		const Matrix4x4& parentWorld = GetParent().GetTransform().GetWorldMatrix();

		Vector3 local = (Matrix4x4::Inversed(parentWorld) * Matrix4x4::CreateTranslate(Vector3(x, y, z))).GetTranslate();

		LocalTranslate(local);
	}

	void ECSTransform::SetScale(Vector3 vector)
	{
		SetScale(vector.x, vector.y, vector.z);
	}

	void ECSTransform::SetScale(Vector2 translation)
	{
		SetScale(translation.x, translation.y);
	}

	void ECSTransform::SetScale(float x, float y)
	{
		SetScale(x, y, worldModel.m22);
	}

	void ECSTransform::SetScale(float x, float y, float z)
	{
		if (parentID == WaveObject::NULL_OBJECT)
		{
			SetLocalScale(x, y, z);
			return;
		}

		const Matrix4x4& parentWorld = GetParent().GetTransform().GetWorldMatrix();

		Vector3 local = (Matrix4x4::Inversed(parentWorld) * Matrix4x4::CreateScale(Vector3(x, y, z))).GetScale();

		SetLocalScale(local);
	}

	void ECSTransform::Scale(Vector3 vector)
	{
		Scale(vector.x, vector.y, vector.z);
	}

	void ECSTransform::Scale(Vector2 translation)
	{
		Scale(translation.x, translation.y);
	}

	void ECSTransform::Scale(float x, float y)
	{
		Scale(x, y, 0.0f);
	}

	void ECSTransform::Scale(float x, float y, float z)
	{
		if (parentID == WaveObject::NULL_OBJECT)
		{
			LocalScale(x, y, z);
			return;
		}

		const Matrix4x4& parentWorld = GetParent().GetTransform().GetWorldMatrix();

		Vector3 local = (Matrix4x4::Inversed(parentWorld) * Matrix4x4::CreateScale(Vector3(x, y, z))).GetScale();

		LocalScale(local);
	}

	void ECSTransform::SetRotation(Vector3 vector)
	{
		SetRotation(vector.x, vector.y, vector.z);
	}

	void ECSTransform::SetRotation(Vector2 vector)
	{
		SetRotation(vector.x, vector.y);
	}

	void ECSTransform::SetRotation(float x, float y)
	{
		SetRotation(x, y, worldModel.GetRotation().ToEuler().z);
	}

	void ECSTransform::SetRotation(float x, float y, float z)
	{
		SetRotation(Quaternion::Euler(x, y, z));
	}

	void ECSTransform::SetRotation(Quaternion quaternion)
	{
		if (parentID == WaveObject::NULL_OBJECT)
		{
			SetLocalRotation(quaternion);
			return;
		}

		const Matrix4x4& parentWorld = GetParent().GetTransform().GetWorldMatrix();

		Quaternion local = (Matrix4x4::Inversed(parentWorld) * Matrix4x4::CreateRotation(quaternion)).GetRotation();

		SetLocalRotation(local);
	}

	void ECSTransform::Rotate(Vector3 vector)
	{
		Rotate(vector.x, vector.y, vector.z);
	}

	void ECSTransform::Rotate(Vector2 vector)
	{
		Rotate(vector.x, vector.y);
	}

	void ECSTransform::Rotate(float x, float y)
	{
		Rotate(x, y, 0.0f);
	}

	void ECSTransform::Rotate(float x, float y, float z)
	{
		Rotate(Quaternion::Euler(x, y, z));
	}

	void ECSTransform::Rotate(Quaternion quaternion)
	{
		if (parentID == WaveObject::NULL_OBJECT)
		{
			LocalRotate(quaternion);
			return;
		}

		const Matrix4x4& parentWorld = GetParent().GetTransform().GetWorldMatrix();

		Quaternion local = (Matrix4x4::Inversed(parentWorld) * Matrix4x4::CreateRotation(quaternion)).GetRotation();

		LocalRotate(local);
	}

	void ECSTransform::SetLocalPosition(Vector3 vector)
	{
		SetLocalPosition(vector.x, vector.y, vector.z);
	}

	void ECSTransform::SetLocalPosition(Vector2 translation)
	{
		SetLocalPosition(translation.x, translation.y);
	}

	void ECSTransform::SetLocalPosition(float x, float y)
	{
		SetLocalPosition(x, y, position.z);
	}

	void ECSTransform::SetLocalPosition(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;

		MarkDirty();
	}

	void ECSTransform::LocalTranslate(Vector3 translation)
	{
		LocalTranslate(translation.x, translation.y, translation.z);
	}

	void ECSTransform::LocalTranslate(Vector2 translation)
	{
		LocalTranslate(translation.x, translation.y);
	}

	void ECSTransform::LocalTranslate(float x, float y)
	{
		LocalTranslate(x, y, 0);
	}

	void ECSTransform::LocalTranslate(float x, float y, float z)
	{
		position.x += x;
		position.y += y;
		position.z += z;

		MarkDirty();
	}

	void ECSTransform::SetLocalScale(Vector3 vector)
	{
		SetLocalScale(vector.x, vector.y, vector.z);
	}

	void ECSTransform::SetLocalScale(Vector2 translation)
	{
		SetLocalScale(translation.x, translation.y);
	}

	void ECSTransform::SetLocalScale(float x, float y)
	{
		SetLocalScale(x, y, scale.z);
	}

	void ECSTransform::SetLocalScale(float x, float y, float z)
	{
		scale.x = x;
		scale.y = y;
		scale.z = z;

		MarkDirty();
	}

	void ECSTransform::LocalScale(Vector3 vector)
	{
		LocalScale(vector.x, vector.y, vector.z);
	}

	void ECSTransform::LocalScale(Vector2 translation)
	{
		LocalScale(translation.x, translation.y);
	}

	void ECSTransform::LocalScale(float x, float y)
	{
		LocalScale(x, y, 0.0f);
	}

	void ECSTransform::LocalScale(float x, float y, float z)
	{
		scale.x += x;
		scale.y += y;
		scale.z += z;

		MarkDirty();
	}

	void ECSTransform::SetLocalRotation(Vector3 vector)
	{
		SetLocalRotation(vector.x, vector.y, vector.z);
	}

	void ECSTransform::SetLocalRotation(Vector2 vector)
	{
		SetLocalRotation(vector.x, vector.y);
	}

	void ECSTransform::SetLocalRotation(float x, float y)
	{
		SetLocalRotation(Quaternion::Euler(x, y, GetLocalEulerRotation().z));
	}

	void ECSTransform::SetLocalRotation(Quaternion quaternion)
	{
		rotation = quaternion;
		MarkDirty();
	}

	void ECSTransform::LocalRotate(Vector3 vector)
	{
		LocalRotate(vector.x, vector.y, vector.z);
	}

	void ECSTransform::LocalRotate(Vector2 vector)
	{
		LocalRotate(vector.x, vector.y);
	}

	void ECSTransform::LocalRotate(float x, float y)
	{
		LocalRotate(x, y, 0.0f);
	}

	void ECSTransform::LocalRotate(float x, float y, float z)
	{
		LocalRotate(Quaternion::Euler(x, y, z));
	}

	void ECSTransform::SetLocalRotation(float x, float y, float z)
	{
		SetLocalRotation(Quaternion::Euler(x, y, z));
	}

	void ECSTransform::LocalRotate(Quaternion quaternion)
	{
		rotation *= quaternion;
		MarkDirty();
	}

	Vector3 ECSTransform::WorldToLocal(Vector3 worldPoint) const
	{
		Vector3 local = (Matrix4x4::Inversed(worldModel) * Matrix4x4::CreateTranslate(worldPoint)).GetTranslate();
		return local;
	}

	void ECSTransform::LookAt(Vector3 target)
	{
		rotation = Quaternion::LookAt(target);;
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
		return worldModel.GetFoward();
	}

	Vector3 ECSTransform::GetBack() const
	{
		return worldModel.GetBack();
	}

	Vector3 ECSTransform::GetRight() const
	{
		return worldModel.GetRight();
	}

	Vector3 ECSTransform::GetLeft() const
	{
		return worldModel.GetLeft();
	}

	Vector3 ECSTransform::GetUp() const
	{
		return worldModel.GetUP();
	}

	Vector3 ECSTransform::GetDown() const
	{
		return worldModel.GetDown();
	}

	const Matrix4x4& ECSTransform::GetLocalModel() const
	{
		return localModel;
	}

	const Matrix4x4& ECSTransform::GetGlobalModel() const
	{
		return worldModel;
	}

	void ECSTransform::SetGlobalModel(const Matrix4x4& m)
	{
		worldModel = m;
	}

	unsigned int ECSTransform::GetParentID() const
	{
		return parentID;
	}

	const vector<unsigned int>& ECSTransform::GetChildsIDs() const
	{
		return children;
	}

	WaveObject& ECSTransform::GetChild(const unsigned int index)
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetWaveObject(children[index]);
	}

	vector<WaveObject*> ECSTransform::GetChilds() const
	{
		vector<WaveObject*> childsObjects;

		for (unsigned int childID : children)
			childsObjects.push_back(&ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetWaveObject(childID));

		return childsObjects;
	}

	WaveObject& ECSTransform::GetParent() const
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

	void ECSTransform::RemoveChild(unsigned int id)
	{
		children.erase(remove(children.begin(), children.end(), id), children.end());
	}

	void ECSTransform::CalculateTRS()
	{
		localModel = Matrix4x4::TRS(Matrix4x4::CreateTranslate(position), Matrix4x4::CreateRotation(rotation), Matrix4x4::CreateScale(scale));

		UnDirty();
	}

	const Matrix4x4& ECSTransform::GetWorldMatrix() const
	{
		return worldModel;
	}

	const Matrix4x4& ECSTransform::GetLocalMatrix() const
	{
		return localModel;
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
				parent->MarkHasChildDirty();
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