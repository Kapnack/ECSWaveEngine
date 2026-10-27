#pragma once

#include "Export.h"
#include "ECS/Component/TypeComponent.h"

namespace WaveEngine
{
	class WaveObject;

	class WAVEEXPORT WObject
	{
	public:

		static WaveObject& Instantiate(const char* name = nullptr);

		static WaveObject& InstantiateModel(const char* modelDir, bool useAbsolutePath = true, const char* rootName = nullptr);

		template<TypeComponent T>
		static T& Instantiate(const char* name = nullptr);

		template<TypeComponent T>
		static T& InstantiateModel(const char* modelDir, bool useAbsolutePath = true, const char* rootName = nullptr);

	};
}