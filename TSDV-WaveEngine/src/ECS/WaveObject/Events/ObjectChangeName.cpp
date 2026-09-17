#include "ObjectChangeName.h"

#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	ObjectChangeName::ObjectChangeName()
	{
	}

	ObjectChangeName::ObjectChangeName(unsigned int entityID, string newName)
	{
		this->entityID = entityID;
		this->newName = newName;
	}

	void ObjectChangeName::Reset()
	{
		entityID = WaveObject::NULL_OBJECT;
		newName = "";
	}
}
