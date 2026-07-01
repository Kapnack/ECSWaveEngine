#pragma once

#include "WaveMath/Vector3/Vector3.h"

namespace WaveEngine
{
	struct BoundingBox final
	{
	private:

		Vector3 center = Vector3::Zero();
		Vector3 size = Vector3::Zero();
		Vector3 min = Vector3::Zero();
		Vector3 max = Vector3::Zero();

	public:

		BoundingBox();
		BoundingBox(const Vector3& center, const Vector3& size);
		~BoundingBox();

		void Encapsulate(const BoundingBox& boundingBox);
		void Encapsulate(const Vector3& point);

		void SetMinMax(const Vector3& vectorA, const Vector3& vectorB);

		void SetMin(const Vector3& min);
		void SetMax(const Vector3& max);
		void SetCenter(const Vector3& center);

		void Reset();

		bool IsEmpty() const;

		const Vector3& GetCenter() const;
		const Vector3& GetSize() const;
		const Vector3& GetMin() const;
		const Vector3& GetMax() const;
	};
}