#ifndef W_OBJECT_TPP
#define W_OBJECT_TPP

#include "WObject.h"

#include "ECS/Component/TypeComponent.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectFactory.h"

namespace WaveEngine
{
	template<TypeComponent T>
	T& WObject::Instantiate(const char* name)
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>()->Instantiate<T>(name);
	}

	template<TypeComponent T>
	T& WObject::InstantiateModel(const char* modelDir, bool useAbsolutePath, const char* rootName)
	{
		return InstantiateModel(modelDir, useAbsolutePath, rootName).AddComponent<T>();
	}
}

#endif
