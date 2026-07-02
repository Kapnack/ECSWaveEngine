#pragma once

#include "ECS/Component/Component.h"
#include "ECS/Transform/ECSTransform.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ServiceProvider/ServiceProvider.h"
#include "WaveMath/Vector3/Vector3.h"

namespace WaveEngine
{
	class RigidBody : public Component
	{
	private:

		WaveObjectRegistry* GetWaveObjectRegistry()
		{
			return ServiceProvider::Instance().Get<WaveObjectRegistry>();
		}

		Vector3 velocity;

		float restitution = 1.0f;
		float mass = 0.0f;

		bool isStatic = false;

		bool isGravityAffected = true;

	public:

		void SetGravityAffected(bool isGravityAffected)
		{
			this->isGravityAffected = isGravityAffected;
		}

		void SetIsStatic(bool isStatic)
		{
			this->isStatic = isStatic;
		}

		void SetRestitution(float restitution)
		{
			this->restitution = restitution;
		}

		void SetMass(float mass)
		{
			this->mass = mass;
		}

		float GetInvMass() const
		{
			return mass <= 0.0f ? 0.0f : 1.0f / mass;
		}

		void SetVelocity(Vector3 velocity)
		{
			this->velocity = velocity;
		}

		void AddVelocity(Vector3 velocity)
		{
			this->velocity += velocity;
		}

		Vector3 GetVelocity() const
		{
			return velocity;
		}

		ECSTransform& GetTransform()
		{
			return GetWaveObjectRegistry()->GetWaveObject(GetID()).GetTransform();
		}
	};
}