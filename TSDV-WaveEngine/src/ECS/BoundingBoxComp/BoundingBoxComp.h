#pragma once

#include "Export.h"
#include "ECS/Component/Component.h"
#include "BoundingBox/BoundingBox.h"

namespace WaveEngine
{
	class WAVEEXPORT BoundingBoxComp : public Component
	{
	public:

		BoundingBox bounds;

		BoundingBoxComp(unsigned int id) : Component(id)
		{ }
	};
}