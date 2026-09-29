#pragma once

#include "Triangle.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/WaveMath/WaveMath.h"
#include "WaveMath/Matrix3x3/Matrix3x3.h"
#include "WaveMath/Quaternion/Quaternion.h"

namespace WaveEngine
{
	class InertiaTensor
	{
	public:

		static Matrix3x3 FromBox(Vector3 size, float mass)
		{
			float x2 = size.x * size.x;
			float y2 = size.y * size.y;
			float z2 = size.z * size.z;

			float k = mass / 12.0f;

			return Matrix3x3::Diagonal(Vector3(
				k * (y2 + z2),
				k * (x2 + z2),
				k * (x2 + y2)));
		}

		static bool FromMesh(Triangle* triangles, int trianglesSize, float mass, Matrix3x3& inertia, Vector3& centerOfMass, float& volume)
		{
			inertia = Matrix3x3::Zero();
			centerOfMass = Vector3::Zero();
			volume = 0.0f;

			if (!triangles || trianglesSize == 0)
				return false;

			Matrix3x3 canonical = Matrix3x3(
				2.0f, 1.0f, 1.0f,
				1.0f, 2.0f, 1.0f,
				1.0f, 1.0f, 2.0f) * (1.0f / 120.0f);

			Matrix3x3 covariance = Matrix3x3::Zero();
			Vector3 weightedCentroid = Vector3::Zero();

			for (int i = 0; i < trianglesSize; i++)
			{
				Vector3 a = triangles[i].pointA;
				Vector3 b = triangles[i].pointB;
				Vector3 c = triangles[i].pointC;

				Matrix3x3 A = Matrix3x3::FromColumns(a, b, c);
				float det = A.Determinant();

				float tetVolume = det / 6.0f;
				volume += tetVolume;

				weightedCentroid += tetVolume * (a + b + c) * 0.25f;

				covariance = covariance + (A * canonical * A.Transposed()) * det;
			}

			if (WaveMath::Abs(volume) < WaveMath::Epsilon() * WaveMath::Epsilon())
				return false;

			centerOfMass = weightedCentroid / volume;

			covariance = covariance - Matrix3x3::OuterProduct(centerOfMass, centerOfMass) * volume;

			float density = mass / volume;

			inertia = (Matrix3x3::Identity() * covariance.Trace() - covariance) * density;
			return true;
		}

		static Matrix3x3 ShiftToCenterOfMass(Matrix3x3 inertia, float mass, Vector3 offset)
		{
			float d2 = offset.SqrMagnitude();

			Matrix3x3 shift = (Matrix3x3::Identity() * d2 - Matrix3x3::OuterProduct(offset, offset)) * mass;

			return inertia + shift;
		}

		static float SignedVolume(Triangle* triangles, int trianglesSize)
		{
			if (triangles == nullptr)
				return 0.0f;

			float volume = 0.0f;

			for (int i = 0; i < trianglesSize; i++)
			{
				Vector3 a = triangles[i].pointA;
				Vector3 b = triangles[i].pointB;
				Vector3 c = triangles[i].pointC;

				volume += Vector3::Dot(a, Vector3::Cross(b, c)) / 6.0f;
			}

			return volume;
		}
	};
}