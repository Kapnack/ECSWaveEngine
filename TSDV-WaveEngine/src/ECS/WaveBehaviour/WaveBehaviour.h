#pragma once

#include "ECS/Component/Component.h"
#include "ECS/WaveObject/WaveObject.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectFactory.h"

namespace WaveEngine
{
	class WaveBehaviour : public Component
	{
	private:

		WaveObjectFactory* GetWaveObjectFactory() const
		{
			return ServiceProvider::Instance().Get<WaveObjectFactory>();
		}

	public:

		WaveBehaviour(unsigned int ID) : Component(ID)
		{
		}

		virtual void Update()
		{
		}

		virtual void LateUpdate()
		{
		}

		virtual void Destroy()
		{
		}

		WaveObject& Instantiate() const
		{
			return GetWaveObjectFactory()->Instantiate();
		}
	};
}