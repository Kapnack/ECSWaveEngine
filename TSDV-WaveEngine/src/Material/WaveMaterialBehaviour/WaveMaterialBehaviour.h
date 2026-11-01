#pragma once
namespace WaveEngine
{
	class WaveMaterialBehaviour
	{
	private:

		unsigned int materialID;
		unsigned int currentWaveObject;

		WaveMaterialBehaviour();
		~WaveMaterialBehaviour();

		void SetWaveObject(unsigned int currentWaveObject);

	public:

		virtual void Init();
		virtual void LateInit();
		virtual void Update(float deltaTime);
		virtual void OnDestroy();
	};
}