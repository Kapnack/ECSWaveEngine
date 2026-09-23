#pragma once

#include "Export.h"
#include "EventSystem/Action.h"
#include "WaveMath/Vector2/Vector2.h"

namespace WaveEngine
{
	WAVEEXPORT struct Frame
	{
	public:

		Vector2 topLeft;
		Vector2 bottomRight;

		Action<> callback;

		WAVEEXPORT Frame();

		WAVEEXPORT Frame(Vector2 topLeft, Vector2 bottomRight);

		WAVEEXPORT void SetCallback(void(*func)());

		template<typename T>
		void SetCallback(T* instance, void(T::* func)());

		WAVEEXPORT void Invoke();
	};
}

#include "Frame.tpp"