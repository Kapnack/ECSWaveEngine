#pragma once

#include "Export.h"

namespace WaveEngine
{
	class ServiceProvider;

	class WAVEEXPORT Service
	{
	protected:

		Service();
		virtual ~Service();

		friend class ServiceProvider;
	};
}

