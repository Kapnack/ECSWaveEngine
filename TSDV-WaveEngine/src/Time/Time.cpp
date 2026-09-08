#include "Time.h"

namespace WaveEngine
{
	Time::Time() : Service()
	{
	}

	Time::~Time()
	{
	}

	Window* Time::GetWindow()
	{
		return ServiceProvider::Instance().Get<Window>();
	}

	void Time::UpdateDeltaTime()
	{
		float actualTime = GetWindow()->GetGLTime();

		deltaTime = actualTime - lastTime * timeScale;

		lastTime = actualTime;
	}

	Time& Time::Get()
	{
		return *ServiceProvider::Instance().Get<Time>();
	}

	float Time::GetDeltaTime() const
	{
		return deltaTime;
	}

	void Time::SetTimeScale(const float& timeScale)
	{
		this->timeScale = timeScale;
	}
}
