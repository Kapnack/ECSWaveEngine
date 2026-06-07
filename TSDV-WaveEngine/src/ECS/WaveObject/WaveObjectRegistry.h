#pragma once

#include <map>

#include "ServiceProvider/Service.h"
#include "WaveObject.h"

using namespace std;

class BaseGame;
class ServiceProvider;

namespace WaveEngine
{
	class WaveObjectRegistry : Service
	{
	private:

		map<unsigned int, WaveObject*> waveObjects;

		friend class BaseGame;
		friend class ServiceProvider;

	public:

		WaveObjectRegistry();
		~WaveObjectRegistry();

		void AddObject(WaveObject*& newWaveObject);

		map<unsigned int, WaveObject*>& GetWaveObjects();

		WaveObject& GetWaveObject(const unsigned int& ID);
	};
}