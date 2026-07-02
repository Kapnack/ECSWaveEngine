#include "RigidBodyLogic.h"

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

namespace WaveEngine
{
	ComponentContainer<RigidBody>* RigidBodyLogic::GetRigidBodyContainer()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}
	void RigidBodyLogic::Update(float deltaTime)
	{
		
	}
}
