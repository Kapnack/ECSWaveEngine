#include "WaveMath/Vector3/Vector3.h"

namespace WaveEngine
{
	struct Contact
	{
	public:

		Vector3 position;
		Vector3 normal;
		float depth;

		unsigned int objectA;
		unsigned int objectB;

		float friction;
		float restitution;

		Contact(Vector3 position, Vector3 normal, float depth, unsigned int objectA, unsigned int objectB, float friction, float restitution)
		{
			this->position = position;
			this->normal = normal;
			this->depth = depth;
			this->objectA = objectA;
			this->objectB = objectB;
			this->friction = friction;
			this->restitution = restitution;
		}
	};
}