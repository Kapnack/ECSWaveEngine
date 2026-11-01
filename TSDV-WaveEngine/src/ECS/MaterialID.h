#pragma once

#include "Material/Material.h"
#include "Component/Component.h"

namespace WaveEngine
{
	struct MeshRenderer : public Component
	{
		unsigned int materialID = WObject::NULL_OBJECT;

		MeshRenderer() : Component()
		{
		}
	};
}