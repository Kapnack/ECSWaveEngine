#pragma once

#include "Export.h"
#include "ECS/WObject/WObject.h"

namespace WaveEngine
{
	class Material;
	class WaveObject;
	class MaterialManager;

	class WAVEEXPORT WaveMaterialBehaviour : public WObject
	{
	private:

		unsigned int materialID;
		unsigned int currentWaveObject;

		WaveMaterialBehaviour();
		~WaveMaterialBehaviour();

		void SetMaterial(unsigned int materialID);
		void SetWaveObject(unsigned int currentWaveObject);

		friend class MaterialManager;

	protected:

		WaveObject& GetWaveObject() const;
		Material& GetMaterial() const;

	public:

		virtual void Init();
		virtual void LateInit();
		virtual void GeneralUpdate();
		virtual void Update();
		virtual void Dispose();
	};
}