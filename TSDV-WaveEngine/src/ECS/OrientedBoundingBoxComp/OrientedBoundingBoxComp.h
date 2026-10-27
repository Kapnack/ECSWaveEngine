#pragma once

#include "Export.h"
#include "ECS/Component/Component.h"
#include "OrientedBoundingBox/OrientedBoundingBox.h"

namespace WaveEngine
{
	class WAVEEXPORT OrientedBoundingBoxComp : public Component
	{
	public:

		OrientedBoundingBox bounds;

		OrientedBoundingBoxComp(unsigned int id) : Component(id)
		{

		}
	};
}