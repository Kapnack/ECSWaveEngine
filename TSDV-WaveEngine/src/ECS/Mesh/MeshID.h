#pragma once

#include "ECS/Component/Component.h"

#include "Mesh/Mesh.h"
#include "BoundingBox/BoundingBox.h"

namespace WaveEngine
{
	struct MeshID : Component
	{
		unsigned int meshID = Mesh::NULL_MESH;

		BoundingBox boundingBox;

		MeshID(const unsigned int& ID) : Component(ID)
		{ }
	};
}