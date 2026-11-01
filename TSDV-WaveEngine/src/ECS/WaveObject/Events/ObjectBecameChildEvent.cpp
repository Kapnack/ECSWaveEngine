#include "ObjectBecameChildEvent.h"

#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	ObjectBecameChildEvent::ObjectBecameChildEvent()
	{
	}

	ObjectBecameChildEvent::ObjectBecameChildEvent(unsigned int waveObjectID, unsigned int parentWaveObjectID)
	{
		this->waveObjectID = waveObjectID;
		this->parentWaveObjectID = parentWaveObjectID;
	}

	void ObjectBecameChildEvent::Reset()
	{
		waveObjectID = WObject::NULL_WAVE_OBJECT;
	}
}
