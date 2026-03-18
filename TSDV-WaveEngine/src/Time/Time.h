#pragma once

#include "ServiceProvider/Service.h"
#include "ServiceProvider/ServiceProvider.h"

#include "Export.h"
#include "Window/Window.h"

class BaseGame;

namespace WaveEngine
{
	WAVEEXPORT class Time : public Service
	{
	private:

		float deltaTime = 0;
		float lastTime = 0;

		float timeScale = 1;

		Window* GetWindow();

		Time();
		~Time();

		void UpdateDeltaTime();

		friend class BaseGame;
		friend class ServiceProvider;

	public:

		WAVEEXPORT float GetDeltaTime() const;
		WAVEEXPORT void SetTimeScale(const float& timeScale);
	};
}

