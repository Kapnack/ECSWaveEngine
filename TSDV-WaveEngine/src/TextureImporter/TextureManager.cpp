#include "TextureManager.h"

#include <GL/glew.h>

namespace WaveEngine
{
	TextureManager::TextureManager() : Service()
	{
	}

	TextureManager::~TextureManager()
	{
		for (Texture* texture : textures)
		{
			glDeleteTextures(texture->textureID, &texture->textureID);
			delete texture;
		}
	}

	const unsigned int TextureManager::Save(Texture* texture)
	{
		const unsigned int currentIndex = textures.size();
		indexByname[texture->GetName()] = currentIndex;
		textures.push_back(texture);

		return currentIndex;
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

	vector<Texture*>& TextureManager::GetTextures()
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
		unordered_map<string, unsigned int>::iterator it = indexByname.find(string(name));

		if (it == indexByname.end())
			return;

		glDeleteTextures(textures.at(it->second)->textureID, &textures.at(it->second)->textureID);
		indexByname.erase(textures.at(it->second)->GetName());
		delete textures.at(it->second);
	}
}
