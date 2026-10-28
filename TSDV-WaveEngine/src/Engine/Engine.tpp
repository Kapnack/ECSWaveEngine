#ifndef WAVE_ENGINE_ENGINE
#define WAVE_ENGINE_ENGINE

#include "Engine.h"

namespace WaveEngine
{
	template<typename T>
	void Engine::StartEngine()
	{
		Engine* engine = new Engine(new T());

		engine->Init();
		engine->LateInit();

		engine->Run();

		engine->Dispose();

		delete engine;
	}
}

#endif
