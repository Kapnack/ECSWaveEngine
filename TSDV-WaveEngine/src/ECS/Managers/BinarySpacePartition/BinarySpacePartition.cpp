#include "BinarySpacePartition.h"
#include "ServiceProvider/Service.h"

#include <list>

#include "Plane/Plane.h"
#include "WaveMath/WaveMath/WaveMath.h"
#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	BinarySpacePartition::BinarySpacePartition() : Service()
	{
	}

	bool BinarySpacePartition::ObjectsShareSpace(Vector3 vectorA, Vector3 vectorB)
	{
		for (const Plane& plane : planes)
			if (WaveMath::Sign(plane.SignedDistance(vectorA)) !=
				WaveMath::Sign(plane.SignedDistance(vectorB)))
				return false;

		return true;
	}

	void BinarySpacePartition::AddPlane(Plane newPlane)
	{
		for (Plane& plane : planes)
			if (newPlane == plane)
				return;

		planes.push_back(newPlane);
	}

	void BinarySpacePartition::RemovePlane(Plane plane)
	{
		planes.remove(plane);
	}

	const list<Plane>& BinarySpacePartition::GetPlanes()
	{
		return planes;
	}
}
