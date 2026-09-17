#pragma once

#include "EventSystem/Event.h"

namespace WaveEngine
{
	struct ObjectBecameChildEvent : public Event
	{
		unsigned int waveObjectID = 0;

		ObjectBecameChildEvent();

		ObjectBecameChildEvent(unsigned int waveObjectID);

		void Reset() override;
	};
}