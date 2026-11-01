#include "TextureManager.h"

#include <map>
#include <GL/glew.h>

#include "Texture.h"

namespace WaveEngine
{
	TextureManager::TextureManager() : Service()
	{
	}

	TextureManager::~TextureManager()
	{
		for (map<unsigned int, Texture*>::iterator iterator = textures.begin(); iterator != textures.end(); ++iterator)
		{
			glDeleteTextures(iterator->second->ID, &iterator->second->ID);
			delete iterator->second;
		}
	}

	void TextureManager::Save(Texture*& texture)
	{
		indexByname[texture->GetName()] = texture->GetTextureID();
		textures[texture->GetTextureID()] = texture;
	}

	void TextureManager::Update()
	{
		for (unsigned int textureID : texturesToDestroy)
			DestroyImmediate(textureID);

		texturesToDestroy.clear();
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

	void TextureManager::Destroy(Texture& texture)
	{
		Destroy(texture.ID);
	}

	void TextureManager::Destroy(unsigned int ID)
	{
		texturesToDestroy.insert(ID);
	}

	void TextureManager::DestroyImmediate(Texture& texture)
	{
		DestroyImmediate(texture.ID);
	}

	void TextureManager::DestroyImmediate(unsigned int ID)
	{
		if (ID >= textures.size())
			return;

		glDeleteTextures(textures.at(ID)->ID, &textures.at(ID)->ID);
		indexByname.erase(textures.at(ID)->GetName());
		delete textures.at(ID);
	}
}
