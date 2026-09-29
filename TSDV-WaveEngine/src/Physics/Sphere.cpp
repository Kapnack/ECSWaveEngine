#include "Sphere.h"

#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/WaveMath/WaveMath.h"

namespace WaveEngine
{
	Sphere::Sphere(Vector3 center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}

	bool Sphere::Intersects(Sphere other) const
	{
		float sum = radius + other.radius;
		return (other.center - center).SqrMagnitude() <= sum * sum;
	}

	Sphere Sphere::ComputeBoundingSphere(Vector3 a, Vector3 b, Vector3 c)
	{
		float abSqr = (b - a).SqrMagnitude();
		float bcSqr = (c - b).SqrMagnitude();
		float caSqr = (a - c).SqrMagnitude();

		Vector3 p0 = a, p1 = b;
		float longestSqr = abSqr;
		float otherSumSqr = bcSqr + caSqr;

		if (bcSqr > longestSqr)
		{
			p0 = b; p1 = c;
			longestSqr = bcSqr;
			otherSumSqr = abSqr + caSqr;
		}

		if (caSqr > longestSqr)
		{
			p0 = c; p1 = a;
			longestSqr = caSqr;
			otherSumSqr = abSqr + bcSqr;
		}

		if (longestSqr >= otherSumSqr)
			return Sphere((p0 + p1) * 0.5f, WaveMath::SqrF(longestSqr) * 0.5f);

		return ComputeCircumsphere(a, b, c);
	}

	Sphere Sphere::ComputeCircumsphere(Vector3 a, Vector3 b, Vector3 c)
	{
		Vector3 u = b - a;
		Vector3 v = c - a;
		Vector3 n = Vector3::Cross(u, v);

		float nSqr = n.SqrMagnitude();

		if (nSqr < WaveMath::Epsilon() * WaveMath::Epsilon())
		{
			Vector3 centroid = (a + b + c) / 3.0f;

			float r = WaveMath::MaxF((a - centroid).Magnitude(), WaveMath::MaxF((b - centroid).Magnitude(), (c - centroid).Magnitude()));

			return Sphere(centroid, r);
		}

		Vector3 offset = (Vector3::Cross(v, n) * u.SqrMagnitude() + Vector3::Cross(n, u) * v.SqrMagnitude()) / (2.0f * nSqr);

		return Sphere(a + offset, offset.Magnitude());
	}
}
