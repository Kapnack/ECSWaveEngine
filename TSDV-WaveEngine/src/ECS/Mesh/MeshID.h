#pragma once

#include "ECS/Component/Component.h"

#include "Export.h"
#include "Mesh/Mesh.h"

namespace WaveEngine
{
	struct WAVEEXPORT MeshID : public Component
	{
		unsigned int meshID = WObject::NULL_OBJECT;

		MeshID() : Component()
		{
		}
	};
}