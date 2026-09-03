#pragma once

#include <vector>
#include <list>

#include "Plane/Plane.h"
#include "Renderer/Renderer.h"
#include "ServiceProvider/Service.h"
#include "WaveMath/Vector3/Vector3.h"
#include "ECS/WaveObject/WaveObject.h"
#include "ECS/Transform/ECSTransform.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/ComponentContainer/ComponentContainer.h"

using namespace std;

namespace WaveEngine
{
	class BinarySpacePartition : public Service
	{
	private:

		ComponentContainer<ECSTransform>& GetTransformContainer() const;
		WaveObjectRegistry* GetWaveObjectRegistry() const;

		vector<unsigned int> objectsToMadePlane;
		vector<Plane> planes;

		Renderer* GetRenderer() const;

	public:

		BinarySpacePartition();

		bool ObjectsShareSpace(Vector3 objectA, Vector3 objectB);

		void AddPlane(Plane plane);
		void TurnObjectIntoPlane(const WaveObject& waveObject);
		void TurnObjectIntoPlane(unsigned int waveObjectID);
		void RemovePlane(Plane plane);

		const vector<Plane>& GetPlanes();

		void Update();
	};
}