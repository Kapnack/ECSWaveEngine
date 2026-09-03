#include "BinarySpacePartition.h"
#include "ServiceProvider/Service.h"

#include <vector>

#include "Plane/Plane.h"
#include "Renderer/Renderer.h"
#include "Material/Color/Color.h"
#include "BoundingBox/BoundingBox.h"
#include "WaveMath/Vector3/Vector3.h"
#include "ECS/WaveObject/WaveObject.h"
#include "WaveMath/WaveMath/WaveMath.h"
#include "ECS/Transform/ECSTransform.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ECS/ComponentContainer/ComponentContainer.h"
#include <algorithm>

namespace WaveEngine
{
	ComponentContainer<ECSTransform>& BinarySpacePartition::GetTransformContainer() const
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>()->GetComponentStorage<ECSTransform>();
	}

	WaveObjectRegistry* BinarySpacePartition::GetWaveObjectRegistry() const
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
	}

	Renderer* BinarySpacePartition::GetRenderer() const
	{
		return ServiceProvider::Instance().Get<Renderer>();
	}

	BinarySpacePartition::BinarySpacePartition() : Service()
	{
	}

	bool BinarySpacePartition::ObjectsShareSpace(Vector3 vectorA, Vector3 vectorB)
	{
		for (const Plane& plane : planes)
		{
			const int signOfA = WaveMath::Sign(plane.SignedDistance(vectorA));
			const int signOfB = WaveMath::Sign(plane.SignedDistance(vectorB));

			if (signOfA != 0 && signOfB != 0 && signOfA != signOfB)
				return false;
		}

		return true;
	}

	void BinarySpacePartition::AddPlane(Plane newPlane)
	{
		for (const Plane& plane : planes)
			if (newPlane == plane)
				return;

		planes.push_back(newPlane);
	}

	void BinarySpacePartition::TurnObjectIntoPlane(const WaveObject& waveObject)
	{
		objectsToMadePlane.push_back(waveObject.GetID());
	}

	void BinarySpacePartition::TurnObjectIntoPlane(unsigned int waveObjectID)
	{
		objectsToMadePlane.push_back(waveObjectID);
	}

	void BinarySpacePartition::RemovePlane(Plane plane)
	{
		remove_if(planes.begin(), planes.end(), [&](Plane it) { return it == plane; });
	}

	const vector<Plane>& BinarySpacePartition::GetPlanes()
	{
		return planes;
	}

	void BinarySpacePartition::Update()
	{
		for (unsigned int waveObjectID : objectsToMadePlane)
		{
			ECSTransform& waveObject = GetTransformContainer().Get(waveObjectID);

			planes.push_back(Plane(waveObject.GetForward(), waveObject.GetPosition()));
		}

		objectsToMadePlane.clear();

		for (const Plane& plane : planes)
		{
			BoundingBox newBoundingBox(plane.GetPosition(), Vector3(10, 10, 10));

			GetRenderer()->SubmitWireBox(newBoundingBox, Color::Red());
		}
	}
}
