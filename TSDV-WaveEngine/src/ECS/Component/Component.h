#pragma once

#include "TypeComponent.h"
#include "ECS/WaveObject/WObject.h"

namespace WaveEngine
{
	class WaveObject;
	class ECSTransform;

	class Component : public WObject
	{
	private:

		unsigned int ownerID = 0;
		bool isActive = true;

	public:

		static const unsigned int NULL_COMPONENT = 0;

		Component(unsigned int ID);
		~Component();

		virtual void Init();
		virtual void LateInit();

		WaveObject& GetWaveObject() const;

		ECSTransform& GetTransform() const;

		unsigned int GetID() const;

		virtual void SetIsActive(bool isActive);
		bool GetIsActive() const;

		template<TypeComponent T>
		T& AddComponent();

		template<TypeComponent T>
		T& GetComponent() const;

		template<TypeComponent T>
		T* TryGetComponent();

		template<TypeComponent T>
		void RemoveComponent();
	};
}

#include "Component.tpp"