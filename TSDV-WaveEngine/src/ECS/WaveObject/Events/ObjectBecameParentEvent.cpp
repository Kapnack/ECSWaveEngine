#include "ObjectBecameParentEvent.h"

#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	ObjectBecameParentEvent::ObjectBecameParentEvent()
	{
	}

	ObjectBecameParentEvent::ObjectBecameParentEvent(unsigned int waveObjectID, unsigned int parentID)
	{
		this->waveObjectID = waveObjectID;
		this->parentID = parentID;
	}

	void ObjectBecameParentEvent::Reset()
	{
		this->waveObjectID = WaveObject::NULL_OBJECT;
	}
}