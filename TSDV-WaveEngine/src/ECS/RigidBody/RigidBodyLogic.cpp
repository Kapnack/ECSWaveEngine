#include "RigidBodyLogic.h"

#include "RigidBody.h"
#include "Physics/InertiaTensor.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/WaveMath/WaveMath.h"
#include "ECS/Transform/ECSTransform.h"
#include "WaveMath/Matrix3x3/Matrix3x3.h"
#include "WaveMath/Quaternion/Quaternion.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ECS/ComponentContainer/ComponentContainer.h"

namespace WaveEngine
{
	ComponentContainer<RigidBody>& RigidBodyLogic::GetRigidBodyContainer()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>()->CreateOrGetComponentStorage<RigidBody>();
	}

	void RigidBodyLogic::Update(float deltaTime)
	{
		contacts.clear();

		for (RigidBody& rigidBody : GetRigidBodyContainer().GetComponents())
		{
			if (rigidBody.GetWaveObject().IsStatic())
				continue;

			if (rigidBody.IsGravityAffected())
				rigidBody.velocity += Vector3::Down() * (Gravity * deltaTime);

			rigidBody.velocity += rigidBody.forceAccumulator * rigidBody.GetInvMass() * deltaTime;
			rigidBody.angularVelocity += rigidBody.inverseInertiaWorld * rigidBody.torqueAccumulator * deltaTime;

			rigidBody.velocity *= WaveMath::Pow(rigidBody.linearDamping, deltaTime);
			rigidBody.angularVelocity *= WaveMath::Pow(rigidBody.angularDamping, deltaTime);

			ECSTransform& transform = rigidBody.GetTransform();

			Vector3 centerOfMass = transform.WorldToLocal(rigidBody.centerOfMassLocal) + rigidBody.velocity * deltaTime;

			Quaternion orientation = transform.GetRotation();

			Quaternion spin = Quaternion(rigidBody.angularVelocity.x, rigidBody.angularVelocity.y, rigidBody.angularVelocity.z, 0.0f) * orientation;

			float half = 0.5f * deltaTime;

			orientation = Quaternion(
				orientation.x + spin.x * half,
				orientation.y + spin.y * half,
				orientation.z + spin.z * half,
				orientation.w + spin.w * half).Normalized();

			transform.SetRotation(orientation);

			transform.SetPosition(centerOfMass - orientation * (rigidBody.centerOfMassLocal * transform.GetLocalScale()));

			if (rigidBody.mass <= 0.0f)
				rigidBody.inverseInertiaWorld = Matrix3x3::Zero();
			else
				rigidBody.inverseInertiaWorld = Matrix3x3::Rotated(rigidBody.inverseInertiaLocal, transform.GetRotation());

			//for (int i = 0; i < colliders.Count; i++)
			//	colliders[i].MarkBoundsDirty();

			rigidBody.forceAccumulator = Vector3::Zero();
			rigidBody.torqueAccumulator = Vector3::Zero();

			rigidBody.isGrounded = false;

			rigidBody.GetTransform().Translate(rigidBody.GetVelocity() * deltaTime);
		}


	}
}
