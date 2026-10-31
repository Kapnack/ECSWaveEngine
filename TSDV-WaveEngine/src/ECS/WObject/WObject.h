#pragma once

#include "Export.h"

namespace WaveEngine
{
	class Component;
	class WaveObject;

	class WAVEEXPORT WObject
	{
	public:

		WObject();
		virtual ~WObject();

		static WaveObject& Instantiate(const char* modelDir, bool useAbsolutePath = true, const char* rootName = nullptr);

		static void Destroy(WObject* wObject);
		static void Destroy(Component* component);
		static void Destroy(WaveObject* waveObject);
	};
}