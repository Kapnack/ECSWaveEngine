#pragma once

#include <vector>

#include "Export.h"
#include "ECS/Component/Component.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Vector2/Vector2.h"
#include "EventSystem/EventSystem.h"
#include "WaveMath/Matrix4x4/Matrix4x4.h"
#include "WaveMath/Quaternion/Quaternion.h"

using namespace std;

namespace WaveEngine
{
	class Renderer;
	class WaveObject;
	class TransformLogic;
	class ImGuiClass;

	class WAVEEXPORT ECSTransform : public Component
	{
	private:

		Vector3 position;
		Vector3 scale = Vector3(1, 1, 1);
		Quaternion rotation;

		bool dirty = false;
		bool hasChildDirty = false;

		unsigned int parentID = 0;
		vector<unsigned int> children;

		Matrix4x4 localModel;
		Matrix4x4 worldModel;

		virtual void CalculateTRS();

		const Matrix4x4& GetWorldMatrix() const;
		const Matrix4x4& GetLocalMatrix() const;

		void MarkDirty();
		void MarkHasChildDirty();
		void UnDirty();

		void ClearDirtFlags();

		const bool IsDirty() const;
		const bool HasChildDirty() const;
		void UnMarkChildDirty();

		EventSystem* GetEventSystem();

		friend class Renderer;
		friend class TransformLogic;
		friend class MeshLogic;
		friend class ImGuiClass;

	public:

		ECSTransform(const unsigned int& ID);

		virtual ~ECSTransform();

		Vector3 GetPosition() const;
		Vector3 GetScale() const;
		Quaternion GetRotation() const;
		Vector3 GetEulerRotation() const;

		Vector3 GetLocalPosition() const;
		Vector3 GetLocalScale() const;
		Quaternion GetLocalRotation() const;
		Vector3 GetLocalEulerRotation() const;

		void SetPosition(Vector3 vector);
		void SetPosition(Vector2 translation);
		void SetPosition(float x, float y);
		virtual void SetPosition(float x, float y, float z);

		void Translate(Vector3 translation);
		void Translate(Vector2 translation);
		void Translate(float x, float y);
		virtual void Translate(float x, float y, float z);

		void SetScale(Vector3 vector);
		void SetScale(Vector2 translation);
		void SetScale(float x, float y);
		virtual void SetScale(float x, float y, float z);

		void Scale(Vector3 vector);
		void Scale(Vector2 translation);
		void Scale(float x, float y);
		virtual void Scale(float x, float y, float z);

		void SetRotation(Vector3 vector);
		void SetRotation(Vector2 vector);
		void SetRotation(float x, float y);
		virtual void SetRotation(float x, float y, float z);
		void SetRotation(Quaternion quaternion);

		void Rotate(Vector3 vector);
		void Rotate(Vector2 vector);
		void Rotate(float x, float y);
		virtual void Rotate(float x, float y, float z);
		void Rotate(Quaternion quaternion);

		void SetLocalPosition(Vector3 vector);
		void SetLocalPosition(Vector2 translation);
		void SetLocalPosition(float x, float y);
		virtual void SetLocalPosition(float x, float y, float z);

		void LocalTranslate(Vector3 translation);
		void LocalTranslate(Vector2 translation);
		void LocalTranslate(float x, float y);
		virtual void LocalTranslate(float x, float y, float z);

		void SetLocalScale(Vector3 vector);
		void SetLocalScale(Vector2 translation);
		void SetLocalScale(float x, float y);
		virtual void SetLocalScale(float x, float y, float z);

		void LocalScale(Vector3 vector);
		void LocalScale(Vector2 translation);
		void LocalScale(float x, float y);
		virtual void LocalScale(float x, float y, float z);

		void SetLocalRotation(Vector3 vector);
		void SetLocalRotation(Vector2 vector);
		void SetLocalRotation(float x, float y);
		virtual void SetLocalRotation(float x, float y, float z);
		void SetLocalRotation(Quaternion quaternion);

		void LocalRotate(Vector3 vector);
		void LocalRotate(Vector2 vector);
		void LocalRotate(float x, float y);
		virtual void LocalRotate(float x, float y, float z);
		void LocalRotate(Quaternion quaternion);

		Vector3 WorldToLocal(Vector3 worldPoint) const;

		void LookAt(Vector3 vector);

		void FlipX();
		void FlipY();
		void FlipZ();

		Vector3 GetForward() const;
		Vector3 GetBack() const;
		Vector3 GetRight() const;
		Vector3 GetLeft() const;
		Vector3 GetUp() const;
		Vector3 GetDown() const;

		const Matrix4x4& GetLocalModel() const;
		const Matrix4x4& GetGlobalModel() const;

		void SetGlobalModel(const Matrix4x4& m);

		unsigned int GetParentID() const;
		const vector<unsigned int>& GetChildsIDs() const;

		WaveObject& GetChild(const unsigned int index);
		vector<WaveObject*> GetChilds() const;

		WaveObject& GetParent() const;

		void SetParent(unsigned int id);
		void AddChild(unsigned int id);
		void RemoveChild(unsigned int id);
	};
}
