#include "WaveMaterialBehaviour.h"

namespace WaveEngine
{
	WaveMaterialBehaviour::~WaveMaterialBehaviour()
	{
	}

	void WaveMaterialBehaviour::SetWaveObject(unsigned int currentWaveObject)
	{
		this->currentWaveObject = currentWaveObject;
	}

	void WaveMaterialBehaviour::Init()
	{
	}

	void WaveMaterialBehaviour::LateInit()
	{
	}

	void WaveMaterialBehaviour::Update(float deltaTime)
	{
	}

	void WaveMaterialBehaviour::OnDestroy()
	{
	}
}
