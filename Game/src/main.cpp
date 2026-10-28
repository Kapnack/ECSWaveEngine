#include "Engine/Engine.h"
#include "Engine/WaveManager.h"
#include "Engine/TestingBehaviour.h"

using namespace WaveEngine;

class TestingManager : public WaveManager
{
protected:

	void LateInit() override
	{
		WObject::Instantiate<TanakaWaveBehaviour>();
	}
};

int main()
{
	Engine::StartEngine<TestingManager>();

	return 0;
}