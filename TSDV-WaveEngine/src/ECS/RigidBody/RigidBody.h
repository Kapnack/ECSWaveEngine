#pragma once

#include "ECS/Component/Component.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Matrix3x3/Matrix3x3.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"

namespace WaveEngine
{
	class RigidBody : public Component
	{
	private:

		WaveObjectRegistry* GetWaveObjectRegistry() const;

		Vector3 centerOfMassLocal;

		Vector3 velocity;
		Vector3 angularVelocity;
		Vector3 forceAccumulator;
		Vector3 torqueAccumulator;

		float linearDamping = 0.999f;
		float angularDamping = 0.995f;

		Matrix3x3 inverseInertiaLocal;
		Matrix3x3 inverseInertiaWorld;

		float restitution = 1.0f;
		float mass = 1.0f;
		bool isGrounded = false;
		bool isGravityAffected = true;

		Vector3 groundNormal = Vector3::Up();

		friend class RigidBodyLogic;

	public:

		RigidBody(unsigned int id);

		void SetGravityAffected(bool isGravityAffected);

		void SetRestitution(float restitution);

		void SetMass(float mass);
		bool IsGrounded() const;

		void SetVelocity(Vector3 velocity);

		void AddVelocity(Vector3 velocity);

		float GetMass() const;
		float GetInvMass() const;

		bool IsGravityAffected() const;

		Vector3 GetVelocity() const;
	};

	class Collider : public Component
	{
		Collider(unsigned int id): Component(id)
		{ }
	};
}