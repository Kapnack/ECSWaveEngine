#ifndef WAVE_ENGINE_FRAME_TPP
#define WAVE_ENGINE_FRAME_TPP

#include "Frame.h"

namespace WaveEngine
{
	Frame::Frame()
	{
	}

	Frame::Frame(Vector2 topLeft, Vector2 bottomRight)
	{
		this->topLeft = topLeft;
		this->bottomRight = bottomRight;
	}

	void Frame::SetCallback(void(*func)())
	{
		callback.Subscribe(func);
	}

	void Frame::Invoke()
	{
		callback.Invoke();
	}

	template<typename T>
	void Frame::SetCallback(T* instance, void(T::* func)())
	{
		callback.Subscribe<T>(instance, func);
	}
}
#endif