#pragma once
namespace WaveEngine
{
	class WaveMaterialBehaviour
	{
	private:

		unsigned int materialID;

		WaveMaterialBehaviour();
		~WaveMaterialBehaviour();

	public:

		virtual void Init();
		virtual void LateInit();
		virtual void Update(float deltaTime);
		virtual void OnDestroy();
	};
}