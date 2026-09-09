#pragma once

#include "Export.h"

namespace WaveEngine
{
	class WaveObject;
	class WaveObjectFactory;

	class WObject
	{
	private:

		static WaveObjectFactory* GetWaveFactory();

	public:

		static WaveObject& Instantiate();

		template<typename T>
		static T& Instantiate();

		static WaveObject& Instantiate(const char* modelDir, bool useAbsolutePath = true);

		template<typename T>
		static T& Instantiate(const char* modelDir, bool useAbsolutePath = true);
	};
}

#include "WObject.tpp"