#pragma once

#include "Frame.h"
#include "Export.h"

namespace WaveEngine
{
	WAVEEXPORT class Animation
	{
	private:

		const static float GetDefaultSpeed();

		float currentTime = 0;
		float animationTime = 0;
		float timePerFrame = 0;
		int framesQuantity = 0;
		float animationSpeed;

		Frame* frames = nullptr;

		int previousFrame = -1;
		unsigned int currentFrame = 0;

		bool paused = false;

		void KeepTimerInBounds();
		void SetCurrentFrame();
		void AddToTimer(float addition);

	public:

		Animation(Vector2 startCoords,
			Vector2 frameArea,
			Vector2 textureArea,
			int framesQuantity,
			float animationTime);

		~Animation();
		void Update(float deltaTime);
		WAVEEXPORT void MoveToNextFrame();
		WAVEEXPORT void MoveToPreviousFrame();
		WAVEEXPORT void GoToFrame(int index);
		WAVEEXPORT void ResetTime();
		WAVEEXPORT void Pause();
		WAVEEXPORT void UnPause();
		WAVEEXPORT void SetPause(bool paused);
		WAVEEXPORT void SwitchPauseState();
		WAVEEXPORT bool GetPause();
		WAVEEXPORT bool DidChangeFrame();

		WAVEEXPORT void SetSpeed(float speed);

		WAVEEXPORT Frame GetCurrentFrame() const;
		WAVEEXPORT Frame GetFrame(int index) const;

		WAVEEXPORT void SetCallbackToFrame(int index, void(*func)());

		template<typename T>
		void SetCallbackToFrame(int index, T* instance, void(T::* func)());
	};
}
#include "Animation.tpp"