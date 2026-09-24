#pragma once

#include "Export.h"

#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Vector4/Vector4.h"

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
		Color(Vector3 vector);
		Color(Vector4 vector);
		Color(float r, float g, float b);
		Color(float r, float g, float b, float a);

		void Normalize();
		Color Normalized() const;
		float Magnitude() const;
		float SqrMagnitude() const;
		bool Approximately(Color other) const;

		static Color ColorFromColor255(Color color);
		static Color ColorFromColor255(float r, float g, float b);
		static Color ColorFromColor255(float r, float g, float b, float a);

		Color GetAsColor255();
		static Color Color255FromColor(Color color);
		static Color Color255FromColor(float r, float g, float b);
		static Color Color255FromColor(float r, float g, float b, float a);

		static Color White();
		static Color Black();
		static Color Red();
		static Color Green();
		static Color Blue();
		static Color Yellow();
		static Color Clear();

		Color operator+(Color other) const;
		void operator+=(Color other);
		Color operator-(Color other) const;
		void operator-=(Color other);
		Color operator*(Color other) const;
		Color operator*(float scalar) const;
		friend Color operator*(float scalar, Color color);
		void operator*=(Color other);
		void operator*=(float scalar);
		Color operator/(Color other) const;
		Color operator/(float scalar) const;
		friend Color operator/(float scalar, Color color);
		void operator/=(Color other);
		void operator/=(float scalar);
		bool operator>(Color other) const;
		bool operator<(Color other) const;
		bool operator==(Color other) const;
		bool operator!=(Color other) const;

		operator Vector4() const;

		static Color Normalized(Color color);
		static float Magnitude(Color color);
		static float SqrMagnitude(Color color);
		static float Dot(Color a, Color b);
		static bool Approximately(Color a, Color b);
	};
}