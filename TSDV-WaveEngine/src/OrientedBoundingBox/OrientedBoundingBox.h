#pragma once

#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Matrix4x4/Matrix4x4.h"

namespace WaveEngine
{
	class BoundingBox;

	class OrientedBoundingBox
	{
	private:

		Vector3 center;
		Vector3 extents;
		Vector3 XAxis;
		Vector3 YAxis;
		Vector3 ZAxis;

	public:

		OrientedBoundingBox();
		OrientedBoundingBox(Vector3 center, Vector3 extents, Vector3 XAxis, Vector3 YAxis, Vector3 ZAxis);

		Vector3 GetCenter() const;
		Vector3 GetExtents() const;
		Vector3 GetSize() const;
		Vector3 GetXAxis() const;
		Vector3 GetYAxis()const;
		Vector3 GetZAxis()const;

		void GetCorners(Vector3 cornes[8]) const;
		BoundingBox ToAABB() const;
		bool Contains(Vector3 point) const;
		Vector3 ClosestPoint(Vector3 point) const;
		bool Intersects(const OrientedBoundingBox& other) const;

		static OrientedBoundingBox FromAABB(BoundingBox local, Vector3 position, Vector3 axisX, Vector3 axisY, Vector3 axisZ);
		static OrientedBoundingBox FromPoints(const Vector3* pts, int count, Vector3 axisX, Vector3 axisY, Vector3 axisZ);
		static Matrix4x4 MakeMatrix(const OrientedBoundingBox& oob);
	};
}