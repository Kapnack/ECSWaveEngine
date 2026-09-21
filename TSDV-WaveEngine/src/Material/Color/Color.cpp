#include "Color.h"

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

	Color Color::ColorFromColor255(float r, float g, float b)
	{
		return Color(r / GetColor32MaxValue(), g / GetColor32MaxValue(), b / GetColor32MaxValue(), GetColor32MaxValue());
	}

	Color Color::ColorFromColor255(float r, float g, float b, float a)
	{
		return Color(r / GetColor32MaxValue(), g / GetColor32MaxValue(), b / GetColor32MaxValue(), a / GetColor32MaxValue());
	}

	Color Color::GetAsColor255()
	{
		return GetAsColor255(*this);
	}

	Color Color::GetAsColor255(Color color)
	{
		return Color(color.r * GetColor32MaxValue(), color.g * GetColor32MaxValue(), color.b * GetColor32MaxValue(), color.a * GetColor32MaxValue());
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
}
