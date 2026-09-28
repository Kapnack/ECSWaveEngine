#pragma once

#include "ECS/Component/Component.h"
#include "BoundingBox/BoundingBox.h"

namespace WaveEngine
{
	struct BoundingBoxComp : public Component
	{
		BoundingBox bounds;

		BoundingBoxComp(unsigned int id) : Component(id)
		{ }
	};
}