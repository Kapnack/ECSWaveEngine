#pragma once

#include "ECS/Component/Component.h"

#include "TextureImporter/Texture.h"

namespace WaveEngine
{
	struct TextureID : Component
	{
		unsigned int textureID = Texture::NULL_TEXTURE;
	};
}