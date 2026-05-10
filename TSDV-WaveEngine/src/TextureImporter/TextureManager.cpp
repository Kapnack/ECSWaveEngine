#include "TextureManager.h"

#include <GL/glew.h>

namespace WaveEngine
{
	TextureManager::TextureManager() : Service()
	{
	}

	TextureManager::~TextureManager()
	{
		for (map<unsigned int, Texture*>::iterator iterator = textures.begin(); iterator != textures.end(); ++iterator)
		{
			glDeleteTextures(iterator->second->textureID, &iterator->second->textureID);
			delete iterator->second;
		}
	}

	void TextureManager::Save(Texture*& texture)
	{
		indexByname[texture->GetName()] = texture->GetTextureID();
		textures[texture->GetTextureID()] = texture;
	}

	Texture* TextureManager::GetTexture(const unsigned int& ID) const
	{
		return textures.at(ID);
	}

	Texture* TextureManager::TryGetTexture(const unsigned int& ID) const
	{
		if (ID >= textures.size())
			return nullptr;

		return textures.at(ID);
	}

	map<unsigned int, Texture*>& TextureManager::GetTextures()
	{
		return textures;
	}

	void TextureManager::DeleteTexture(const unsigned int& ID)
	{
		if (ID >= textures.size())
			return;

		glDeleteTextures(textures.at(ID)->textureID, &textures.at(ID)->textureID);
		indexByname.erase(textures.at(ID)->GetName());
		delete textures.at(ID);
	}

	void TextureManager::DeleteTexture(const string_view name)
	{
		map<string, unsigned int>::iterator it = indexByname.find(string(name));

		if (it == indexByname.end())
			return;

		glDeleteTextures(textures.at(it->second)->textureID, &textures.at(it->second)->textureID);
		indexByname.erase(textures.at(it->second)->GetName());
		delete textures.at(it->second);
	}
}
