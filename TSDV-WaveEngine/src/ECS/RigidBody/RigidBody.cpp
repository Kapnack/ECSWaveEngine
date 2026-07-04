#include "RigidBody.h"

namespace WaveEngine
{
	WaveObjectRegistry* RigidBody::GetWaveObjectRegistry() const
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
	}

	RigidBody::RigidBody(const unsigned int& id) : Component(id)
	{

	}

	void RigidBody::SetGravityAffected(bool isGravityAffected)
	{
		this->isGravityAffected = isGravityAffected;
	}

	void RigidBody::SetIsStatic(bool isStatic)
	{
		this->isStatic = isStatic;
	}

	void RigidBody::SetRestitution(float restitution)
	{
		this->restitution = restitution;
	}

	void RigidBody::SetMass(float mass)
	{
		this->mass = mass;
	}

	float RigidBody::GetInvMass() const
	{
		return mass <= 0.0f ? 0.0f : 1.0f / mass;
	}

	bool RigidBody::GetIsStatic() const
	{
		return isStatic;
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
