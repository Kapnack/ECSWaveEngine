#pragma once

#include "WaveMath/Vector2/Vector2.h"
#include "Export.h"

#include <string>


using namespace std;

namespace WaveEngine
{
	class TextureManager;
	class TextureImporter;

	class Texture final
	{
	private:

		string name;
		unsigned int ID = 0;
		unsigned int textureID = 0;

		int width;
		int height;

		Texture(const unsigned int& ID, const unsigned int& textureID, const int& width, const int& height);
		~Texture();

		friend class TextureManager;
		friend class TextureImporter;

	public:

		static const int NULL_TEXTURE = 0;

		int GetWidth() const;
		int GetHeight() const;
		string GetName() const;

		Vector2 GetRes() const;

		unsigned int GetTextureID() const;
		unsigned int GetID() const;
	};
}