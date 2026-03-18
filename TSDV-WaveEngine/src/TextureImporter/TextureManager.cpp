#include "TextureManager.h"

#include <GL/glew.h>

namespace WaveEngine
{
	TextureManager::TextureManager() : Service()
	{
	}

	TextureManager::~TextureManager()
	{
		for (unordered_map<unsigned int, Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
			delete it->second;
	}

	void TextureManager::Save(const unsigned int& ID, Texture* texture)
	{
		textures[ID] = texture;
	}

	Texture* TextureManager::GetTexture(const unsigned int& ID) const
	{
		return textures.at(ID);
	}

	Texture* TextureManager::TryGetTexture(const unsigned int& ID) const
	{
		unordered_map<unsigned int, Texture*>::const_iterator it = textures.find(ID);

		if (it == textures.end())
			return nullptr;

		return it->second;
	}

	unordered_map<unsigned int, Texture*>& TextureManager::GetTextures()
	{
		return textures;
	}

	void TextureManager::DeleteTexture(const unsigned int& ID)
	{
		unordered_map<unsigned int, Texture*>::iterator texture = textures.find(ID);

		if (texture == textures.end() || texture->second == nullptr)
			return;

		glDeleteTextures(textures[ID]->textureID, &textures[ID]->textureID);
		delete textures[ID];
		textures.erase(ID);
	}

	void TextureManager::DeleteTexture(const string_view name)
	{
		unordered_map<unsigned int, Texture*>::iterator it = find_if(textures.begin(), textures.end(),
			[&name](const pair<const unsigned int, Texture*>& it)
			{
				return it.second && it.second->GetName() == name;
			});

		if (it == textures.end())
			return;

		glDeleteTextures(it->second->textureID, &it->second->textureID);
		delete it->second;
		textures.erase(it);
	}
}
