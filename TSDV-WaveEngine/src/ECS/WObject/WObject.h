#pragma once

#include <typeindex>
#include <unordered_map>

#include "Export.h"
#include "Mesh/Mesh.h"
#include "Material/Material.h"
#include "TextureImporter/Texture.h"

namespace WaveEngine
{
	class Component;
	class WaveObject;

	class WAVEEXPORT WObject
	{
	private:

	public:

		WObject();
		virtual ~WObject();

		type_index GetType() const;

		static WaveObject& Instantiate(const char* modelDir, bool useAbsolutePath = true, const char* rootName = nullptr);

		static void Destroy(WObject& wObject);
		static void Destroy(Component& component);
		static void Destroy(WaveObject& waveObject);
		static void Destroy(Material& material);
		static void Destroy(Texture& texture);
		static void Destroy(Mesh& mesh);
		static void DestroyImmediate(WObject& wObject);
		static void DestroyImmediate(Component& component);
		static void DestroyImmediate(WaveObject& waveObject);
		static void DestroyImmediate(Material& material);
		static void DestroyImmediate(Texture& texture);
		static void DestroyImmediate(Mesh& mesh);
	};
}