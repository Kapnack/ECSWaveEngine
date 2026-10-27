#pragma once

#include "ServiceProvider/Service.h"

#include "Export.h"
#include "Window/Window.h"

class BaseGame;

namespace WaveEngine
{
	class WAVEEXPORT Time : public Service
	{
	private:

		float deltaTime = 0;
		float lastTime = 0;

		float timeScale = 1;

		Window* GetWindow();

		Time();
		~Time();

		void UpdateDeltaTime();

		friend class Engine;
		friend class ServiceProvider;

	public:

		static Time& Get();

		float GetDeltaTime() const;
		void SetTimeScale(float timeScale);
	};
}

