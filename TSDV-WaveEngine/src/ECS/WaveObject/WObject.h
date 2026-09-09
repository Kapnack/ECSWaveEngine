#pragma once

#include "Export.h"
#include "ECS/Component/TypeComponent.h"

namespace WaveEngine
{
	class WaveObject;
	class WaveObjectFactory;

	class WAVEEXPORT WObject
	{
	private:

		static WaveObjectFactory* GetWaveFactory();

	public:

		static WaveObject& Instantiate();

		template<TypeComponent T>
		static T& Instantiate();

		static WaveObject& Instantiate(const char* modelDir, bool useAbsolutePath = true);

		template<TypeComponent T>
		static T& Instantiate(const char* modelDir, bool useAbsolutePath = true);
	};
}

#include "WObject.tpp"