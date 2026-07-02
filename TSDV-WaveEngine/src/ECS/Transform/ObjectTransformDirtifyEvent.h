#pragma once

#include "EventSystem/Event.h"

namespace WaveEngine
{
	struct ObjectTransformDirtifyEvent : Event
	{
		unsigned int objectID = 0;

		ObjectTransformDirtifyEvent()
		{
		};

		ObjectTransformDirtifyEvent(unsigned int objectID)
		{
			this->objectID = objectID;
		}

		void Reset() override
		{
			objectID = 0;
		}
	};
}