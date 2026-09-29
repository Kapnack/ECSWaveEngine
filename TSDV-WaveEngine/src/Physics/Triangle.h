#pragma once

#include "BoundingBox/BoundingBox.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Matrix4x4/Matrix4x4.h"

namespace WaveEngine
{
	struct Triangle
	{
	public:

		Vector3 pointA;
		Vector3 pointB;
		Vector3 pointC;

		Vector3 rawNormal;

		Triangle(Vector3 pointA, Vector3 pointB, Vector3 pointC)
		{
			this->pointA = pointA;
			this->pointB = pointB;
			this->pointC = pointC;

			this->rawNormal = Vector3::Cross(pointB - pointA, pointC - pointA);
		}

		bool IsDegenerate() const;

		Vector3 FaceNormal() const;

		Vector3 Centroid() const;

		Vector3 GetPoint(int index) const;

		Triangle Transformed(const Matrix4x4& matrix) const;

		void GetBounds(Vector3& min, Vector3& max) const;

		static bool Intersects(Triangle triangle, BoundingBox boundingBox);
	};
}