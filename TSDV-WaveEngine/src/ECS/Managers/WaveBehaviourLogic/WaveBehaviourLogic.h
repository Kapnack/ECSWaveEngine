#pragma once

#include "ECS/CompontRegistry/ComponentRegistry.h"

namespace WaveEngine
{
	class WaveBehaviourLogic final
	{
	private:

		ComponentRegistry* GetComponentRegistry() const;

	public:

		void Init() const;
		void LateInit() const;

		void Update() const;
		void LateUpdate() const;

		void Destroy() const;
	};
}