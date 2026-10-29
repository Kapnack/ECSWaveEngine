#include "Texture.h"

#include <string_view>

#include "TextureImporter.h"
#include "WaveMath/Vector2/Vector2.h"
#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine
{
	Texture::Texture(const unsigned int& textureID, const unsigned int& gpuID, const int& width, const int& height)
	{
		this->textureID = textureID;
		this->gputID = gpuID;
		this->width = width;
		this->height = height;
	}

	Texture::~Texture()
	{
	}

	Texture& Texture::Import(const string_view path, bool useAbsolutePath, const char* overrideName)
	{
		return *ServiceProvider::Instance().Get<TextureImporter>()->LoadTexture(path, useAbsolutePath, overrideName);
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

	unsigned int Texture::GetGPUID() const
	{
		return gputID;
	}
}
