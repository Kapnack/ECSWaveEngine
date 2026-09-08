#ifndef WAVEOBJECTFACTORY
#define WAVEOBJECTFACTORY

#include "WaveObjectFactory.h"

#include <string>

#include "WaveObject.h"
#include "ECS/Mesh/MeshID.h"
#include "WaveObjectRegistry.h"
#include "ModelImporter/ModelImporter.h"
#include "ECS/Component/TypeComponent.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

namespace WaveEngine
{
	WaveObjectFactory::WaveObjectFactory() : Service()
	{

	}

	WaveObjectFactory::~WaveObjectFactory()
	{
	}

	WaveObject& WaveObjectFactory::Instantiate()
	{
		WaveObject* newWaveObject = new WaveObject(++currentObjectID);

		newWaveObject->AddComponent<ECSTransform>();
		newWaveObject->AddComponent<MeshID>();

		GetWaveObjectRegistry()->AddObject(newWaveObject, "WaveObject: " + to_string(currentObjectID) + ".");

		return *newWaveObject;
	}

	WaveObject& WaveObjectFactory::Instantiate(const char* modelDir, bool useAbsolutePath)
	{
		GetModelImporter()->LoadScene(modelDir, useAbsolutePath);

		return *GetModelImporter()->IntantiateModel();
	}

	template<TypeComponent T>
	T& WaveObjectFactory::Instantiate()
	{
		WaveObject& waveObject = Instantiate();
		return waveObject.AddComponent<T>();
	}

	template<TypeComponent T>
	T& WaveObjectFactory::Instantiate(const char* modelDir, bool useAbsolutePath)
	{
		WaveObject& instance = Instantiate(modelDir, useAbsolutePath);

		return GetModelImporter()->IntantiateModel()->AddComponent<T>();
	}


	ComponentRegistry* WaveObjectFactory::GetComponenetRegistry() const
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}

	WaveObjectRegistry* WaveObjectFactory::GetWaveObjectRegistry() const
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
	}

	ModelImporter* WaveObjectFactory::GetModelImporter() const
	{
		return ServiceProvider::Instance().Get<ModelImporter>();
	}
}
#endif