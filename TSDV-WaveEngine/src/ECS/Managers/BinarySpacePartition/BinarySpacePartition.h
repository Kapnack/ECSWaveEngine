#pragma once

#include <list>


#include "Plane/Plane.h"
#include "ServiceProvider/Service.h"
#include "WaveMath/Vector3/Vector3.h"

using namespace std;

namespace WaveEngine
{
	class BinarySpacePartition : public Service
	{
	private:

		list<Plane> planes;

	public:

		BinarySpacePartition();

		bool ObjectsShareSpace(Vector3 objectA, Vector3 objectB);

		void AddPlane(Plane plane);
		void RemovePlane(Plane plane);

		const list<Plane>& GetPlanes();
	};
}