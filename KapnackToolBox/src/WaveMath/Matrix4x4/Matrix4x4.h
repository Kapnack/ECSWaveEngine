#pragma once

#include "Export.h"

#include "../Quaternion/Quaternion.h"

struct WAVEEXPORT Matrix4x4 final
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;

	Matrix4x4();
	Matrix4x4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	Matrix4x4(Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3);
	~Matrix4x4();

	void SetTranslate(Vector3 vector);
	void AddTranslate(Vector3 vector);
	Matrix4x4 GetTranslateMatrix() const;
	Matrix4x4 GetRotationMatrix() const;
	void SetScale(Vector3 vector);
	void AddScale(Vector3 vector);
	Matrix4x4 GetScaleMatrix() const;

	void UpdateMaxtrix();

	Matrix4x4 operator*(const Matrix4x4& other) const;

	static Matrix4x4 Identity();
	static Matrix4x4 CreateScale(float x, float y, float z);
	static Matrix4x4 CreateScale(Vector3 vector);
	static Matrix4x4 CreateRotation(const Matrix4x4& matrix);
	static Quaternion GetRotation(const Matrix4x4& matrix);
	static Matrix4x4 CreateRotation(float x, float y, float z, float w);
	static Matrix4x4 CreateRotation(Quaternion quaternian);
	static Matrix4x4 CreateTranslate(float x, float y, float z);
	static Matrix4x4 CreateTranslate(Vector3 vector);

	static Matrix4x4 TRS(Vector3 t, Quaternion r, Vector3 s);
	static Matrix4x4 TRS(const Matrix4x4& t, const Matrix4x4& r, const Matrix4x4& s);
};
