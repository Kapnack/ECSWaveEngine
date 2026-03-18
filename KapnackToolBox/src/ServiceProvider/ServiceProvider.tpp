#ifndef SERVICEPROVIDER
#define SERVICEPROVIDER

#include "ServiceProvider.h"

namespace WaveEngine
{
	template<ServiceStandard T>
	void ServiceProvider::Register(T* service)
	{
		if (services.contains(typeid(T)) && services[typeid(T)] != nullptr)
		{
			delete service;
			return;
		}

		services[typeid(T)] = service;
	}

	template<ServiceStandard T>
	T* ServiceProvider::Get()
	{
		return static_cast<T*>(services.at(typeid(T)));
	}

	template<ServiceStandard T>
	T* ServiceProvider::TryGet()
	{
		map<type_index, Service*>::iterator it = services.find(typeid(T));

		return (it != services.end() && it->second != nullptr) ? static_cast<T*>(it->second) : nullptr;
	}

	template<ServiceStandard T>
	void ServiceProvider::UnRegister()
	{
		map<type_index, Service*>::iterator it = services.find(typeid(T));

		if (it == services.end())
			return;

		if (it->second != nullptr)
			delete it->second;

		services.erase(it);
	}

	void ServiceProvider::Clear()
	{
		for (map<type_index, Service*>::iterator it = services.begin(); it != services.end(); ++it)
		{
			delete it->second;
			it->second = nullptr;
		}

		services.clear();
	}
}
#endif