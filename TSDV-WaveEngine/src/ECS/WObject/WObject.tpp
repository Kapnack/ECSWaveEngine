#ifndef W_OBJECT_TPP
#define W_OBJECT_TPP

#include "WObject.h"

#include "ECS/WaveObject/WaveObject.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectFactory.h"

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

	template<TypeComponent T>
	T& WObject::Instantiate()
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>()->Instantiate<T>();
	}

	template<TypeComponent T>
	T& WObject::Instantiate(const char* modelDir, bool useAbsolutePath)
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>()->Instantiate<T>();
	}

}

#endif
