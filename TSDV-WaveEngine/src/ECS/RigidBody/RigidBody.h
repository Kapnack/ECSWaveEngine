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

		WaveObjectRegistry* GetWaveObjectRegistry() const;

		Vector3 velocity;

		float restitution = 1.0f;
		float mass = 0.0f;

		bool isStatic = false;

		bool isGravityAffected = true;

	public:

		RigidBody(const unsigned int& id);

		void SetGravityAffected(bool isGravityAffected);

		void SetIsStatic(bool isStatic);

		void SetRestitution(float restitution);

		void SetMass(float mass);

		void SetVelocity(Vector3 velocity);

		void AddVelocity(Vector3 velocity);

		float GetInvMass() const;

		bool IsGravityAffected() const;

		Vector3 GetVelocity() const;
	};
}