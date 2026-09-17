#include "ObjectBecameParentEvent.h"

#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	ObjectBecameParentEvent::ObjectBecameParentEvent()
	{
	}

	ObjectBecameParentEvent::ObjectBecameParentEvent(unsigned int waveObjectID)
	{
		this->waveObjectID = waveObjectID;
	}

	void ObjectBecameParentEvent::Reset()
	{
		this->waveObjectID = WaveObject::NULL_OBJECT;
	}
}