#include "TextureImporter.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <GL/glew.h>
#include <iostream>
#include <filesystem>

#include "ServiceProvider/ServiceProvider.h"
#include "Texture.h"

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

		unsigned int textureGPUID = 0;

		glGenTextures(1, &textureGPUID);
		glBindTexture(GL_TEXTURE_2D, textureGPUID);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		Texture* newTexture = new Texture(++currentTextureID, textureGPUID, width, height);

		std::filesystem::path path = filePath;

		newTexture->name = path.filename().string();

		GetTextureManager()->Save(newTexture);

		stbi_image_free(data);

		std::cout << "Loaded texture: " << filePath << " (" << width << "x" << height << ")" << std::endl;

		return currentTextureID;
	}

	unsigned int TextureImporter::LoadTextureFromMemory(const unsigned char* buffer, int size)
	{
		int width;
		int height;
		int nrChannels;

		stbi_set_flip_vertically_on_load(true);

		unsigned char* data =
			stbi_load_from_memory(buffer, size, &width, &height, &nrChannels, 0);

		if (!data)
		{
			std::cout << "Failed to load embedded texture\n";
			return 0;
		}

		GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

		unsigned int textureGPUID = 0;

		glGenTextures(1, &textureGPUID);
		glBindTexture(GL_TEXTURE_2D, textureGPUID);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		Texture* newTexture = new Texture(++currentTextureID, textureGPUID, width, height);
		newTexture->name = "embedded_" + std::to_string(currentTextureID);

		GetTextureManager()->Save(newTexture);

		stbi_image_free(data);

		std::cout << "Loaded embedded texture (" << width << "x" << height << ")" << std::endl;

		return currentTextureID;
	}

	unsigned int TextureImporter::LoadTextureFromPixels(const unsigned char* buffer, const unsigned int& width, const unsigned int& height)
	{
		unsigned int textureGPUID = 0;

		glGenTextures(1, &textureGPUID);
		glBindTexture(GL_TEXTURE_2D, textureGPUID);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// aiTexel is BGRA, no stbi involved — upload raw pixels directly
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, buffer);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		Texture* newTexture = new Texture(++currentTextureID, textureGPUID, width, height);
		newTexture->name = "embedded_pixels_" + std::to_string(currentTextureID);

		GetTextureManager()->Save(newTexture);

		std::cout << "Loaded embedded raw texture (" << width << "x" << height << ")" << std::endl;

		return currentTextureID;
	}
}