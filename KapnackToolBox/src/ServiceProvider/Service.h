#pragma once

#include "Export.h"

namespace WaveEngine
{
	class ServiceProvider;

	WAVEEXPORT class Service
	{
	protected:

		WAVEEXPORT Service();
		WAVEEXPORT virtual ~Service();

		friend class ServiceProvider;
	};
}

