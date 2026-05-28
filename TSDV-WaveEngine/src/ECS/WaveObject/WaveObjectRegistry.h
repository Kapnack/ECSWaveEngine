#pragma once

#include <map>

#include "ServiceProvider/Service.h"
#include "WaveObject.h"

using namespace std;
using namespace WaveEngine::Objects;

class WaveObjectFactory;
class BaseGame;
class ServiceProvider;

namespace WaveEngine
{
	class WaveObjectRegistry : Service
	{
	private:

		map<unsigned int, WaveObject*> waveObjects;

		friend class WaveObjectFactory;
		friend class BaseGame;
		friend class ServiceProvider;

	public:

		WaveObjectRegistry();
		~WaveObjectRegistry();

		void AddObject(WaveObject*& newWaveObject);

		WaveObject& GetWaveObject(const unsigned int& ID);
	};
}