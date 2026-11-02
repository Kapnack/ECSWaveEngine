#pragma once

#include <vector>
#include <typeindex>

#include "Export.h"
#include "ECS/Component/TypeComponent.h"

namespace WaveEngine
{
	class Mesh;
	class Texture;
	class Material;
	class Component;
	class WaveObject;
	class MeshFactory;
	class TextureManager;
	class MaterialFactory;
	class TextureImporter;
	class MaterialManager;
	class WaveObjectFactory;
	class ComponentRegistry;
	class WaveObjectRegistry;
	class WaveMaterialBehaviour;

	template <TypeComponent T>
	class ComponentContainer;

	using namespace std;

	class WAVEEXPORT WObject
	{
	private:

		unsigned int ID = NULL_OBJECT;

		void SetID(unsigned int ID);

		friend class MeshFactory;
		friend class TextureManager;
		friend class TextureImporter;
		friend class MaterialFactory;
		friend class MaterialManager;
		friend class WaveObjectFactory;
		friend class ComponentRegistry;
		friend class WaveObjectRegistry;

		template <TypeComponent T>
		friend class ComponentContainer;

	public:

		static const unsigned int NULL_OBJECT;

		WObject();
		virtual ~WObject();

		unsigned int GetID() const;

		static WaveObject& Instantiate(const char* modelDir, bool useAbsolutePath = true, const char* rootName = nullptr);

		template<TypeComponent T>
		static vector<T*> FindByType()
		{
			vector<WObject*> wObjects = FindByType(typeid(T));
			vector<T*> result;

			result.reserve(wObjects.size());

			for (WObject* object : wObjects)
				result.push_back(static_cast<T*>(object));

			return result;
		}

		static vector<WObject*> FindByType(type_index typeIndex);

		static void Destroy(WObject& wObject);
		static void Destroy(Component& component);
		static void Destroy(WaveObject& waveObject);
		static void Destroy(Material& material);
		static void Destroy(Texture& texture);
		static void Destroy(Mesh& mesh);
		static void Destroy(WaveMaterialBehaviour& waveMaterialBehaviour);
		static void DestroyImmediate(WObject& wObject);
		static void DestroyImmediate(Component& component);
		static void DestroyImmediate(WaveObject& waveObject);
		static void DestroyImmediate(Material& material);
		static void DestroyImmediate(Texture& texture);
		static void DestroyImmediate(Mesh& mesh);
		static void DestroyImmediate(WaveMaterialBehaviour& waveMaterialBehaviour);
	};
}