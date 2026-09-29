#include "RigidBody.h"

#include "ECS/Component/Component.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"

namespace WaveEngine
{
	WaveObjectRegistry* RigidBody::GetWaveObjectRegistry() const
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
	}

	RigidBody::RigidBody(unsigned int id) : Component(id)
	{

	}

	void RigidBody::SetGravityAffected(bool isGravityAffected)
	{
		this->isGravityAffected = isGravityAffected;
	}

	void RigidBody::SetRestitution(float restitution)
	{
		this->restitution = restitution;
	}

	void RigidBody::SetMass(float mass)
	{
		this->mass = mass;
	}

	bool RigidBody::IsGrounded() const
	{
		return isGrounded;
	}

	float RigidBody::GetMass() const
	{
		return mass;
	}

	float RigidBody::GetInvMass() const
	{
		return mass <= 0.0f ? 0.0f : 1.0f / mass;
	}

	bool RigidBody::IsGravityAffected() const
	{
		return isGravityAffected;
	}

	void RigidBody::SetVelocity(Vector3 velocity)
	{
		this->velocity = velocity;
	}

	void RigidBody::AddVelocity(Vector3 velocity)
	{
		this->velocity += velocity;
	}

	Vector3 RigidBody::GetVelocity() const
	{
		return velocity;
	}
}
