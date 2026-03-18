#include "TextureImporter.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <GL/glew.h>
#include <iostream>
#include <filesystem>

namespace WaveEngine
{
	TextureImporter::TextureImporter() : Service()
	{
	}

	TextureImporter::~TextureImporter()
	{
	}

	TextureManager* TextureImporter::GetTextureManager()
	{
		return ServiceProvider::Instance().Get<TextureManager>();
	}

	unsigned int TextureImporter::LoadTextureAbsolutePath(const string_view filePath)
	{
		string absolutePath = std::filesystem::absolute(filePath).lexically_normal().string();

		return LoadTexture(absolutePath);
	}

	unsigned int TextureImporter::LoadTexture(const string_view filePath)
	{
		int width;
		int height;
		int nrChannels;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filePath.data(), &width, &height, &nrChannels, 0);

		GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

		if (!data)
		{
			std::cout << "Failed to load texture: " << filePath << std::endl;
			return 0;
		}

		unsigned int texture = 0;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		++currentTextureID;

		Texture* newTexture = new Texture(currentTextureID, texture, width, height);

		std::filesystem::path path = filePath;

		newTexture->name = path.filename().string();

		GetTextureManager()->Save(currentTextureID, newTexture);

		stbi_image_free(data);

		std::cout << "Loaded texture: " << filePath << " (" << width << "x" << height << ")" << std::endl;

		return currentTextureID;
	}
}