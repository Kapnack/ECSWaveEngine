#pragma once

#include "EventSystem/Event.h"

namespace WaveEngine
{
	struct ObjectBecameParentEvent : public Event
	{
		unsigned int waveObjectID = 0;

		ObjectBecameParentEvent();

		ObjectBecameParentEvent(unsigned int waveObjectID);

		void Reset() override;
	};
}