#include "WaveMaterialBehaviour.h"

#include "Material/Material.h"
#include "Material/MaterialManager.h"
#include "ECS/WaveObject/WaveObject.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"

namespace WaveEngine
{
	WaveMaterialBehaviour::~WaveMaterialBehaviour()
	{
	}

	void WaveMaterialBehaviour::SetMaterial(unsigned int materialID)
	{
		this->materialID = materialID;
	}

	void WaveMaterialBehaviour::SetWaveObject(unsigned int currentWaveObject)
	{
		this->currentWaveObject = currentWaveObject;
	}

	WaveObject& WaveMaterialBehaviour::GetWaveObject() const
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetWaveObject(currentWaveObject);
	}

	Material& WaveMaterialBehaviour::GetMaterial() const
	{
		return ServiceProvider::Instance().Get<MaterialManager>()->GetMaterial(currentWaveObject);
	}

	void WaveMaterialBehaviour::Init()
	{
	}

	void WaveMaterialBehaviour::LateInit()
	{
	}

	void WaveMaterialBehaviour::GeneralUpdate(float deltaTime)
	{
	}

	void WaveMaterialBehaviour::Update(float deltaTime)
	{
	}

	void WaveMaterialBehaviour::Dispose()
	{
	}
}
