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

		WaveObject* CreateNewWaveObject();
		void AddDefaultComponents(WaveObject& waveObject);

		friend class ServiceProvider;
		friend class Engine;

	public:

		WaveObject& Instantiate(const char* name = nullptr);

		template<TypeComponent T>
		T& Instantiate(const char* name = nullptr)
		{
			WaveObject& waveObject = Instantiate(name);
			return waveObject.AddComponent<T>();
		}
	};
}