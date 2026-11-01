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

		bool isActive = true;

	public:

		Component();
		virtual ~Component();

		virtual void Init();
		virtual void LateInit();
		virtual void Dispose();

		WaveObject& GetWaveObject() const;

		ECSTransform& GetTransform() const;

		BoundingBoxComp& GetBounds() const;

		virtual void SetActive(bool isActive);
		bool GetIsActive() const;
	};
}