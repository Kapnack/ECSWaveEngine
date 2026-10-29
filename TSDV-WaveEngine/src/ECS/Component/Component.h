#pragma once

#include "Export.h"
#include "ECS/WObject/WObject.h"

namespace WaveEngine
{
	class WaveObject;
	class ECSTransform;
	class BoundingBoxComp;

	class WAVEEXPORT Component : public WObject
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
		virtual void Dispose();

		WaveObject& GetWaveObject() const;

		ECSTransform& GetTransform() const;

		BoundingBoxComp& GetBounds() const;

		unsigned int GetID() const;

		virtual void SetIsActive(bool isActive);
		bool GetIsActive() const;

		Component() = default;
	};
}