#pragma once

#include "ECS/ComponentContainer/ComponentContainer.h"
#include "RigidBody.h"

namespace WaveEngine
{
	class RigidBodyLogic
	{
	private:

		const float Gravity = 9.81f;

		ComponentContainer<RigidBody>& GetRigidBodyContainer();

	public:

		void Update(float deltaTime);
	};
}