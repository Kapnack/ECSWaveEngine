#pragma once

#include "Export.h"

#include "ServiceProvider/Service.h"
#include "TextureImporter/TextureManager.h"
#include <string_view>
#include "Texture.h"

class BaseGame;

using namespace std;

namespace WaveEngine
{
	WAVEEXPORT class TextureImporter final : public Service
	{
	private:

		unsigned int currentTextureID = 0;

		TextureManager* GetTextureManager();

		TextureImporter();
		~TextureImporter();

		friend class Engine;
		friend class ServiceProvider;

	public:

		WAVEEXPORT Texture* LoadTextureAbsolutePath(const string_view filePath);
		WAVEEXPORT Texture* LoadTexture(const string_view filePath);
		WAVEEXPORT Texture* LoadTextureFromMemory(const unsigned char* buffer, int size);
		WAVEEXPORT Texture* LoadTextureFromPixels(const unsigned char* buffer, const unsigned int& width, const unsigned int& height);
	};
}