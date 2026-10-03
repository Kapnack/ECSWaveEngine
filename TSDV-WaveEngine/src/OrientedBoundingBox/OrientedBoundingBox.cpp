#include "OrientedBoundingBox.h"

#include "BoundingBox/BoundingBox.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/WaveMath/WaveMath.h"
#include "WaveMath/Matrix4x4/Matrix4x4.h"

namespace WaveEngine
{
	OrientedBoundingBox::OrientedBoundingBox()
	{
	}

	OrientedBoundingBox::OrientedBoundingBox(Vector3 center, Vector3 extends, Vector3 XAxis, Vector3 YAxis, Vector3 ZAxis)
	{
		this->center = center;
		this->extents = extends * 0.5f;
		this->XAxis = XAxis;
		this->YAxis = YAxis;
		this->ZAxis = ZAxis;
	}

	Vector3 OrientedBoundingBox::GetCenter() const
	{
		return center;
	}

	Vector3 OrientedBoundingBox::GetExtents() const
	{
		return extents;
	}

	Vector3 OrientedBoundingBox::GetSize() const
	{
		return extents * 2;
	}

	Vector3 OrientedBoundingBox::GetXAxis() const
	{
		return XAxis;
	}

	Vector3 OrientedBoundingBox::GetYAxis() const
	{
		return YAxis;
	}

	Vector3 OrientedBoundingBox::GetZAxis() const
	{
		return ZAxis;
	}

	void OrientedBoundingBox::GetCorners(Vector3 corners[8]) const
	{
		Vector3 x = XAxis * extents.x;
		Vector3 y = YAxis * extents.y;
		Vector3 z = ZAxis * extents.z;
		int i = 0;

		for (int sx = -1; sx <= 1; sx += 2)
			for (int sy = -1; sy <= 1; sy += 2)
				for (int sz = -1; sz <= 1; sz += 2)
					corners[i++] = center + x * static_cast<float>(sx) + y * static_cast<float>(sy) + z * static_cast<float>(sz);
	}

	BoundingBox OrientedBoundingBox::ToAABB() const
	{
		Vector3 extends;

		extends += Vector3::Abs(XAxis) * extents.x + Vector3::Abs(YAxis) * extents.y * Vector3::Abs(ZAxis) * extents.y;

		return BoundingBox(center, extends * 2.0f);
	}

	bool OrientedBoundingBox::Contains(Vector3 point) const
	{
		Vector3 direction = point - center;

		if (WaveMath::Abs(Vector3::Dot(direction, XAxis)) > extents.x)
			return false;

		if (WaveMath::Abs(Vector3::Dot(direction, YAxis)) > extents.y)
			return false;

		if (WaveMath::Abs(Vector3::Dot(direction, ZAxis)) > extents.z)
			return false;

		return true;
	}

	Vector3 OrientedBoundingBox::ClosestPoint(Vector3 point) const
	{
		Vector3 d = point - center;
		Vector3 result = center;

		float dist = WaveMath::ClampF(Vector3::Dot(d, XAxis), -extents.x, extents.x);
		result += XAxis * dist;

		dist = WaveMath::ClampF(Vector3::Dot(d, YAxis), -extents.y, extents.y);
		result += YAxis * dist;

		dist = WaveMath::ClampF(Vector3::Dot(d, ZAxis), -extents.z, extents.z);
		result += ZAxis * dist;

		return result;
	}

	bool OrientedBoundingBox::Intersects(const OrientedBoundingBox& b) const
	{
		float ae[3] = { extents.x, extents.y, extents.z };
		float be[3] = { b.extents.x, b.extents.y, b.extents.z };

		Vector3 aXis[3]{ XAxis, YAxis, ZAxis };
		Vector3 bXis[3]{ b.XAxis, b.YAxis, b.ZAxis };

		float R[3][3]{ 0.0f };
		float AbsR[3][3]{ 0.0f };
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
			{
				R[i][j] = Vector3::Dot(aXis[i], bXis[j]);
				AbsR[i][j] = WaveMath::Abs(R[i][j]) + WaveMath::Epsilon();
			}

		Vector3 tw = b.center - center;
		float t[3] = { Vector3::Dot(tw, XAxis), Vector3::Dot(tw, YAxis), Vector3::Dot(tw, ZAxis) };

		float ra = 0.0f;
		float rb = 0.0f;

		for (int i = 0; i < 3; ++i)
		{
			ra = ae[i];
			rb = be[0] * AbsR[i][0] + be[1] * AbsR[i][1] + be[2] * AbsR[i][2];

			if (WaveMath::Abs(t[i]) > ra + rb)
				return false;
		}

		for (int j = 0; j < 3; ++j)
		{
			ra = ae[0] * AbsR[0][j] + ae[1] * AbsR[1][j] + ae[2] * AbsR[2][j];
			rb = be[j];

			if (WaveMath::Abs(t[0] * R[0][j] + t[1] * R[1][j] + t[2] * R[2][j]) > ra + rb)
				return false;
		}

		for (int i = 0; i < 3; ++i)
		{
			int i1 = (i + 1) % 3, i2 = (i + 2) % 3;
			for (int j = 0; j < 3; ++j)
			{
				int j1 = (j + 1) % 3, j2 = (j + 2) % 3;
				ra = ae[i1] * AbsR[i2][j] + ae[i2] * AbsR[i1][j];
				rb = be[j1] * AbsR[i][j2] + be[j2] * AbsR[i][j1];

				if (WaveMath::Abs(t[i2] * R[i1][j] - t[i1] * R[i2][j]) > ra + rb)
					return false;
			}
		}

		return true;
	}

	OrientedBoundingBox OrientedBoundingBox::FromAABB(BoundingBox boundingBox, Vector3 position, Vector3 XAxis, Vector3 YAxis, Vector3 ZAxis)
	{
		Vector3 boundingBoxCenter = boundingBox.GetCenter();

		Vector3 worldCenter = position + XAxis * boundingBoxCenter.x + YAxis * boundingBoxCenter.y + ZAxis * boundingBoxCenter.z;
		return OrientedBoundingBox(worldCenter, boundingBox.GetSize(), XAxis, YAxis, ZAxis);
	}

	OrientedBoundingBox OrientedBoundingBox::FromPoints(const Vector3* pts, int count, Vector3 XAxis, Vector3 YAxis, Vector3 ZAxis)
	{
		BoundingBox boundingBox;

		for (int i = 0; i < count; ++i)
			boundingBox.Encapsulate(Vector3(Vector3::Dot(pts[i], XAxis), Vector3::Dot(pts[i], YAxis), Vector3::Dot(pts[i], ZAxis)));

		Vector3 boundinBoxCenter = boundingBox.GetCenter();

		return OrientedBoundingBox(XAxis * boundinBoxCenter.x + YAxis * boundinBoxCenter.y + ZAxis * boundinBoxCenter.z,
			boundingBox.GetSize(), XAxis, YAxis, ZAxis);
	}

	Matrix4x4 OrientedBoundingBox::MakeMatrix(const OrientedBoundingBox& oob)
	{
		Vector3 s = oob.GetSize();
		Vector3 x = oob.XAxis * s.x;
		Vector3 y = oob.YAxis * s.y;
		Vector3 z = oob.ZAxis * s.z;

		return Matrix4x4
		(
			x.x, y.x, z.x, oob.center.x,
			x.y, y.y, z.y, oob.center.y,
			x.z, y.z, z.z, oob.center.z,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
}
