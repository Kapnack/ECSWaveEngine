#ifndef WAVE_ENGINE_ANIMATION_TPP
#define WAVE_ENGINE_ANIMATION_TPP

#include "Animation.h"

#include "Frame.h"

namespace WaveEngine
{
	const float Animation::GetDefaultSpeed()
	{
		return 1;
	}

	Animation::Animation(
		Vector2 startCoords,
		Vector2 frameArea,
		Vector2 textureArea,
		int framesQuantity,
		float animationTime
	)
	{
		this->animationSpeed = GetDefaultSpeed();
		this->currentFrame = 0;
		this->currentTime = 0.0f;
		this->animationTime = animationTime;
		this->framesQuantity = framesQuantity;

		float frameWidthFloat = frameArea.x;
		float frameHeightFloat = frameArea.y;
		float textureWidth = textureArea.x;
		float textureHeight = textureArea.y;

		Vector2 startUVCoords =
		{
			startCoords.x / textureWidth,
			startCoords.y / textureHeight
		};

		frames = new Frame[framesQuantity];

		for (int i = 0; i < framesQuantity; i++)
		{
			Vector2 leftTopUVCoords =
			{
				startUVCoords.x + ((i * frameWidthFloat) / textureWidth),
				startUVCoords.y
			};

			Vector2 rightBottomUVCoords =
			{
				startUVCoords.x + frameWidthFloat / textureWidth + ((i * frameWidthFloat) / textureWidth),
				startUVCoords.y - (frameHeightFloat / textureHeight)
			};

			frames[i] = Frame(leftTopUVCoords, rightBottomUVCoords);
		}

		timePerFrame = animationTime / framesQuantity;
	}

	Animation::~Animation()
	{
		delete[] frames;
	}

	void Animation::KeepTimerInBounds()
	{
		while (currentTime >= animationTime)
			currentTime -= animationTime;
	}

	void Animation::SetCurrentFrame()
	{
		currentFrame = static_cast<int>(currentTime / timePerFrame);
	}

	void Animation::AddToTimer(float addition)
	{
		int auxFrame = currentFrame;

		currentTime += addition;

		KeepTimerInBounds();

		SetCurrentFrame();

		if (auxFrame != currentFrame)
		{
			previousFrame = auxFrame;
			frames[currentFrame].Invoke();
		}
	}

	Frame Animation::GetCurrentFrame() const
	{
		return frames[currentFrame];
	}

	Frame Animation::GetFrame(int index) const
	{
		index = index % framesQuantity;
		return frames[index];
	}

	void Animation::SetCallbackToFrame(int index, void(*func)())
	{
		if (index >= framesQuantity)
			return;

		frames[index].SetCallback(func);
	}

	void Animation::Update(float deltaTime)
	{
		if (paused)
			return;

		AddToTimer(animationSpeed * deltaTime);
	}

	void Animation::MoveToNextFrame()
	{
		AddToTimer(timePerFrame);
	}

	void Animation::MoveToPreviousFrame()
	{
		AddToTimer(-timePerFrame);
	}

	void Animation::GoToFrame(int index)
	{
		ResetTime();

		for (int i = 0; i < index; ++i)
			AddToTimer(timePerFrame);
	}

	void Animation::ResetTime()
	{
		currentTime = 0;
		previousFrame = -1;
	}

	void Animation::Pause()
	{
		paused = true;
	}

	void Animation::UnPause()
	{
		paused = false;
	}

	void Animation::SetPause(bool paused)
	{
		this->paused = paused;
	}

	void Animation::SwitchPauseState()
	{
		paused = !paused;
	}

	bool Animation::GetPause()
	{
		return paused;
	}

	bool Animation::DidChangeFrame()
	{
		return previousFrame != currentFrame;
	}

	void Animation::SetSpeed(float speed)
	{
		animationSpeed = speed;
	}

	template<typename T>
	void Animation::SetCallbackToFrame(int index, T* instance, void(T::* func)())
	{
		if (index >= framesQuantity)
			return;

		frames[index].SetCallback(instance, func);
	}
}
#endif
