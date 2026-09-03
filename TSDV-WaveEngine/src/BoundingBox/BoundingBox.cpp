#include "BoundingBox.h"

#include <cstdlib>

#include "WaveMath/Vector3/Vector3.h"

namespace WaveEngine
{
	BoundingBox::BoundingBox()
	{
		Reset();
	}

	BoundingBox::BoundingBox(Vector3 center, Vector3 size)
	{
		SetMinMax(center - size * 0.5f, center + size * 0.5f);
	}

	BoundingBox::~BoundingBox()
	{
	}

	void BoundingBox::Reset()
	{
		min = Vector3::Max();
		max = Vector3::NMax();
	}

	void BoundingBox::Encapsulate(const BoundingBox& boundingBox)
	{
		if (boundingBox.IsEmpty())
			return;

		SetMinMax(Vector3::Min(this->min, boundingBox.GetMin()), Vector3::Max(this->max, boundingBox.GetMax()));
	}

	bool BoundingBox::IsEmpty() const
	{
		return min.x > max.x || min.y > max.y || min.z > max.z;
	}

	void BoundingBox::Encapsulate(Vector3 point)
	{
		SetMinMax(Vector3::Min(this->min, point), Vector3::Max(this->max, point));
	}

	void BoundingBox::SetMinMax(Vector3 vectorA, Vector3 vectorB)
	{
		min = Vector3::Min(vectorA, vectorB);
		max = Vector3::Max(vectorA, vectorB);
	}

	void BoundingBox::SetMin(Vector3 min)
	{
		this->min = min;
	}

	void BoundingBox::SetMax(Vector3 max)
	{
		this->max = max;
	}

	void BoundingBox::SetSize(Vector3 size)
	{
		Vector3 center = GetCenter();
		SetMinMax(center - size * 0.5f, center + size * 0.5f);
	}

	void BoundingBox::SetCenter(Vector3 center)
	{
		Vector3 half = GetExtents();
		min = center - half;
		max = center + half;
	}

	Vector3 BoundingBox::GetCenter() const
	{
		return (max + min) * 0.5f;
	}

	Vector3 BoundingBox::GetSize() const
	{
		return max - min;
	}

	Vector3 BoundingBox::GetExtents() const
	{
		return (max - min) * 0.5f;
	}

	Vector3 BoundingBox::GetMin() const
	{
		return min;
	}

	Vector3 BoundingBox::GetMax() const
	{
		return max;
	}

	bool BoundingBox::Intersects(const BoundingBox& other) const
	{
		return std::abs(GetCenter().x - other.GetCenter().x) <= (GetSize().x + other.GetSize().x) * 0.5f &&
			std::abs(GetCenter().y - other.GetCenter().y) <= (GetSize().y + other.GetSize().y) * 0.5f &&
			std::abs(GetCenter().z - other.GetCenter().z) <= (GetSize().z + other.GetSize().z) * 0.5f;
	}
}