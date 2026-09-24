#include "Color.h"

#include "WaveMath/Vector4/Vector4.h"
#include "WaveMath/WaveMath/WaveMath.h"

namespace WaveEngine
{
	float Color::GetColor32MaxValue()
	{
		return 255.0f;
	}

	Color::Color()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 1.0f;
	}

	Color::Color(const Color& color)
	{
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
		this->a = color.a;
	}

	Color::Color(Vector3 vector)
	{
		this->r = vector.x;
		this->g = vector.y;
		this->b = vector.z;
		this->a = 1.0f;
	}

	Color::Color(Vector4 vector)
	{
		this->r = vector.x;
		this->g = vector.y;
		this->b = vector.z;
		this->a = vector.w;
	}

	Color::Color(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 1.0f;
	}

	Color::Color(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void Color::Normalize()
	{
		*this = Normalized();
	}

	Color Color::Normalized() const
	{
		return Normalized(*this);
	}

	float Color::Magnitude() const
	{
		return Magnitude(*this);
	}

	float Color::SqrMagnitude() const
	{
		return SqrMagnitude(*this);
	}

	bool Color::Approximately(Color other) const
	{
		return Approximately(*this, other);
	}

	Color Color::ColorFromColor255(Color color)
	{
		return ColorFromColor255(color.r, color.g, color.b, color.a);
	}

	Color Color::ColorFromColor255(float r, float g, float b)
	{
		return Color(r / GetColor32MaxValue(), g / GetColor32MaxValue(), b / GetColor32MaxValue());
	}

	Color Color::ColorFromColor255(float r, float g, float b, float a)
	{
		return Color(r / GetColor32MaxValue(), g / GetColor32MaxValue(), b / GetColor32MaxValue(), a / GetColor32MaxValue());
	}

	Color Color::GetAsColor255()
	{
		return Color255FromColor(*this);
	}

	Color Color::Color255FromColor(Color color)
	{
		return Color255FromColor(color.r, color.g, color.b, color.a);
	}

	Color Color::Color255FromColor(float r, float g, float b)
	{
		return Color(r * GetColor32MaxValue(), g * GetColor32MaxValue(), b * GetColor32MaxValue(), GetColor32MaxValue());
	}

	Color Color::Color255FromColor(float r, float g, float b, float a)
	{
		return Color(r * GetColor32MaxValue(), g * GetColor32MaxValue(), b * GetColor32MaxValue(), a * GetColor32MaxValue());
	}

	Color Color::White()
	{
		return Color(1.0f, 1.0f, 1.0f);
	}

	Color Color::Black()
	{
		return Color(0.0f, 0.0f, 0.0f);
	}

	Color Color::Red()
	{
		return Color(1.0f, 0.0f, 0.0f);
	}

	Color Color::Green()
	{
		return Color(0.0f, 1.0f, 0.0f);
	}

	Color Color::Blue()
	{
		return Color(0.0f, 0.0f, 1.0f);
	}

	Color Color::Yellow()
	{
		return Color(1.0f, 1.0f, 0.0f);
	}

	Color Color::Clear()
	{
		return Color(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Color Color::operator+(Color other) const
	{
		return Color(r + other.r, g + other.g, b + other.b, a + other.a);
	}

	void Color::operator+=(Color other)
	{
		*this = *this + other;
	}

	Color Color::operator-(Color other) const
	{
		return Color(r - other.r, g - other.g, b - other.b, a - other.a);
	}

	void Color::operator-=(Color other)
	{
		*this = *this - other;
	}

	Color Color::operator*(Color other) const
	{
		return Color(r * other.r, g * other.g, b * other.b, a * other.a);
	}

	Color Color::operator*(float scalar) const
	{
		return Color(r * scalar, g * scalar, b * scalar, a * scalar);
	}

	void Color::operator*=(Color other)
	{
		*this = *this * other;
	}

	void Color::operator*=(float scalar)
	{
		*this = *this * scalar;
	}

	Color Color::operator/(Color other) const
	{
		return Color(r / other.r, g / other.g, b / other.b, a / other.a);
	}

	Color Color::operator/(float scalar) const
	{
		return Color(r / scalar, g / scalar, b / scalar, a / scalar);
	}

	void Color::operator/=(Color other)
	{
		*this = *this / other;
	}

	void Color::operator/=(float scalar)
	{
		*this = *this / scalar;
	}

	bool Color::operator>(Color other) const
	{
		return r > other.r && g > other.g && b > other.b && a > other.a;
	}

	bool Color::operator<(Color other) const
	{
		return other > *this;
	}

	bool Color::operator==(Color other) const
	{
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}

	bool Color::operator!=(Color other) const
	{
		return !(*this == other);
	}

	Color::operator Vector4() const
	{
		return Vector4(r, g, b, a);
	}

	Color Color::Normalized(Color color)
	{
		float mag = color.Magnitude();

		if (mag < WaveMath::Epsilon())
			return Color::Clear();

		if (WaveMath::Abs(mag - 1.0f) < WaveMath::Epsilon())
			return color;

		return color / mag;
	}

	float Color::Magnitude(Color color)
	{
		return WaveMath::SqrF(SqrMagnitude(color));
	}

	float Color::SqrMagnitude(Color color)
	{
		return Dot(color, color);
	}

	float Color::Dot(Color a, Color b)
	{
		return a.r * b.r + a.g * b.g + a.b * b.b + a.a * b.a;
	}

	bool Color::Approximately(Color a, Color b)
	{
		return WaveMath::Approximately(a.r, b.r) && WaveMath::Approximately(a.g, b.g) && WaveMath::Approximately(a.b, b.b) && WaveMath::Approximately(a.a, b.a);
	}

	Color operator*(float scalar, Color color)
	{
		return color * scalar;
	}

	Color operator/(float scalar, Color color)
	{
		return color / scalar;
	}
}
