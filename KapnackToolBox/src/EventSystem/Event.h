#pragma once

#include "Export.h"

namespace WaveEngine
{
	struct WAVEEXPORT Event
	{
		Event();
		~Event();

		virtual void Reset() = 0;
	};
}