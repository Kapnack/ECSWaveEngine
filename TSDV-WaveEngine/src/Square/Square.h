#pragma once

#include "WaveMath/Vector2/Vector2.h"

namespace WaveEngine
{
	struct Square
	{
		Vector2 position = Vector2::Zero();
		Vector2 size = Vector2::One();
	};
}