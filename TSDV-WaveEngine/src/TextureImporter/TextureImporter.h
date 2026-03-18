#pragma once

#include "Export.h"
#include <string>

#include "ServiceProvider/ServiceProvider.h"
#include "ServiceProvider/Service.h"
#include "TextureImporter/TextureManager.h"
#include "TextureImporter/Texture.h"

class BaseGame;

using namespace std;

namespace WaveEngine
{
	WAVEEXPORT class TextureImporter final : public Service
	{
	private:

		unsigned int currentTextureID = Texture::NULL_TEXTURE;

		TextureManager* GetTextureManager();

		TextureImporter();
		~TextureImporter();

		friend class BaseGame;
		friend class ServiceProvider;

	public:

		WAVEEXPORT unsigned int  LoadTextureAbsolutePath(const string_view filePath);
		WAVEEXPORT unsigned int  LoadTexture(const string_view filePath);
	};
}