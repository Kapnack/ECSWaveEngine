#pragma once

#include "WaveMath/Vector3/Vector3.h"

namespace WaveEngine
{
	struct BoundingBox final
	{
	private:

		Vector3 min = Vector3::Zero();
		Vector3 max = Vector3::Zero();

	public:

		BoundingBox();
		BoundingBox(Vector3 center, Vector3 size);
		~BoundingBox();

		void Encapsulate(const BoundingBox& boundingBox);
		void Encapsulate(Vector3 point);

		void SetMinMax(Vector3 vectorA, Vector3 vectorB);

		void SetMin(Vector3 min);
		void SetMax(Vector3 max);
		void SetCenter(Vector3 center);

		bool IsEmpty() const;

		void Reset();

		Vector3 GetCenter() const;
		Vector3 GetSize() const;
		Vector3 GetExtents() const;
		Vector3 GetMin() const;
		Vector3 GetMax() const;

		bool Intersects(const BoundingBox& other) const;
	};
}