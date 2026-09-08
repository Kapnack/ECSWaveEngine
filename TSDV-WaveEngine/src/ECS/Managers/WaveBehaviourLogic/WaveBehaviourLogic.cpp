#include "WaveBehaviourLogic.h"

#include "ECS/WaveBehaviour/WaveBehaviour.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

namespace WaveEngine
{
	ComponentRegistry* WaveBehaviourLogic::GetComponentRegistry() const
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}

	void WaveBehaviourLogic::Init() const
	{
		for (WaveBehaviour* waveBehaviour : GetComponentRegistry()->GetBehaviours())
			waveBehaviour->Init();
	}

	void WaveBehaviourLogic::LateInit() const
	{
		for (WaveBehaviour* waveBehaviour : GetComponentRegistry()->GetBehaviours())
			waveBehaviour->LateInit();
	}

	void WaveBehaviourLogic::Update() const
	{
		for (WaveBehaviour* waveBehaviour : GetComponentRegistry()->GetBehaviours())
			waveBehaviour->Update();
	}

	void WaveBehaviourLogic::LateUpdate() const
	{
		for (WaveBehaviour* waveBehaviour : GetComponentRegistry()->GetBehaviours())
			waveBehaviour->LateUpdate();
	}

	void WaveBehaviourLogic::Destroy() const
	{
		for (WaveBehaviour* waveBehaviour : GetComponentRegistry()->GetBehaviours())
			waveBehaviour->Destroy();
	}
}
