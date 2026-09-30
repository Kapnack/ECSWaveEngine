#include "Matrix3x3.h"

#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/WaveMath/WaveMath.h"
#include "WaveMath/Quaternion/Quaternion.h"


Matrix3x3::Matrix3x3()
{
	*this = Zero();
}

Matrix3x3::Matrix3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02;
	this->m10 = m10; this->m11 = m11; this->m12 = m12;
	this->m20 = m20; this->m21 = m21; this->m22 = m22;
}

void Matrix3x3::Transpose()
{
	*this = Transposed();
}

Matrix3x3 Matrix3x3::Transposed() const
{
	return Transposed(*this);
}

void Matrix3x3::Inverse()
{
	*this = Inversed();
}

Matrix3x3 Matrix3x3::Inversed() const
{
	return Inversed(*this);
}

float Matrix3x3::Trace() const
{
	return Trace(*this);
}

float Matrix3x3::Determinant() const
{
	return Determinant(*this);
}

void Matrix3x3::Rotate(Quaternion rotation)
{
	*this = Rotated(rotation);
}

Matrix3x3 Matrix3x3::Rotated(Quaternion rotation) const
{
	return Rotated(*this, rotation);
}

void Matrix3x3::Rotate(Vector3 rotation)
{
	*this = Rotated(rotation);
}

Matrix3x3 Matrix3x3::Rotated(Vector3 rotation) const
{
	return Rotated(*this, rotation);
}

Vector3 Matrix3x3::ArvosMethod(Vector3 extends) const
{
	return ArvosMethod(*this, extends);
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other)
{
	return Matrix3x3(
		m00 + other.m00, m01 + other.m01, m02 + m02,
		m10 + other.m10, m11 + other.m11, m12 + m12,
		m20 + other.m20, m21 + other.m21, m22 + m22);
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other)
{
	return Matrix3x3(
		m00 - other.m00, m01 - other.m01, m02 - other.m02,
		m10 - other.m10, m11 - other.m11, m12 - other.m12,
		m20 - other.m20, m21 - other.m21, m22 - other.m22);
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other)
{
	return Matrix3x3(
		m00 * other.m00 + m01 * other.m10 + m02 * other.m20,
		m00 * other.m01 + m01 * other.m11 + m02 * other.m21,
		m00 * other.m02 + m01 * other.m12 + m02 * other.m22,

		m10 * other.m00 + m11 * other.m10 + m12 * other.m20,
		m10 * other.m01 + m11 * other.m11 + m12 * other.m21,
		m10 * other.m02 + m11 * other.m12 + m12 * other.m22,

		m20 * other.m00 + m21 * other.m10 + m22 * other.m20,
		m20 * other.m01 + m21 * other.m11 + m22 * other.m21,
		m20 * other.m02 + m21 * other.m12 + m22 * other.m22);
}

Matrix3x3 Matrix3x3::operator*(float scalar)
{
	return Matrix3x3(
		m00 * scalar, m01 * scalar, m02 * scalar,
		m10 * scalar, m11 * scalar, m12 * scalar,
		m20 * scalar, m21 * scalar, m22 * scalar);
}

Vector3 Matrix3x3::operator*(Vector3 vector)
{
	return Vector3(
		m00 * vector.x + m01 * vector.y + m02 * vector.z,
		m10 * vector.x + m11 * vector.y + m12 * vector.z,
		m20 * vector.x + m21 * vector.y + m22 * vector.z);
}

Matrix3x3 Matrix3x3::Identity()
{
	return Matrix3x3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
}

Matrix3x3 Matrix3x3::Diagonal(Vector3 vector)
{
	return Matrix3x3(
		vector.x, 0.0f, 0.0f,
		0.0f, vector.y, 0.0f,
		0.0f, 0.0f, vector.z);
}

Matrix3x3 Matrix3x3::FromColumns(Vector3 a, Vector3 b, Vector3 c)
{
	return Matrix3x3(
		a.x, b.x, c.x,
		a.y, b.y, c.y,
		a.z, b.z, c.z);
}

Matrix3x3 Matrix3x3::OuterProduct(Vector3 a, Vector3 b)
{
	return Matrix3x3(
		a.x * b.x, a.x * b.y, a.x * b.z,
		a.y * b.x, a.y * b.y, a.y * b.z,
		a.z * b.x, a.z * b.y, a.z * b.z);
}

Matrix3x3 Matrix3x3::FromQuaternion(Quaternion quaternion)
{
	quaternion.Normalize();

	float xx = quaternion.x * quaternion.x;
	float yy = quaternion.y * quaternion.y;
	float zz = quaternion.z * quaternion.z;
	float xy = quaternion.x * quaternion.y;
	float xz = quaternion.x * quaternion.z;
	float yz = quaternion.y * quaternion.z;
	float wx = quaternion.w * quaternion.x;
	float wy = quaternion.w * quaternion.y;
	float wz = quaternion.w * quaternion.z;

	return Matrix3x3(
		1.0f - 2.0f * (yy + zz), 2.0f * (xy - wz), 2.0f * (xz + wy),
		2.0f * (xy + wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - wx),
		2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (xx + yy));
}

Matrix3x3 Matrix3x3::Transposed(const Matrix3x3& matrix3x3)
{
	return Matrix3x3(
		matrix3x3.m00, matrix3x3.m10, matrix3x3.m20,
		matrix3x3.m01, matrix3x3.m11, matrix3x3.m21,
		matrix3x3.m02, matrix3x3.m12, matrix3x3.m22);
}

Matrix3x3 Matrix3x3::Inversed(const Matrix3x3& matrix3x3)
{
	float det = matrix3x3.Determinant();

	if (WaveMath::Abs(det) < WaveMath::Epsilon())
		return Zero();

	float invDet = 1.0f / det;

	return Matrix3x3(
		(matrix3x3.m11 * matrix3x3.m22 - matrix3x3.m12 * matrix3x3.m21) * invDet,
		(matrix3x3.m02 * matrix3x3.m21 - matrix3x3.m01 * matrix3x3.m22) * invDet,
		(matrix3x3.m01 * matrix3x3.m12 - matrix3x3.m02 * matrix3x3.m11) * invDet,

		(matrix3x3.m12 * matrix3x3.m20 - matrix3x3.m10 * matrix3x3.m22) * invDet,
		(matrix3x3.m00 * matrix3x3.m22 - matrix3x3.m02 * matrix3x3.m20) * invDet,
		(matrix3x3.m02 * matrix3x3.m10 - matrix3x3.m00 * matrix3x3.m12) * invDet,

		(matrix3x3.m10 * matrix3x3.m21 - matrix3x3.m11 * matrix3x3.m20) * invDet,
		(matrix3x3.m01 * matrix3x3.m20 - matrix3x3.m00 * matrix3x3.m21) * invDet,
		(matrix3x3.m00 * matrix3x3.m11 - matrix3x3.m01 * matrix3x3.m10) * invDet);
}

Matrix3x3 Matrix3x3::Zero()
{
	return Matrix3x3(
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f);
}

Matrix3x3 Matrix3x3::One()
{
	return Matrix3x3(
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f);
}

float Matrix3x3::Trace(const Matrix3x3& matrix3x3)
{
	return matrix3x3.m00 + matrix3x3.m11 + matrix3x3.m22;
}

float Matrix3x3::Determinant(const Matrix3x3& matrix3x3)
{
	return matrix3x3.m00 * (matrix3x3.m11 * matrix3x3.m22 - matrix3x3.m12 * matrix3x3.m21)
		- matrix3x3.m01 * (matrix3x3.m10 * matrix3x3.m22 - matrix3x3.m12 * matrix3x3.m20)
		+ matrix3x3.m02 * (matrix3x3.m10 * matrix3x3.m21 - matrix3x3.m11 * matrix3x3.m20);
}

Matrix3x3 Matrix3x3::Rotated(const Matrix3x3& inertia, Vector3 rotation)
{
	return Rotated(inertia, Quaternion::Euler(rotation));
}

Vector3 Matrix3x3::ArvosMethod(const Matrix3x3& matrix, Vector3 extends)
{
	return Vector3
	(
		WaveMath::Abs(matrix.m00) * extends.x + WaveMath::Abs(matrix.m01) * extends.y + WaveMath::Abs(matrix.m02) * extends.z,
		WaveMath::Abs(matrix.m10) * extends.x + WaveMath::Abs(matrix.m11) * extends.y + WaveMath::Abs(matrix.m12) * extends.z,
		WaveMath::Abs(matrix.m20) * extends.x + WaveMath::Abs(matrix.m21) * extends.y + WaveMath::Abs(matrix.m22) * extends.z
	);
}

Matrix3x3 Matrix3x3::Rotated(const Matrix3x3& inertia, Quaternion rotation)
{
	Matrix3x3 r = FromQuaternion(rotation);
	return r * inertia * r.Transposed();
}
