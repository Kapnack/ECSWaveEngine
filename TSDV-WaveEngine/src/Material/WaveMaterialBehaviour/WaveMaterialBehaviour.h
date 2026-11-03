#pragma once

#include "Export.h"
#include "ECS/WObject/WObject.h"

namespace WaveEngine
{
	class Camera;
	class Renderer;
	class Material;
	class WaveObject;
	class MaterialManager;

	class WAVEEXPORT WaveMaterialBehaviour : public WObject
	{
	private:

		unsigned int materialID = WObject::NULL_OBJECT;
		unsigned int currentWaveObjectID = WObject::NULL_OBJECT;
		unsigned int currentCameraID = WObject::NULL_OBJECT;

		WaveMaterialBehaviour();
		~WaveMaterialBehaviour();

		void SetCamera(unsigned int cameraID);
		void SetMaterial(unsigned int materialID);
		void SetWaveObject(unsigned int waveObjectID);

		void UnBind();

		friend class Renderer;
		friend class MaterialManager;

	protected:

		Camera& GetCamera() const;
		Material& GetMaterial() const;
		WaveObject& GetWaveObject() const;

		virtual void Init();
		virtual void LateInit();
		virtual void GeneralUpdate();
		virtual void Update();
		virtual void Dispose();
	};
}