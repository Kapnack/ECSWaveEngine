#pragma once

#include "WaveMath/Vector2/Vector2.h"

namespace WaveEngine
{
	struct Square
	{
	private:

		Vector2 min = -Vector2::One() * 0.5f;
		Vector2 max = Vector2::One() * 0.5f;

	public:

		Square();
		Square(Vector2 center, Vector2 size);

		void Encapsulate(Square square);

		void SetMinMax(Vector2 vector2A, Vector2 vector2B);

		void SetMin(Vector2 min);
		void SetMax(Vector2 max);

		Vector2 GetSize() const;
		Vector2 GetExtends() const;
		Vector2 GetCenter() const;

		Vector2 GetMin() const;
		Vector2 GetMax() const;
	};
}