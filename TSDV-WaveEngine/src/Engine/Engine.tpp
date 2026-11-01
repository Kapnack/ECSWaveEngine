#ifndef WAVE_ENGINE_ENGINE
#define WAVE_ENGINE_ENGINE

#include "Engine.h"
#include "WaveManagerConcept.h"

namespace WaveEngine
{
	template<WaveManagerConcept T>
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
