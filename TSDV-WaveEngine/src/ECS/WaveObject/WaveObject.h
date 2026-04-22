#pragma once

#include "EventSystem/EventSystem.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include <ECS/Transform/ECSTransform.h>

namespace WaveEngine::Objects
{
	class WaveObject
	{
	private:

		static const unsigned int NULL_OBJECT = 0;
		static unsigned int currentID;
		unsigned int ID = currentID;

		ComponentRegistry* GetComponentRegistry();

	protected:


		const unsigned int GetID() const;

	public:

		WaveObject()
		{
			ID = ++currentID;
			AddComponent<ECSTransform>();
		}

		template<typename T>
		void AddComponent(const int& entity)
		{
			type_index typeIndex = typeid(T);

			if (!storages.contains(typeIndex))
				return;

			static_cast<Storage<T>*>(storages.at(typeIndex))->container.Remove(entity);
		}


		template<typename T>
		void AddComponent()
		{
			GetComponentRegistry()->AddComponent<T>(ID);
		}

		template<typename T>
		void RemoveComponent()
		{
			GetComponentRegistry()->RemoveComponent<T>(ID);
		}
	};
}