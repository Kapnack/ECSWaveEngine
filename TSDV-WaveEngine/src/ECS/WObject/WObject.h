#pragma once

#include "Export.h"

namespace WaveEngine
{
	class WaveObject;

	class WAVEEXPORT WObject
	{
	public:

		static WaveObject& Instantiate(const char* modelDir, bool useAbsolutePath = true, const char* rootName = nullptr);
	};
}