#include "WaveMaterialBehaviour.h"

#include "Material/Material.h"
#include "ECS/Camera/Camera.h"
#include "ECS/WObject/WObject.h"
#include "Material/MaterialManager.h"
#include "ECS/WaveObject/WaveObject.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

namespace WaveEngine
{
	WaveMaterialBehaviour::~WaveMaterialBehaviour()
	{
	}

	void WaveMaterialBehaviour::SetCamera(unsigned int cameraID)
	{
		this->currentCameraID = cameraID;
	}

	void WaveMaterialBehaviour::SetMaterial(unsigned int materialID)
	{
		this->materialID = materialID;
	}

	void WaveMaterialBehaviour::SetWaveObject(unsigned int waveObjectID)
	{
		this->currentWaveObjectID = waveObjectID;
	}

	void WaveMaterialBehaviour::UnBind()
	{
		materialID = WObject::NULL_OBJECT;
		currentWaveObjectID = WObject::NULL_OBJECT;
		currentCameraID = WObject::NULL_OBJECT;
	}

	WaveObject& WaveMaterialBehaviour::GetWaveObject() const
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetWaveObject(currentWaveObjectID);
	}

	Camera& WaveMaterialBehaviour::GetCamera() const
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>()->Get<Camera>(currentCameraID);
	}

	Material& WaveMaterialBehaviour::GetMaterial() const
	{
		return ServiceProvider::Instance().Get<MaterialManager>()->GetMaterial(currentWaveObjectID);
	}

	void WaveMaterialBehaviour::Init()
	{
	}

	void WaveMaterialBehaviour::LateInit()
	{
	}

	void WaveMaterialBehaviour::GeneralUpdate()
	{
	}

	void WaveMaterialBehaviour::Update()
	{
	}

	void WaveMaterialBehaviour::Dispose()
	{
	}
}
