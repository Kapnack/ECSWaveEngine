#pragma once

#include "EventSystem/Event.h"

namespace WaveEngine
{
	struct ObjectBecameParentEvent : public Event
	{
		unsigned int waveObjectID = 0;
		unsigned int parentID = 0;

		ObjectBecameParentEvent();

		ObjectBecameParentEvent(unsigned int waveObjectID, unsigned int parentID);

		void Reset() override;
	};
}