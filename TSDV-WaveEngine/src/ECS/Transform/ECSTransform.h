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

		WAVEEXPORT Vector3 GetPreviousPos() const;
		WAVEEXPORT void GoToPreviousPos();

		WAVEEXPORT void SetPosition(Vector3 vector);
		WAVEEXPORT void SetPosition(Vector2 translation);
		WAVEEXPORT void SetPosition(float x, float y);
		WAVEEXPORT virtual void SetPosition( float x,  float y,  float z);

		WAVEEXPORT void Translate(Vector3 translation);
		WAVEEXPORT void Translate(Vector2 translation);
		WAVEEXPORT void Translate(float x, float y);
		WAVEEXPORT virtual void Translate( float x,  float y,  float z);

		WAVEEXPORT void SetScale(Vector3 vector);
		WAVEEXPORT void SetScale(Vector2 translation);
		WAVEEXPORT void SetScale(float x, float y);
		WAVEEXPORT virtual void SetScale(float x, float y, float z);

		WAVEEXPORT void Scale(Vector3 vector);
		WAVEEXPORT void Scale(Vector2 translation);
		WAVEEXPORT void Scale(float x, float y);
		WAVEEXPORT virtual void Scale(float x, float y, float z);

		WAVEEXPORT void SetRotation(Vector3 vector);
		WAVEEXPORT void SetRotation(Vector2 vector);
		WAVEEXPORT void SetRotation(float x, float y);
		WAVEEXPORT virtual void SetRotation(float x, float y, float z);

		WAVEEXPORT void Rotate(Vector3 vector);
		WAVEEXPORT void Rotate(Vector2 vector);
		WAVEEXPORT void Rotate(float x, float y);
		WAVEEXPORT virtual void Rotate(float x, float y, float z);

		WAVEEXPORT Vector3 WorldToLocal(Vector3 worldPoint) const;

		WAVEEXPORT void LookAt(Vector3 vector);

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
