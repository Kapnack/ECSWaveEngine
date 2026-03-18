#include "Vector2.h"

#include "WaveMath/Vector3/Vector3.h"

Vector2::Vector2()
{
}

Vector2::Vector2(const Vector2& other)
{
	x = other.x;
	y = other.y;
}

Vector2::Vector2(const Vector3& vector3)
{
	x = vector3.x;
	y = vector3.y;
}

Vector2::Vector2(const float& x, const float& y)
{
	this->x = x;
	this->y = y;
}

Vector2 operator*(const float& scalar, const Vector2 vector2)
{
	return Vector2(vector2.x * scalar, vector2.y * scalar);
}

void Vector2::operator*=(const float& scalar)
{
	x *= scalar;
	y *= scalar;
}

void Vector2::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;
}

void Vector2::operator=(const Vector3& vector3)
{
	x = vector3.x;
	y = vector3.y;
}

Vector2 Vector2::operator/(const Vector2& other)
{
	return Vector2(x / other.x, y / other.y);
}

Vector2 Vector2::operator*(const float& scalar)
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::Up()
{
	return Vector2(0.0f, 1.0f);
}

Vector2 Vector2::Down()
{
	return Vector2(0.0f, -1.0f);
}

Vector2 Vector2::Right()
{
	return Vector2(1.0f, 0.0f);
}

Vector2 Vector2::Left()
{
	return Vector2(-1.0f, 0.0f);
}