#pragma once

#include "WaveObjectRegistry.h"
#include "ServiceProvider/Service.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

class ServiceProvider;
class BaseGame;

namespace WaveEngine
{
	class WaveObject;

	class WaveObjectFactory : Service
	{
	private:

		unsigned int currentObjectID = 0;

		WaveObjectFactory();
		~WaveObjectFactory();

		ComponentRegistry* GetComponenetRegistry();
		WaveObjectRegistry* GetWaveObjectRegistry();

		WaveObject* CreateNewWaveObject();
		void AddDefaultComponents(WaveObject& waveObject);

		friend class ServiceProvider;
		friend class Engine;

	public:

		WaveObject& Instantiate(const char* name = nullptr);
	};
}