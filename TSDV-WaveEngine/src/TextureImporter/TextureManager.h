#pragma once

#include "ServiceProvider/Service.h"

#include "TextureImporter/Texture.h"

#include <map>
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

		map<unsigned int, Texture*> textures;
		map<string, unsigned int> indexByname;

		TextureManager();
		~TextureManager();

		void Save(Texture*& texture);

		Texture* GetTexture(const unsigned int& ID) const;
		Texture* TryGetTexture(const unsigned int& ID) const;

		map<unsigned int, Texture*>& GetTextures();

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