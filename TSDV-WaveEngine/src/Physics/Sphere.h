#pragma once

#include "WaveMath/Vector3/Vector3.h"

namespace WaveEngine
{
	struct Sphere
	{
	public:

		Vector3 center;
		float radius;

		Sphere(Vector3 center, float radius);

		bool Intersects(Sphere other) const;

		static Sphere ComputeBoundingSphere(Vector3 a, Vector3 b, Vector3 c);

		static Sphere ComputeCircumsphere(Vector3 a, Vector3 b, Vector3 c);
	};
}