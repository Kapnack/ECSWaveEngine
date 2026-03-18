#pragma once

#include "ServiceProvider/Service.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialManager.h"

#include <string>

using namespace std;

namespace WaveEngine
{
	class BaseGame;

	class MaterialFactory final : public Service
	{
	private:

		unsigned int currentMaterialID = Material::NULL_MATERIAL;

		MaterialManager* GetMaterialManager();

		unsigned int CompileShader(const string_view source, const unsigned int type);

		MaterialFactory();
		~MaterialFactory();

		friend class BaseGame;
		friend class ServiceProvider;

	public:

		unsigned int CreateMaterial(const string_view name, const string_view vertexShader, const string_view fragmentShader);
	};
}