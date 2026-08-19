#include "Square.h"

namespace WaveEngine
{
	Square::Square()
	{
	}

	Square::Square(Vector2 center, Vector2 size)
	{
		SetMinMax(center - size * 0.5f, center + size * 0.5f);
	}

	void Square::Encapsulate(Square square)
	{
		SetMinMax(Vector2::Min(min, square.min), Vector2::Max(max, square.max));
	}

	bool Square::Contains(Square square)
	{
		return square.min >= min && square.max <= max;
	}

	bool Square::Contains(Vector2 point)
	{
		return point >= min && point <= max;
	}

	void Square::SetMinMax(Vector2 vector2A, Vector2 vector2B)
	{
		min = Vector2::Min(vector2A, vector2B);
		max = Vector2::Max(vector2A, vector2B);
	}

	void Square::SetCenter(Vector2 center)
	{
		Vector2 extends = GetExtends();
		SetMinMax(center - extends, center + extends);
	}

	void Square::SetSize(Vector2 size)
	{
		Vector2 center = GetCenter();
		SetMinMax(center - size * 0.5f, center + size * 0.5f);
	}

	void Square::SetMin(Vector2 min)
	{
		SetMinMax(min, max);
	}

	void Square::SetMax(Vector2 max)
	{
		SetMinMax(min, max);
	}

	Vector2 Square::GetSize() const
	{
		return max - min;
	}

	Vector2 Square::GetCenter() const
	{
		return (max + min) * 0.5f;
	}

	Vector2 Square::GetExtends() const
	{
		return (max - min) * 0.5f;
	}
}
