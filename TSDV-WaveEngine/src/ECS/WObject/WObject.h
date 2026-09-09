#pragma once

namespace WaveEngine
{
	class WaveObject;

	class WObject
	{
	public:

		static WaveObject& Instantiate();

		template<typename T>
		static T& Instantiate();

		static WaveObject& Instantiate(const char* modelDir, bool useAbsolutePath = true);

		template<typename T>
		static T& Instantiate(const char* modelDir, bool useAbsolutePath = true);

	};
}