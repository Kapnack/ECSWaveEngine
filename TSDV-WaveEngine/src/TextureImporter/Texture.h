#pragma once

#include <vector>
#include <string>
#include <string_view>

#include "Export.h"
#include "ECS/WObject/WObject.h"
#include "WaveMath/Vector2/Vector2.h"

using namespace std;

namespace WaveEngine
{
	class TextureManager;
	class TextureImporter;

	class WAVEEXPORT Texture final : public WObject
	{
	private:

		string name;
		unsigned int ID = 0;
		unsigned int gputID = 0;

		int width;
		int height;

		Texture(unsigned int ID, unsigned int gpuID, int width, int height);
		~Texture();

		friend class TextureManager;
		friend class TextureImporter;

	public:

		static const int NULL_TEXTURE = 0;

		static Texture& Import(const string_view path, bool useAbsolutePath = true, const char* overrideName = nullptr);

		int GetWidth() const;
		int GetHeight() const;
		string GetName() const;
		Vector2 GetRes() const;

		vector<unsigned char> GetPixels() const;

		unsigned int GetTextureID() const;
		unsigned int GetGPUID() const;
	};
}