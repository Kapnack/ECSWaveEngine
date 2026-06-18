#pragma once

#include "Export.h"

#include "ServiceProvider/Service.h"
#include "TextureImporter/TextureManager.h"

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

		friend class BaseGame;
		friend class ServiceProvider;

	public:

		WAVEEXPORT unsigned int LoadTextureAbsolutePath(const string_view filePath);
		WAVEEXPORT unsigned int LoadTexture(const string_view filePath);
		WAVEEXPORT unsigned int LoadTextureFromMemory(const unsigned char* buffer, int size);
		WAVEEXPORT unsigned int LoadTextureFromPixels(const unsigned char* buffer, const unsigned int& width, const unsigned int& height);
	};
}