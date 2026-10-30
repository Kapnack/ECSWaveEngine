#include "Engine/Engine.h"
#include "Engine/WaveManager.h"
#include "ECS/WObject/WObject.h"
#include "Engine/TestingBehaviour.h"
#include "ECS/WaveObject/WaveObject.h"

using namespace WaveEngine;

class TestingManager : public WaveManager
{
protected:

	void Init() override
	{
		WaveObject waveObject;

		waveObject.AddComponent<TanakaWaveBehaviour>();
	}
};

int main()
{
	Engine::StartEngine<TestingManager>();

	return 0;
}