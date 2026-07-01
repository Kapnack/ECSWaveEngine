#include "BoundingBox.h"
#include <cfloat>

namespace WaveEngine
{
	BoundingBox::BoundingBox()
	{
		Reset();
	}

	BoundingBox::BoundingBox(const Vector3& center, const Vector3& size)
	{
		this->center = center;
		this->size = size;
		this->min = center - size * 0.5f;
		this->max = center + size * 0.5f;
	}

	BoundingBox::~BoundingBox()
	{
	}

	void BoundingBox::Reset()
	{
		min = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		max = Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		center = Vector3(0, 0, 0);
		size = Vector3(0, 0, 0);
	}

	void BoundingBox::Encapsulate(const BoundingBox& boundingBox)
	{
		if (boundingBox.IsEmpty())
			return;

		Vector3 min = Vector3::Min(this->min, boundingBox.GetMin());
		Vector3 max = Vector3::Max(this->max, boundingBox.GetMax());

		SetMinMax(min, max);
	}

	bool BoundingBox::IsEmpty() const
	{
		return min.x > max.x || min.y > max.y || min.z > max.z;
	}


	void BoundingBox::Encapsulate(const Vector3& point)
	{
		Vector3 min = Vector3::Min(this->min, point);
		Vector3 max = Vector3::Max(this->max, point);

		SetMinMax(min, max);
	}

	void BoundingBox::SetMinMax(const Vector3& vectorA, const Vector3& vectorB)
	{
		min = Vector3::Min(vectorA, vectorB);
		max = Vector3::Max(vectorA, vectorB);

		center = (min + max) * 0.5f;
		size = max - min;
	}

	void BoundingBox::SetMin(const Vector3& min)
	{
		this->min = min;
		center = (min + max) * 0.5f;
		size = max - min;
	}

	void BoundingBox::SetMax(const Vector3& max)
	{
		this->max = max;
		center = (min + max) * 0.5f;
		size = max - min;
	}

	void BoundingBox::SetCenter(const Vector3& center)
	{
		Vector3 half = size * 0.5f;
		this->center = center;
		min = center - half;
		max = center + half;
	}

	const Vector3& BoundingBox::GetCenter() const
	{
		return center;
	}

	const Vector3& BoundingBox::GetSize() const
	{
		return size;
	}

	const Vector3& BoundingBox::GetMin() const
	{
		return min;
	}

	const Vector3& BoundingBox::GetMax() const
	{
		return max;
	}
}