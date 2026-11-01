#pragma once

#include "ECS/Component/Component.h"

#include "Export.h"
#include "TextureImporter/Texture.h"

namespace WaveEngine
{
	class WAVEEXPORT TextureID : public Component
	{
		unsigned int ID = Texture::NULL_TEXTURE;
	};
}