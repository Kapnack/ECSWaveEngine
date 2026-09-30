#pragma once

#include "Export.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Quaternion/Quaternion.h"

struct WAVEEXPORT Matrix3x3
{
public:

	float m00, m01, m02;
	float m10, m11, m12;
	float m20, m21, m22;

	Matrix3x3();
	Matrix3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);

	void Transpose();
	Matrix3x3 Transposed() const;

	void Inverse();
	Matrix3x3 Inversed() const;

	float Trace() const;
	float Determinant() const;
	void Rotate(Quaternion rotation);
	Matrix3x3 Rotated(Quaternion rotation) const;
	void Rotate(Vector3 rotation);
	Matrix3x3 Rotated(Vector3 rotation) const;
	Vector3 ArvosMethod(Vector3 extends) const;

	Matrix3x3 operator+(const Matrix3x3& other);
	Matrix3x3 operator-(const Matrix3x3& other);
	Matrix3x3 operator*(const Matrix3x3& other);
	Matrix3x3 operator*(float scalar);
	Vector3 operator*(Vector3 vector);

	static Matrix3x3 Identity();
	static Matrix3x3 Zero();
	static Matrix3x3 One();

	static Matrix3x3 Diagonal(Vector3 vector);
	static Matrix3x3 FromColumns(Vector3 a, Vector3 b, Vector3 c);
	static Matrix3x3 OuterProduct(Vector3 a, Vector3 b);
	static Matrix3x3 FromQuaternion(Quaternion quaternion);
	static Matrix3x3 Transposed(const Matrix3x3& matrix3x3);
	static Matrix3x3 Inversed(const Matrix3x3& matrix3x3);
	static float Trace(const Matrix3x3& matrix3x3);
	static float Determinant(const Matrix3x3& matrix3x3);
	static Matrix3x3 Rotated(const Matrix3x3& inertia, Quaternion rotation);
	static Matrix3x3 Rotated(const Matrix3x3& inertia, Vector3 rotation);
	static Vector3 ArvosMethod(const Matrix3x3& matrix, Vector3 extends);
};