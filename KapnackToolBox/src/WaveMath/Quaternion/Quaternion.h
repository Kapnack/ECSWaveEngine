#pragma once

#include "Export.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Vector2/Vector2.h"

struct WAVEEXPORT Quaternion final
{
	float x;
	float y;
	float z;
	float w;

	Quaternion();
	Quaternion(Vector3 eulerAngles);
	Quaternion(Vector3 vector3, float w);
	Quaternion(float x, float y, float z, float w);
	~Quaternion();
	float Magnitude() const;
	float SqrMagnitude() const;
	void Normalize();
	Quaternion Normalized() const;
	Vector3 ToEuler() const;

	Quaternion operator+(Quaternion other) const;
	void operator+=(Quaternion other);
	Quaternion operator-(Quaternion other) const;
	void operator-=(Quaternion other);
	Vector3 operator* (Vector3 v) const;
	Quaternion operator* (Quaternion other) const;
	void operator*=(Quaternion other);
	Quaternion operator*(float scalar) const;
	friend Quaternion operator*(float scalar, Quaternion other);
	void operator*=(float scalar);
	Quaternion operator/(float scalar) const;
	friend Quaternion operator/(float scalar, Quaternion quaternion);
	void operator/=(float scalar);

	static Quaternion Identity();

	static float Magnitude(Quaternion a);
	static float SqrMagnitude(Quaternion a);
	static float Dot(Quaternion a, Quaternion b);
	static Quaternion Normalized(Quaternion a);
	static Quaternion AngleAxis(float angle, Vector3 axis);
	static Quaternion Lerp(Quaternion a, Quaternion b, float t);
	static Quaternion Slerp(Quaternion a, Quaternion b, float t);
	static Quaternion UnclampLerp(Quaternion a, Quaternion b, float t);
	static Quaternion Euler(float x, float y, float z = 0.0f);
	static Quaternion Euler(Vector3 eulerAngles);
	static Quaternion Euler(Vector2 eulerAngles);
	static Vector3 ToEuler(Quaternion quaternion);
	static Quaternion Conjugate(Quaternion a);
	static Quaternion Inverse(Quaternion a);
	static Quaternion LookAt(Vector3 target);
};

