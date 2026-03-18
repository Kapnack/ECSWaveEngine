#include "Texture.h"

namespace WaveEngine
{
	Texture::Texture(const unsigned int& ID, const unsigned int& textureID, const int& width, const int& height)
	{
		this->ID = ID;
		this->textureID = textureID;
		this->width = width;
		this->height = height;
	}

	Texture::~Texture()
	{
	}

	int Texture::GetWidth() const
	{
		return width;
	}

	int Texture::GetHeight() const
	{
		return height;
	}

	Vector2 Texture::GetRes() const
	{
		return Vector2(width, height);
	}

	string Texture::GetName() const
	{
		return name;
	}

	unsigned int Texture::GetTextureID() const
	{
		return textureID;
	}

	unsigned int Texture::GetID() const
	{
		return ID;
	}
}
