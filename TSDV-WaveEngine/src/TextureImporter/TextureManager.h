#pragma once

#include "ServiceProvider/Service.h"
#include "ServiceProvider/ServiceProvider.h"

#include "TextureImporter/Texture.h"

#include <unordered_map>
#include "Export.h"

namespace WaveEngine
{
	class TextureImporter;
	class BaseGame;
	class EntitiesImGui;
	class TexturesImGui;
	class TileMap;
	class Renderer;

	using namespace std;

	WAVEEXPORT class TextureManager final : public Service
	{
	private:

		unordered_map<unsigned int, Texture*> textures;

		TextureManager();
		~TextureManager();

		void Save(const unsigned int& ID, Texture* texture);

		Texture* GetTexture(const unsigned int& ID) const;
		Texture* TryGetTexture(const unsigned int& ID) const;

		unordered_map<unsigned int, Texture*>& GetTextures();

		friend class BaseGame;
		friend class TextureImporter;
		friend class ServiceProvider;
		friend class EntitiesImGui;
		friend class TexturesImGui;
		friend class TileMap;
		friend class Renderer;

	public:

		WAVEEXPORT void DeleteTexture(const unsigned int& ID);
		WAVEEXPORT void DeleteTexture(const string_view name);
	};
}