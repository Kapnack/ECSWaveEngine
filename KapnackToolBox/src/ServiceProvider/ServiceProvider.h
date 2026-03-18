#pragma once

#include "Singleton/Singleton.h"

#include <map>
#include <typeindex>

#include "Service.h"

using namespace std;

namespace WaveEngine
{
	template<typename T>
	concept ServiceStandard = is_base_of_v<Service, T>;

	class ServiceProvider final : public Singleton<ServiceProvider>
	{
	private:

		map<type_index, Service*> services;

	public:

		template<ServiceStandard T>
		void Register(T* service);

		template<ServiceStandard T>
		T* Get();

		template<ServiceStandard T>
		T* TryGet();

		template<ServiceStandard T>
		void UnRegister();

		inline void Clear();
	};
}

#include "ServiceProvider.tpp"