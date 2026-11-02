#pragma once

#include "Material.h"
#include "FileReader/FileReader.h"
#include "ServiceProvider/Service.h"
#include "Material/MaterialManager.h"

using namespace std;

namespace WaveEngine
{
	class Engine;

	class MaterialFactory final : public Service
	{
	private:

		unsigned int currentMaterialID = WObject::NULL_OBJECT;

		MaterialManager* GetMaterialManager();
		FileReader* GetFileReader();

		unsigned int CompileShader(const string_view source, const unsigned int type);

		MaterialFactory();
		~MaterialFactory();

		friend class Engine;
		friend class ServiceProvider;

	public:

		Material* CreateMaterial(const string_view name, const string_view vertexShader, const string_view fragmentShader);
		Material* LoadMaterial(const string_view name, const string_view vertexShaderDir, const string_view fragmentShaderDir);
	};
}