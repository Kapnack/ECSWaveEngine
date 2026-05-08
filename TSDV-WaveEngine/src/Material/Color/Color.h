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

	static Color White()
	{
		return Color(1.0f, 1.0f, 1.0f, 1.0f);
	}

	static Color Black()
	{
		return Color(0.0f, 0.0f, 0.0f, 1.0f);
	}

	static Color Red()
	{
		return Color(1.0f, 0.0f, 0.0f, 1.0f);
	}

	static Color Green()
	{
		return Color(0.0f, 1.0f, 0.0f, 1.0f);
	}

	static Color Blue()
	{
		return Color(0.0f, 0.0f, 1.0f, 1.0f);
	}
};