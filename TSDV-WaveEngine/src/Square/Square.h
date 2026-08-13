#pragma once

#include "WaveMath/Vector2/Vector2.h"

namespace WaveEngine
{
	struct Square
	{
		Vector2 position = Vector2::Zero();
		Vector2 size = Vector2::One();

		Vector2 min = -Vector2::One() * 0.5f;
		Vector2 max = Vector2::One() * 0.5f;
	};
}