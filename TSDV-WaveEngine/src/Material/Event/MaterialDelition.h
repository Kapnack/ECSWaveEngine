#pragma once

#include "EventSystem/Event.h"
#include "ECS/WObject/WObject.h"

namespace WaveEngine
{
	struct MaterialDelition : public Event
	{
		unsigned int ID = WObject::NULL_WAVE_OBJECT;

		MaterialDelition()
		{
		}

		MaterialDelition(const unsigned int& ID)
		{
			this->ID = ID;
		}

		void Reset() override
		{
			ID = WObject::NULL_WAVE_OBJECT;
		}
	};
}