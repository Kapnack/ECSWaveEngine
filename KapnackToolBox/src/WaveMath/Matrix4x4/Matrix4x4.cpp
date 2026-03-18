#include "Matrix4x4.h"

#include <cmath>

#include <stdexcept> 

Matrix4x4::Matrix4x4()
{
	*this = Identity();
}

Matrix4x4::Matrix4x4(const float& m00, const float& m01, const float& m02, const float& m03, const float& m10, const float& m11, const float& m12, const float& m13, const float& m20, const float& m21, const float& m22, const float& m23, const float& m30, const float& m31, const float& m32, const float& m33)
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02; this->m03 = m03;
	this->m10 = m10; this->m11 = m11; this->m12 = m12; this->m13 = m13;
	this->m20 = m20; this->m21 = m21; this->m22 = m22; this->m23 = m23;
	this->m30 = m30; this->m31 = m31; this->m32 = m32; this->m33 = m33;
}

Matrix4x4::Matrix4x4(const Quaternion& q0, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3)
{
	m00 = q0.x; m01 = q0.y; m02 = q0.z; m03 = q0.w;
	m10 = q1.x; m11 = q1.y; m12 = q1.z; m13 = q1.w;
	m20 = q2.x; m21 = q2.y; m22 = q2.z; m23 = q2.w;
	m30 = q3.x; m31 = q3.y; m32 = q3.z; m33 = q3.w;
}

Matrix4x4::~Matrix4x4()
{
}

void Matrix4x4::SetTranslate(const Vector3& vector)
{
	m03 = vector.x;
	m13 = vector.y;
	m23 = vector.z;
}

void Matrix4x4::AddTranslate(const Vector3& vector)
{
	m03 += vector.x;
	m13 += vector.y;
	m23 += vector.z;
}

Matrix4x4 Matrix4x4::GetTranslateMatrix() const
{
	return CreateTranslate(m03, m13, m23);
}

Matrix4x4 Matrix4x4::GetRotationMatrix() const
{
	return CreateRotation(*this);
}

void Matrix4x4::SetScale(const Vector3& vector)
{
	m00 = vector.x;
	m11 = vector.y;
	m22 = vector.z;
}

void Matrix4x4::AddScale(const Vector3& vector)
{
	m00 *= vector.x;
	m11 *= vector.y;
	m22 *= vector.z;
}

Matrix4x4 Matrix4x4::GetScaleMatrix() const
{
	return CreateScale(m00, m11, m22);
}

void Matrix4x4::UpdateMaxtrix()
{
	*this = TRS(GetTranslateMatrix(), GetRotationMatrix(), GetScaleMatrix());
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
{
	return Matrix4x4
	(
		m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30,
		m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31,
		m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32,
		m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33,

		m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30,
		m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31,
		m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32,
		m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33,

		m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30,
		m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31,
		m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32,
		m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33,

		m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30,
		m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31,
		m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32,
		m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33
	);
}

Matrix4x4 Matrix4x4::Identity()
{
	return Matrix4x4
	(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::CreateScale(const float& x, const float& y, const float& z)
{
	Matrix4x4 scale;

	scale.m00 = x;
	scale.m11 = y;
	scale.m22 = z;

	return scale;
}

Matrix4x4 Matrix4x4::CreateScale(const Vector3& vector)
{
	return CreateScale(vector.x, vector.y, vector.z);
}

Matrix4x4 Matrix4x4::CreateRotation(const Matrix4x4& matrix)
{
	Matrix4x4 r;

	r.m00 = matrix.m00;
	r.m01 = matrix.m01;
	r.m02 = matrix.m02;

	r.m10 = matrix.m10;
	r.m11 = matrix.m11;
	r.m12 = matrix.m12;

	r.m20 = matrix.m20;
	r.m21 = matrix.m21;
	r.m22 = matrix.m22;

	return r;
}

Quaternion Matrix4x4::GetRotation(const Matrix4x4& m)
{
	float trace = m.m00 + m.m11 + m.m22;
	Quaternion q;

	if (trace > 0.0f)
	{
		float s = std::sqrt(trace + 1.0f) * 2.0f;
		q.w = 0.25f * s;
		q.x = (m.m21 - m.m12) / s;
		q.y = (m.m02 - m.m20) / s;
		q.z = (m.m10 - m.m01) / s;
	}
	else if (m.m00 > m.m11 && m.m00 > m.m22)
	{
		float s = std::sqrt(1.0f + m.m00 - m.m11 - m.m22) * 2.0f;
		q.w = (m.m21 - m.m12) / s;
		q.x = 0.25f * s;
		q.y = (m.m01 + m.m10) / s;
		q.z = (m.m02 + m.m20) / s;
	}
	else if (m.m11 > m.m22)
	{
		float s = std::sqrt(1.0f + m.m11 - m.m00 - m.m22) * 2.0f;
		q.w = (m.m02 - m.m20) / s;
		q.x = (m.m01 + m.m10) / s;
		q.y = 0.25f * s;
		q.z = (m.m12 + m.m21) / s;
	}
	else
	{
		float s = std::sqrt(1.0f + m.m22 - m.m00 - m.m11) * 2.0f;
		q.w = (m.m10 - m.m01) / s;
		q.x = (m.m02 + m.m20) / s;
		q.y = (m.m12 + m.m21) / s;
		q.z = 0.25f * s;
	}

	return q;
}

Matrix4x4 Matrix4x4::CreateRotation(const float& x, const float& y, const float& z, const float& w)
{
	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;

	Matrix4x4 m;
	m.m00 = 1.0f - 2.0f * (yy + zz);
	m.m01 = 2.0f * (xy - wz);
	m.m02 = 2.0f * (xz + wy);

	m.m10 = 2.0f * (xy + wz);
	m.m11 = 1.0f - 2.0f * (xx + zz);
	m.m12 = 2.0f * (yz - wx);

	m.m20 = 2.0f * (xz - wy);
	m.m21 = 2.0f * (yz + wx);
	m.m22 = 1.0f - 2.0f * (xx + yy);

	return m;
}

Matrix4x4 Matrix4x4::CreateRotation(const Quaternion& q)
{
	return CreateRotation(q.x, q.y, q.z, q.w);
}

Matrix4x4 Matrix4x4::CreateTranslate(const float& x, const float& y, const float& z)
{
	Matrix4x4 translate;

	translate.m03 = x;
	translate.m13 = y;
	translate.m23 = z;

	return translate;
}

Matrix4x4 Matrix4x4::CreateTranslate(const Vector3& vector)
{
	return CreateTranslate(vector.x, vector.y, vector.z);
}

Matrix4x4 Matrix4x4::TRS(const Vector3& t, const Quaternion& r, const Vector3& s)
{
	const Matrix4x4 translate = CreateTranslate(t);
	const Matrix4x4 rotate = CreateRotation(r);
	const Matrix4x4 scale = CreateScale(s);

	return TRS(translate, rotate, scale);
}

Matrix4x4 Matrix4x4::TRS(const Matrix4x4& t, const Matrix4x4& r, const Matrix4x4& s)
{
	return t * r * s;
}
