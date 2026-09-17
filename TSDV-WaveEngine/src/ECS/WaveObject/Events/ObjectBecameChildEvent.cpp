#include "ObjectBecameChildEvent.h"

#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	ObjectBecameChildEvent::ObjectBecameChildEvent()
	{
	}

	ObjectBecameChildEvent::ObjectBecameChildEvent(unsigned int waveObjectID)
	{
		this->waveObjectID = waveObjectID;
	}

	void ObjectBecameChildEvent::Reset()
	{
		waveObjectID = WaveObject::NULL_OBJECT;
	}
}
