#pragma once

#include "WaveObject.h"
#include <ServiceProvider/Service.h>
#include "WaveObjectRegistry.h"

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

		ComponentRegistry* GetComponenetRegistry();
		WaveObjectRegistry* GetWaveObjectRegistry();

		friend class ServiceProvider;
		friend class BaseGame;

	public:

		WaveObject& Instantiate();
	};
}