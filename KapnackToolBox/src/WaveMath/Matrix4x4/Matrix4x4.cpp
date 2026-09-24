#include "Matrix4x4.h"

#include <cmath>

#include <stdexcept> 
#include "WaveMath/WaveMath/WaveMath.h"

Matrix4x4::Matrix4x4()
{
	*this = Identity();
}

Matrix4x4::Matrix4x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02; this->m03 = m03;
	this->m10 = m10; this->m11 = m11; this->m12 = m12; this->m13 = m13;
	this->m20 = m20; this->m21 = m21; this->m22 = m22; this->m23 = m23;
	this->m30 = m30; this->m31 = m31; this->m32 = m32; this->m33 = m33;
}

Matrix4x4::Matrix4x4(Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3)
{
	m00 = q0.x; m01 = q0.y; m02 = q0.z; m03 = q0.w;
	m10 = q1.x; m11 = q1.y; m12 = q1.z; m13 = q1.w;
	m20 = q2.x; m21 = q2.y; m22 = q2.z; m23 = q2.w;
	m30 = q3.x; m31 = q3.y; m32 = q3.z; m33 = q3.w;
}

Matrix4x4::~Matrix4x4()
{
}

void Matrix4x4::SetTranslate(Vector3 vector)
{
	m03 = vector.x;
	m13 = vector.y;
	m23 = vector.z;
}

void Matrix4x4::AddTranslate(Vector3 vector)
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

Vector3 Matrix4x4::GetTranslate() const
{
	return GetTranslate(*this);
}

Quaternion Matrix4x4::GetRotation() const
{
	return GetRotation(*this);
}

Vector3 Matrix4x4::GetScale() const
{
	return GetScale(*this);
}

void Matrix4x4::SetScale(Vector3 vector)
{
	m00 = vector.x;
	m11 = vector.y;
	m22 = vector.z;
}

void Matrix4x4::AddScale(Vector3 vector)
{
	m00 *= vector.x;
	m11 *= vector.y;
	m22 *= vector.z;
}

Matrix4x4 Matrix4x4::GetScaleMatrix() const
{
	return CreateScale(m00, m11, m22);
}

void Matrix4x4::Decomposed(Vector3& translation, Quaternion& rotation, Vector3& scale)
{
	Decompose(*this, translation, rotation, scale);
}

void Matrix4x4::Decomposed(Vector3& translation, Vector3& rotation, Vector3& scale)
{
	Decompose(*this, translation, rotation, scale);
}

void Matrix4x4::Transpose()
{
	*this = Transposed();
}

Matrix4x4 Matrix4x4::Transposed() const
{
	return Transposed(*this);
}

Vector3 Matrix4x4::GetFoward() const
{
	return GetFoward(*this);
}

Vector3 Matrix4x4::GetBack() const
{
	return GetBack(*this);
}

Vector3 Matrix4x4::GetRight() const
{
	return GetRight(*this);
}

Vector3 Matrix4x4::GetLeft() const
{
	return GetLeft(*this);
}

Vector3 Matrix4x4::GetUP() const
{
	return GetUP(*this);
}

Vector3 Matrix4x4::GetDown() const
{
	return GetDown(*this);
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

Matrix4x4 Matrix4x4::CreateScale(float x, float y, float z)
{
	Matrix4x4 scale;

	scale.m00 = x;
	scale.m11 = y;
	scale.m22 = z;

	return scale;
}

Matrix4x4 Matrix4x4::CreateScale(Vector3 vector)
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
		float s = WaveMath::Sqrt(trace + 1.0f) * 2.0f;
		q.w = 0.25f * s;
		q.x = (m.m21 - m.m12) / s;
		q.y = (m.m02 - m.m20) / s;
		q.z = (m.m10 - m.m01) / s;
	}
	else if (m.m00 > m.m11 && m.m00 > m.m22)
	{
		float s = WaveMath::Sqrt(1.0f + m.m00 - m.m11 - m.m22) * 2.0f;
		q.w = (m.m21 - m.m12) / s;
		q.x = 0.25f * s;
		q.y = (m.m01 + m.m10) / s;
		q.z = (m.m02 + m.m20) / s;
	}
	else if (m.m11 > m.m22)
	{
		float s = WaveMath::Sqrt(1.0f + m.m11 - m.m00 - m.m22) * 2.0f;
		q.w = (m.m02 - m.m20) / s;
		q.x = (m.m01 + m.m10) / s;
		q.y = 0.25f * s;
		q.z = (m.m12 + m.m21) / s;
	}
	else
	{
		float s = WaveMath::Sqrt(1.0f + m.m22 - m.m00 - m.m11) * 2.0f;
		q.w = (m.m10 - m.m01) / s;
		q.x = (m.m02 + m.m20) / s;
		q.y = (m.m12 + m.m21) / s;
		q.z = 0.25f * s;
	}

	return q;
}

Vector3 Matrix4x4::GetTranslate(const Matrix4x4& matrix)
{
	return Vector3(matrix.m03, matrix.m13, matrix.m23);
}

Vector3 Matrix4x4::GetScale(const Matrix4x4& matrix)
{
	return Vector3(matrix.m00, matrix.m11, matrix.m22);
}

Matrix4x4 Matrix4x4::CreateRotation(Quaternion q)
{
	return CreateRotation(q.x, q.y, q.z, q.w);
}

Matrix4x4 Matrix4x4::CreateRotation(float x, float y, float z, float w)
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

Matrix4x4 Matrix4x4::CreateTranslate(Vector3 vector)
{
	return CreateTranslate(vector.x, vector.y, vector.z);
}

Matrix4x4 Matrix4x4::CreateTranslate(float x, float y, float z)
{
	Matrix4x4 translate;

	translate.m03 = x;
	translate.m13 = y;
	translate.m23 = z;

	return translate;
}

Vector3 Matrix4x4::GetFoward(const Matrix4x4& matrix)
{
	return Vector3(matrix.m02, matrix.m12, matrix.m22).Normalized();
}

Vector3 Matrix4x4::GetBack(const Matrix4x4& matrix)
{
	return -GetFoward(matrix);
}

Vector3 Matrix4x4::GetRight(const Matrix4x4& matrix)
{
	return -Vector3(matrix.m00, matrix.m10, matrix.m20).Normalized();
}

Vector3 Matrix4x4::GetLeft(const Matrix4x4& matrix)
{
	return -GetRight(matrix);
}

Vector3 Matrix4x4::GetUP(const Matrix4x4& matrix)
{
	return Vector3(matrix.m01, matrix.m11, matrix.m21).Normalized();
}

Vector3 Matrix4x4::GetDown(const Matrix4x4& matrix)
{
	return -GetUP(matrix);
}

Matrix4x4 Matrix4x4::TRS(Vector3 t, Quaternion r, Vector3 s)
{
	const Matrix4x4 translate = CreateTranslate(t);
	const Matrix4x4 rotate = CreateRotation(r);
	const Matrix4x4 scale = CreateScale(s);

	return TRS(translate, rotate, scale);
}

Matrix4x4 Matrix4x4::Inversed(const Matrix4x4& matrix)
{
	const float s0 = matrix.m00 * matrix.m11 - matrix.m10 * matrix.m01;
	const float s1 = matrix.m00 * matrix.m12 - matrix.m10 * matrix.m02;
	const float s2 = matrix.m00 * matrix.m13 - matrix.m10 * matrix.m03;
	const float s3 = matrix.m01 * matrix.m12 - matrix.m11 * matrix.m02;
	const float s4 = matrix.m01 * matrix.m13 - matrix.m11 * matrix.m03;
	const float s5 = matrix.m02 * matrix.m13 - matrix.m12 * matrix.m03;

	const float c0 = matrix.m20 * matrix.m31 - matrix.m30 * matrix.m21;
	const float c1 = matrix.m20 * matrix.m32 - matrix.m30 * matrix.m22;
	const float c2 = matrix.m20 * matrix.m33 - matrix.m30 * matrix.m23;
	const float c3 = matrix.m21 * matrix.m32 - matrix.m31 * matrix.m22;
	const float c4 = matrix.m21 * matrix.m33 - matrix.m31 * matrix.m23;
	const float c5 = matrix.m22 * matrix.m33 - matrix.m32 * matrix.m23;

	const float det = s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;

	if (WaveMath::Abs(det) < 1e-8f)
		throw std::runtime_error("Matrix4x4::Inverse - matrix is singular and cannot be inverted");

	const float invDet = 1.0f / det;

	Matrix4x4 result;

	result.m00 = (matrix.m11 * c5 - matrix.m12 * c4 + matrix.m13 * c3) * invDet;
	result.m01 = (-matrix.m01 * c5 + matrix.m02 * c4 - matrix.m03 * c3) * invDet;
	result.m02 = (matrix.m31 * s5 - matrix.m32 * s4 + matrix.m33 * s3) * invDet;
	result.m03 = (-matrix.m21 * s5 + matrix.m22 * s4 - matrix.m23 * s3) * invDet;

	result.m10 = (-matrix.m10 * c5 + matrix.m12 * c2 - matrix.m13 * c1) * invDet;
	result.m11 = (matrix.m00 * c5 - matrix.m02 * c2 + matrix.m03 * c1) * invDet;
	result.m12 = (-matrix.m30 * s5 + matrix.m32 * s2 - matrix.m33 * s1) * invDet;
	result.m13 = (matrix.m20 * s5 - matrix.m22 * s2 + matrix.m23 * s1) * invDet;

	result.m20 = (matrix.m10 * c4 - matrix.m11 * c2 + matrix.m13 * c0) * invDet;
	result.m21 = (-matrix.m00 * c4 + matrix.m01 * c2 - matrix.m03 * c0) * invDet;
	result.m22 = (matrix.m30 * s4 - matrix.m31 * s2 + matrix.m33 * s0) * invDet;
	result.m23 = (-matrix.m20 * s4 + matrix.m21 * s2 - matrix.m23 * s0) * invDet;

	result.m30 = (-matrix.m10 * c3 + matrix.m11 * c1 - matrix.m12 * c0) * invDet;
	result.m31 = (matrix.m00 * c3 - matrix.m01 * c1 + matrix.m02 * c0) * invDet;
	result.m32 = (-matrix.m30 * s3 + matrix.m31 * s1 - matrix.m32 * s0) * invDet;
	result.m33 = (matrix.m20 * s3 - matrix.m21 * s1 + matrix.m22 * s0) * invDet;

	return result;
}

Matrix4x4 Matrix4x4::Transposed(const Matrix4x4& matrix)
{
	return Matrix4x4
	(
		matrix.m00, matrix.m10, matrix.m20, matrix.m30,
		matrix.m01, matrix.m11, matrix.m21, matrix.m31,
		matrix.m02, matrix.m12, matrix.m22, matrix.m32,
		matrix.m03, matrix.m13, matrix.m23, matrix.m33
	);
}

Matrix4x4 Matrix4x4::TRS(const Matrix4x4& t, const Matrix4x4& r, const Matrix4x4& s)
{
	return t * r * s;
}

void Matrix4x4::Decompose(const Matrix4x4& matrix, Vector3& translation, Quaternion& rotation, Vector3& scale)
{
	translation = matrix.GetTranslate();
	rotation = matrix.GetRotation();
	scale = matrix.GetScale();
}

void Matrix4x4::Decompose(const Matrix4x4& matrix, Vector3& translation, Vector3& rotation, Vector3& scale)
{
	Quaternion temRotation;
	Decompose(matrix, translation, temRotation, scale);
	rotation = temRotation.ToEuler();
}

Matrix4x4 Matrix4x4::CreateLookAt(Vector3 eye, Vector3 center, Vector3 up)
{
	Vector3 f = (center - eye).Normalized();
	Vector3 r = Vector3::Cross(f, up);

	if (r.SqrMagnitude() < WaveMath::Epsilon())
		r = Vector3::Cross(f, WaveMath::Abs(f.y) < 0.999f ? Vector3::Up() : Vector3::Right());

	r = r.Normalized();
	Vector3 u = Vector3::Cross(r, f);

	return Matrix4x4
	(
		r.x, r.y, r.z, -Vector3::Dot(r, eye),
		u.x, u.y, u.z, -Vector3::Dot(u, eye),
		-f.x, -f.y, -f.z, Vector3::Dot(f, eye),
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::CreatePerspective(float fovYRadians, float aspectRatio, float zNear, float zFar)
{
	if (WaveMath::Abs(zFar - zNear) < WaveMath::Epsilon())
		throw std::runtime_error("Matrix4x4::CreatePerspective - zNear and zFar too close");

	const float tanHalfFovY = std::tan(fovYRadians * 0.5f);

	const float sx = 1.0f / (aspectRatio * tanHalfFovY);
	const float sy = 1.0f / tanHalfFovY;

	const float A = (zFar + zNear) / (zNear - zFar);
	const float B = (2.0f * zFar * zNear) / (zNear - zFar);

	return Matrix4x4
	(
		sx, 0.0f, 0.0f, 0.0f,
		0.0f, sy, 0.0f, 0.0f,
		0.0f, 0.0f, A, B,
		0.0f, 0.0f, -1.0f, 0.0f
	);
}

Matrix4x4 Matrix4x4::CreateOrthographic(float left, float right, float bottom, float top, float zNear, float zFar)
{
	const float sx = 2.0f / (right - left);
	const float sy = 2.0f / (top - bottom);
	const float sz = -2.0f / (zFar - zNear);

	const float tx = -(right + left) / (right - left);
	const float ty = -(top + bottom) / (top - bottom);
	const float tz = -(zFar + zNear) / (zFar - zNear);

	return Matrix4x4
	(
		sx, 0.0f, 0.0f, tx,
		0.0f, sy, 0.0f, ty,
		0.0f, 0.0f, sz, tz,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}