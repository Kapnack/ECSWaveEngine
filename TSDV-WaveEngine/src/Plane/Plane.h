#pragma once

#include "WaveMath/Vector3/Vector3.h"

namespace WaveEngine
{
	struct Plane
	{
	private:

		Vector3 normal;
		float originDistance;

	public:

		Plane();
		Plane(Vector3 normal);
		Plane(Vector3 normal, Vector3 center);
		static Plane BisectorPlane(Vector3 positionA, Vector3 positionB);

		float SignedDistance(Vector3 position) const;

		void SetNormal(Vector3 normal);
		void SetPosition(Vector3 position);

		Vector3 GetNormal() const;
		float GetOriginDistance() const;
		Vector3 GetPosition() const;

		bool operator==(Plane other) const;
	};
}