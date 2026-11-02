#pragma once

#include "Export.h"
#include "Material/Material.h"
#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	class WAVEEXPORT WaveMaterialBehaviour
	{
	private:

		unsigned int materialID;
		unsigned int currentWaveObject;

		WaveMaterialBehaviour();
		~WaveMaterialBehaviour();

		void SetMaterial(unsigned int materialID);
		void SetWaveObject(unsigned int currentWaveObject);

	protected:

		WaveObject& GetWaveObject() const;
		Material& GetMaterial() const;

	public:

		virtual void Init();
		virtual void LateInit();
		virtual void GeneralUpdate(float deltaTime);
		virtual void Update(float deltaTime);
		virtual void Dispose();
	};
}