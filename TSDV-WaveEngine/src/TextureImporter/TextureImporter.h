#pragma once

#include <string_view>

#include "Export.h"

#include "Texture.h"
#include "ServiceProvider/Service.h"
#include "TextureImporter/TextureManager.h"

class BaseGame;

using namespace std;

namespace WaveEngine
{
	class WAVEEXPORT TextureImporter final : public Service
	{
	private:

		unsigned int currentTextureID = 0;

		TextureManager* GetTextureManager();

		TextureImporter();
		~TextureImporter();

		friend class Engine;
		friend class ServiceProvider;

	public:

		Texture* LoadTextureAbsolutePath(const string_view filePath);
		Texture* LoadTexture(const string_view filePath);
		Texture* LoadTextureFromMemory(const unsigned char* buffer, int size);
		Texture* LoadTextureFromPixels(const unsigned char* buffer, const unsigned int& width, const unsigned int& height);
	};
}