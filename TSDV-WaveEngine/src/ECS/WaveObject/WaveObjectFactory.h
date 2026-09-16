#pragma once

#include "WaveObject.h"
#include "WaveObjectRegistry.h"
#include "ServiceProvider/Service.h"
#include "ECS/Component/TypeComponent.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

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
		friend class Engine;

	public:

		WaveObject& Instantiate();

		template<TypeComponent T>
		T& Instantiate()
		{
			WaveObject& waveObject = Instantiate();
			return waveObject.AddComponent<T>();
		}
	};
}