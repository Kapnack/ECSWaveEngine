#pragma once

#include "Export.h"
#include <glm/glm.hpp>
#include <vector>
#include "ECS/Component/Component.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Vector2/Vector2.h"
#include "EventSystem/EventSystem.h"
#include "WaveMath/Matrix4x4/Matrix4x4.h"

using namespace std;

namespace WaveEngine
{
	class Renderer;
	class TransformLogic;
	class ImGuiClass;

	WAVEEXPORT class ECSTransform : public Component
	{
	private:

		Vector3 previousPosition;
		Vector3 position;
		Vector3 scale = Vector3(1, 1, 1);
		Vector3 rotation;

		bool dirty = false;
		bool hasChildDirty = false;

		unsigned int parentID = 0;
		vector<int> children;

		Matrix4x4 localModel;
		Matrix4x4 globalModel;

		virtual void CalculateTRS();

		const Matrix4x4& GetModel() const;

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

		WAVEEXPORT Vector3 GetPosition() const;
		WAVEEXPORT Vector3 GetScale() const;
		WAVEEXPORT Quaternion GetRotation() const;
		WAVEEXPORT Vector3 GetEulerRotation() const;

		WAVEEXPORT Vector3 GetLocalPosition() const;
		WAVEEXPORT Vector3 GetLocalScale() const;
		WAVEEXPORT Quaternion GetLocalRotation() const;
		WAVEEXPORT Vector3 GetLocalEulerRotation() const;

		WAVEEXPORT const Vector3& GetPreviousPos() const;
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

		WAVEEXPORT Vector3 WorldToLocal(const Vector3& worldPoint) const;

		WAVEEXPORT void LookAt(const Vector3& vector);

		WAVEEXPORT void FlipX();
		WAVEEXPORT void FlipY();
		WAVEEXPORT void FlipZ();

		WAVEEXPORT Vector3 GetForward() const;
		WAVEEXPORT Vector3 GetBack() const;
		WAVEEXPORT Vector3 GetRight() const;
		WAVEEXPORT Vector3 GetLeft() const;
		WAVEEXPORT Vector3 GetUp() const;
		WAVEEXPORT Vector3 GetDown() const;

		const Matrix4x4& GetLocalModel() const;
		const Matrix4x4& GetGlobalModel() const;

		WAVEEXPORT void SetGlobalModel(const Matrix4x4& m);

		unsigned int GetParentID() const;
		const vector<int>& GetChildsIDs() const;

		WaveObject& GetChild(const unsigned int index);
		vector<WaveObject*> GetChilds();

		WaveObject& GetParent();

		void SetParent(unsigned int id);
		void AddChild(unsigned int id);
		void RemoveChild(unsigned int id);
	};
}
