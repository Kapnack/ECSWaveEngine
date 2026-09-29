#include "Triangle.h"

#include "Sphere.h"
#include "BoundingBox/BoundingBox.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/WaveMath/WaveMath.h"
#include "WaveMath/Matrix4x4/Matrix4x4.h"

namespace WaveEngine
{
	bool Triangle::IsDegenerate() const
	{
		return rawNormal.SqrMagnitude() < WaveMath::Epsilon() * WaveMath::Epsilon();
	}

	Vector3 Triangle::FaceNormal() const
	{
		return rawNormal.Normalized();
	}

	Vector3 Triangle::Centroid() const
	{
		return (pointA + pointB + pointC) / 3.0f;
	}

	Vector3 Triangle::GetPoint(int index) const
	{
		return index == 0 ? pointA : index == 1 ? pointB : pointC;
	}

	Triangle Triangle::Transformed(const Matrix4x4& matrix) const
	{
		return Triangle(matrix * pointA, matrix * pointB, matrix * pointC);
	}

	void Triangle::GetBounds(Vector3& min, Vector3& max) const
	{
		min = Vector3::Min(pointA, Vector3::Min(pointB, pointC));
		max = Vector3::Max(pointA, Vector3::Max(pointB, pointC));
	}

	bool Triangle::Intersects(Triangle triangle, BoundingBox boundingBox)
	{
		Vector3 min = boundingBox.GetMin();
		Vector3 max = boundingBox.GetMax();

		Sphere sphereBound = Sphere::ComputeBoundingSphere(triangle.pointA, triangle.pointB, triangle.pointC);

		float closestX = WaveMath::ClampF(sphereBound.center.x, min.x, max.x);
		float closestY = WaveMath::ClampF(sphereBound.center.y, min.y, max.y);
		float closestZ = WaveMath::ClampF(sphereBound.center.z, min.z, max.z);

		float dx = sphereBound.center.x - closestX;
		float dy = sphereBound.center.y - closestY;
		float dz = sphereBound.center.z - closestZ;

		return dx * dx + dy * dy + dz * dz <= sphereBound.radius * sphereBound.radius;
	}
}
