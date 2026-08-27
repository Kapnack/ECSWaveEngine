#pragma once

#include "Export.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Vector2/Vector2.h"

WAVEEXPORT struct Quaternion final
{
	float x;
	float y;
	float z;
	float w;

	WAVEEXPORT Quaternion();
	WAVEEXPORT Quaternion(Vector3 eulerAngles);
	WAVEEXPORT Quaternion(Vector3 vector3, float w);
	WAVEEXPORT Quaternion(float x, float y, float z, float w);
	WAVEEXPORT ~Quaternion();
	WAVEEXPORT float Magnitude() const;
	WAVEEXPORT float SqrMagnitude() const;
	WAVEEXPORT void Normalize();
	WAVEEXPORT Quaternion Normalized() const;

	WAVEEXPORT Quaternion operator+(Quaternion other) const;
	WAVEEXPORT void operator+=(Quaternion other);
	WAVEEXPORT Quaternion operator-(Quaternion other) const;
	WAVEEXPORT void operator-=(Quaternion other);
	WAVEEXPORT Vector3 operator* (Vector3 v) const;
	WAVEEXPORT Quaternion operator* (Quaternion other) const;
	WAVEEXPORT void operator*=(Quaternion other);
	WAVEEXPORT Quaternion operator*(float scalar) const;
	WAVEEXPORT friend Quaternion operator*(float scalar, Quaternion other);
	WAVEEXPORT void operator*=(float scalar);
	WAVEEXPORT Quaternion operator/(float scalar) const;
	WAVEEXPORT friend Quaternion operator/(float scalar, Quaternion quaternion);
	WAVEEXPORT void operator/=(float scalar);

	WAVEEXPORT static Quaternion Identity();

	WAVEEXPORT static float Magnitude(Quaternion a);
	WAVEEXPORT static float SqrMagnitude(Quaternion a);
	WAVEEXPORT static float Dot(Quaternion a, Quaternion b);
	WAVEEXPORT static Quaternion Normalized(Quaternion a);
	WAVEEXPORT static Quaternion AngleAxis(float angle, Vector3 axis);
	WAVEEXPORT static Quaternion Lerp(Quaternion a, Quaternion b, float t);
	WAVEEXPORT static Quaternion Slerp(Quaternion a, Quaternion b, float t);
	WAVEEXPORT static Quaternion UnclampLerp(Quaternion a, Quaternion b, float t);
	WAVEEXPORT static Quaternion Euler(float x, float y, float z = 0.0f);
	WAVEEXPORT static Quaternion Euler(Vector3 eulerAngles);
	WAVEEXPORT static Quaternion Euler(Vector2 eulerAngles);
	WAVEEXPORT static Quaternion Conjugate(Quaternion a);
	WAVEEXPORT static Quaternion Inverse(Quaternion a);
};

