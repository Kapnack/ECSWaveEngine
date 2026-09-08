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

		unsigned int currentObjectID = WaveObject::NULL_OBJECT;

		WaveObjectFactory();
		~WaveObjectFactory();

		ComponentRegistry* GetComponenetRegistry() const;
		WaveObjectRegistry* GetWaveObjectRegistry() const;
		ModelImporter* GetModelImporter() const;

		friend class ServiceProvider;
		friend class Engine;

	public:

		WaveObject& Instantiate();

		template<TypeComponent T>
		T& Instantiate();

		WaveObject& Instantiate(const char* modelDir, bool useAbsolutePath = true);

		template<TypeComponent T>
		T& Instantiate(const char* modelDir, bool useAbsolutePath = true);
	};
}