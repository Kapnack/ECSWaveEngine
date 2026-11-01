#include "Texture.h"

#include <vector>
#include <string>
#include <algorithm>
#include <GL/glew.h>
#include <string_view>

#include "TextureImporter.h"
#include "ECS/WObject/WObject.h"
#include "WaveMath/Vector2/Vector2.h"
#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine
{
	Texture::Texture(unsigned int gpuID, int width, int height) : WObject()
	{
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

	vector<unsigned char> Texture::GetPixels() const
	{
		vector<unsigned char> pixels(width * height * 4);

		glBindTexture(GL_TEXTURE_2D, gputID);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

		const int rowSize = width * 4;
		for (int y = 0; y < height / 2; ++y)
		{
			swap_ranges(
				pixels.begin() + y * rowSize,
				pixels.begin() + (y + 1) * rowSize,
				pixels.begin() + (height - 1 - y) * rowSize);
		}

		return pixels;
	}

	unsigned int Texture::GetGPUID() const
	{
		return gputID;
	}
}
