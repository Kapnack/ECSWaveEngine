#ifndef WOBJECT
#define WOBJECT

#include "WObject.h"

#include "WaveObject.h"
#include "WaveObjectFactory.h"
#include "ECS/Component/TypeComponent.h"
#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine
{
	WaveObjectFactory* WObject::GetWaveFactory()
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>();
	}

	WaveObject& WObject::Instantiate()
	{
		return GetWaveFactory()->Instantiate();
	}

	template<TypeComponent T>
	WaveObject& WObject::Instantiate()
	{
		return GetWaveFactory()->Instantiate<T>();
	}

	WaveObject& WObject::Instantiate(const char* modelDir, bool useAbsolutePath)
	{
		return GetWaveFactory()->Instantiate(modelDir, useAbsolutePath);
	}

	template<TypeComponent T>
	WaveObject& WObject::Instantiate(const char* modelDir, bool useAbsolutePath)
	{
		return GetWaveFactory()->Instantiate<T>(modelDir, useAbsolutePath);
	}
}
#endif