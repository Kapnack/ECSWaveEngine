#pragma once

#include "ECS/Component/Component.h"
#include "OrientedBoundingBox/OrientedBoundingBox.h"

namespace WaveEngine
{
	struct OrientedBoundingBoxComp : public Component
	{
		OrientedBoundingBox bounds;

		OrientedBoundingBoxComp(unsigned int id) : Component(id)
		{

		}
	};
}