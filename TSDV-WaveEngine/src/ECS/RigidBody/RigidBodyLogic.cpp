#include "RigidBodyLogic.h"

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

namespace WaveEngine
{
	ComponentContainer<RigidBody>& RigidBodyLogic::GetRigidBodyContainer()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>()->CreateOrGetComponentStorage<RigidBody>();
	}

	void RigidBodyLogic::Update(float deltaTime)
	{
		for (RigidBody& rigidBody : GetRigidBodyContainer().GetComponents())
		{
			if (rigidBody.GetIsStatic())
				continue;

			if (rigidBody.IsGravityAffected())
				rigidBody.AddVelocity(Vector3::Down() * (Gravity * deltaTime));

			rigidBody.GetTransform().Translate(rigidBody.GetVelocity() * deltaTime);
		}
	}
}
