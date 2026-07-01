#pragma once

#include "Export.h"

struct Color
{
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 1.0f;

	Color()
	{
	}

	Color(const Color& color)
	{
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
		this->a = color.a;
	}

	Color(const float& r, const float& g, const float& b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	Color(const float& r, const float& g, const float& b, const float& a)
	{
		*this = Color(r, g, b);
		this->a = a;
	}

	static Color Color32(const float& r, const float& g, const float& b)
	{
		const float color32MaxValue = 255.0f;
		return Color(r / color32MaxValue, g / color32MaxValue, b / color32MaxValue);
	}

	static Color Color32(const float& r, const float& g, const float& b, const float& a)
	{
		const float color32MaxValue = 255.0f;
		return Color(r / color32MaxValue, g / color32MaxValue, b / color32MaxValue, a / color32MaxValue);
	}

	Color GetAsColor32()
	{
		const float color32MaxValue = 255.0f;
		return Color(r * color32MaxValue, g * color32MaxValue, b * color32MaxValue, a * color32MaxValue);
	}

	static Color White()
	{
		return Color(1.0f, 1.0f, 1.0f);
	}

	static Color Black()
	{
		return Color(0.0f, 0.0f, 0.0f);
	}

	static Color Red()
	{
		return Color(1.0f, 0.0f, 0.0f);
	}

	static Color Green()
	{
		return Color(0.0f, 1.0f, 0.0f);
	}

	static Color Blue()
	{
		return Color(0.0f, 0.0f, 1.0f);
	}

	static Color Yellow()
	{
		return Color(1.0f, 1.0f, 0.0f);
	}
};