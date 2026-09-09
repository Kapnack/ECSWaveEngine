#pragma once

#include "ServiceProvider/Service.h"

#include "WaveObject.h"
#include "ECS/Component/TypeComponent.h"
#include "ModelImporter/ModelImporter.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

class BaseGame;
class ServiceProvider;

namespace WaveEngine
{
	class WaveObjectRegistry;

	class WaveObjectFactory : public Service
	{
	private:

		unsigned int currentObjectID = 0;

		WaveObjectFactory();
		~WaveObjectFactory();

		inline ComponentRegistry* GetComponentRegistry() const;
		inline WaveObjectRegistry* GetWaveObjectRegistry() const;
		inline ModelImporter* GetModelImporter() const;

		friend class ServiceProvider;
		friend class Engine;

	public:

		inline WaveObject& Instantiate();

		template<typename T>
		T& Instantiate();

		inline WaveObject& Instantiate(const char* modelDir, bool useAbsolutePath = true);

		template<typename T>
		T& Instantiate(const char* modelDir, bool useAbsolutePath = true);
	};
}

#include "WaveObjectFactory.tpp"