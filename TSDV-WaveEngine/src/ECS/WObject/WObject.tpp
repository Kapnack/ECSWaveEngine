#ifndef W_OBJECT_TPP
#define W_OBJECT_TPP

#include "WObject.h"

#include "ECS/WaveObject/WaveObject.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectFactory.h"
#include "ECS/ComponentContainer/ComponentContainer.h"

namespace WaveEngine
{
	WaveObject& WObject::Instantiate()
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>()->Instantiate();
	}

	WaveObject& WObject::Instantiate(const char* modelDir, bool useAbsolutePath)
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>()->Instantiate();
	}

	template<typename T>
	T& WObject::Instantiate()
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>()->Instantiate<T>();
	}

	template<typename T>
	T& WObject::Instantiate(const char* modelDir, bool useAbsolutePath)
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>()->Instantiate<T>();
	}

}

#endif
