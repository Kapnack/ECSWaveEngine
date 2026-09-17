#pragma once

#include "ECS/Component/Component.h"

namespace WaveEngine
{
	class WaveBehaviour : public Component
	{
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
	};
}