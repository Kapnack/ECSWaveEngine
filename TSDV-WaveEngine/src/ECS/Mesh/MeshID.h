#pragma once

#include "ECS/Component/Component.h"

#include "Export.h"
#include "Mesh/Mesh.h"

namespace WaveEngine
{
	struct WAVEEXPORT MeshID : Component
	{
		unsigned int meshID = Mesh::NULL_MESH;

		MeshID(const unsigned int& ID) : Component(ID)
		{ }
	};
}