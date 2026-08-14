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

Vector2::Vector2(Vector3 vector3)
{
	x = vector3.x;
	y = vector3.y;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2 operator*(float scalar, Vector2 vector2)
{
	return Vector2(vector2.x * scalar, vector2.y * scalar);
}

void Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
}

void Vector2::operator=(Vector2 other)
{
	x = other.x;
	y = other.y;
}

void Vector2::operator=(Vector3 vector3)
{
	x = vector3.x;
	y = vector3.y;
}

Vector2 Vector2::operator-(Vector2 other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator+(Vector2 other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator/(Vector2 other) const
{
	return Vector2(x / other.x, y / other.y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator*(Vector2 other) const
{
	return Vector2(x * other.x, y * other.y);
}

bool Vector2::operator>(Vector2 other) const
{
	return x > other.x && y > other.y;
}

bool Vector2::operator<(Vector2 other) const
{
	return other > *this;
}

Vector2 Vector2::Min(Vector2 vectorA, Vector2 vectorB)
{
	const float x = vectorA.x < vectorB.x ? vectorA.x : vectorB.x;
	const float y = vectorA.y < vectorB.y ? vectorA.y : vectorB.y;

	return Vector2(x, y);
}

Vector2 Vector2::Max(Vector2 vectorA, Vector2 vectorB)
{
	const float x = vectorA.x > vectorB.x ? vectorA.x : vectorB.x;
	const float y = vectorA.y > vectorB.y ? vectorA.y : vectorB.y;

	return Vector2(x, y);
}

Vector2 Vector2::Zero()
{
	return Vector2(0.0f, 0.0f);
}

Vector2 Vector2::One()
{
	return Vector2(1.0f, 1.0f);
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