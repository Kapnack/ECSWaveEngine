#pragma once

#include <list>

#include "RigidBody.h"
#include "Physics/Contact.h"
#include "ECS/ComponentContainer/ComponentContainer.h"

namespace WaveEngine
{
	class RigidBodyLogic
	{
	private:

		const float Gravity = 9.81f;

		list<Contact> contacts;

		ComponentContainer<RigidBody>& GetRigidBodyContainer();

	public:

		void Update(float deltaTime);
	};
}