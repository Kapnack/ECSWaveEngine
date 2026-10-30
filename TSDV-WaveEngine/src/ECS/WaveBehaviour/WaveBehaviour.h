#pragma once

#include "Export.h"
#include "ECS/Component/Component.h"

namespace WaveEngine
{
	class WAVEEXPORT WaveBehaviour : public Component
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

		virtual void OnCollision()
		{

		}

		virtual void Dispose()
		{
		}
	};
}