#pragma once

#include <list>

#include "ServiceProvider/Service.h"

#include "Plane/Plane.h"
#include "ECS/WaveObject/WaveObject.h"

using namespace std;

namespace WaveEngine
{
	class BinarySpacePartition : public Service
	{
	private:

		list<Plane> planes;

	public:

		BinarySpacePartition();

		bool ObjectsShareSpace(const WaveObject& objectA, const WaveObject& objectB);

		void AddPlane(Plane plane);
		void RemovePlane(Plane plane);

		const list<Plane>& GetPlanes();
	};
}