#pragma once

#include "ECS/Component/TypeComponent.h"

namespace WaveEngine
{
	class WaveObject;

	class WObject
	{
	public:

		static WaveObject& Instantiate();

		template<TypeComponent T>
		static T& Instantiate();

		static WaveObject& Instantiate(const char* modelDir, bool useAbsolutePath = true);

		template<TypeComponent T>
		static T& Instantiate(const char* modelDir, bool useAbsolutePath = true);

	};
}