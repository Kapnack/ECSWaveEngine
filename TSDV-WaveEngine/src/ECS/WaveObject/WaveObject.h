#pragma once

#include "ECS/CompontRegistry/ComponentRegistry.h"
#include <ECS/Transform/ECSTransform.h>

class WaveObjectFactory;

namespace WaveEngine::Objects
{
	class WaveObject
	{
	private:

		unsigned int ID = NULL_OBJECT;

		ComponentRegistry* GetComponentRegistry();


		friend class WaveObjectFactory;

	public:

		ECSTransform* transform;

		WaveObject(const unsigned int& ID)
		{
			this->ID = ID;
		}

		static const unsigned int NULL_OBJECT = 0;

		const unsigned int GetID() const;

		ECSTransform& GetTransform();

		template<typename T>
		T& AddComponent()
		{
			return GetComponentRegistry()->AddComponent<T>(ID);
		}

		template<typename T>
		T& GetComponent()
		{
			return GetComponentRegistry()->GetComponent<T>(ID);
		}

		template<typename T>
		void RemoveComponent()
		{
			GetComponentRegistry()->RemoveComponent<T>(ID);
		}
	};
}