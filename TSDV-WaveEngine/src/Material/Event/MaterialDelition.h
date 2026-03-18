#pragma once

#include "EventSystem/Event.h"
#include "Material/Material.h"

namespace WaveEngine
{
	struct MaterialDelition : public Event
	{
		unsigned int ID = Material::NULL_MATERIAL;

		MaterialDelition()
		{
		}

		MaterialDelition(const unsigned int& ID)
		{
			this->ID = ID;
		}

		void Reset() override
		{
			ID = Material::NULL_MATERIAL;
		}
	};
}