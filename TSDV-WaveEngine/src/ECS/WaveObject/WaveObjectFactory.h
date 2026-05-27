#pragma once

#include "WaveObject.h"
#include <ServiceProvider/Service.h>
#include "WaveObjectRegistry.h"

using namespace WaveEngine::Objects;

class ServiceProvider;
class BaseGame;

namespace WaveEngine
{
	class WaveObjectFactory : Service
	{
	private:

		unsigned int currentObjectID = WaveObject::NULL_OBJECT;

		WaveObjectFactory();
		~WaveObjectFactory();

		WaveObject& Instantiate();

		ComponentRegistry* GetComponenetRegistry();
		WaveObjectRegistry* GetWaveObjectRegistry();

		friend class ServiceProvider;
		friend class BaseGame;
	};
}