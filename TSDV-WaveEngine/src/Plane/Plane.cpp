#include "Plane.h"

#include "WaveMath/Vector3/Vector3.h"

namespace WaveEngine
{
	Plane::Plane()
	{
		originDistance = 0.0f;
	}

	Plane::Plane(Vector3 normal)
	{
		SetNormal(normal);
	}

	Plane::Plane(Vector3 normal, Vector3 position)
	{
		this->normal = normal.Normalized();
		originDistance = Vector3::Dot(this->normal, position);
	}

	Plane Plane::BisectorPlane(Vector3 positionA, Vector3 positionB)
	{
		Vector3 dir = positionB - positionA;
		Vector3 mid = (positionA + positionB) * 0.5f;

		return Plane(dir, mid);
	}

	float Plane::SignedDistance(Vector3 position) const
	{
		return Vector3::Dot(normal, position) - originDistance;
	}

	void Plane::SetNormal(Vector3 normal)
	{
		*this = Plane(normal, this->normal * originDistance);
	}

	void Plane::SetPosition(Vector3 position)
	{
		originDistance = Vector3::Dot(normal, position);
	}

	Vector3 Plane::GetNormal() const
	{
		return normal;
	}

	float Plane::GetOriginDistance() const
	{
		return originDistance;
	}

	Vector3 Plane::GetPosition() const
	{
		return normal * originDistance;
	}

	bool Plane::operator==(Plane other) const
	{
		return normal == other.normal && originDistance == other.originDistance;
	}
}
