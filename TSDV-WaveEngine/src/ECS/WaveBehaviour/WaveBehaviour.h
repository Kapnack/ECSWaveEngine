#pragma once

#include "ECS/Component/Component.h"

namespace WaveEngine
{
	class WaveObject;

	class WaveBehaviour : public Component
	{
	public:

		WaveBehaviour(unsigned int ID);

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