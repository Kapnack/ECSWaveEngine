#pragma once

#include "Material/Material.h"
#include "Component/Component.h"

namespace WaveEngine
{
	struct MeshRenderer : Component
	{
		unsigned int materialID = Material::NULL_MATERIAL;

		MeshRenderer(unsigned int ID) : Component(ID)
		{
		}
	};
}