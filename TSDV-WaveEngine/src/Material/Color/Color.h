#pragma once

#include "Export.h"

namespace WaveEngine
{
	struct WAVEEXPORT Color
	{
	private:

		static float GetColor32MaxValue();

	public:

		float r;
		float g;
		float b;
		float a;

		Color();

		Color(const Color& color);

		Color(float r, float g, float b);

		Color(float r, float g, float b, float a);

		static Color ColorFromColor255(float r, float g, float b);

		static Color ColorFromColor255(float r, float g, float b, float a);

		Color GetAsColor255();

		static Color GetAsColor255(Color color);

		static Color White();

		static Color Black();

		static Color Red();

		static Color Green();

		static Color Blue();

		static Color Yellow();

		static Color Clear();
	};
}