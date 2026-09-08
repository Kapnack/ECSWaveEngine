#include "WaveBehaviour.h"

#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	WaveObject& WaveBehaviour::Instantiate() const
	{
		return GetWaveObjectFactory()->Instantiate();
	}
}
