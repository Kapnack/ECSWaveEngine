#pragma once

#include "Export.h"

namespace WaveEngine
{
	class Engine;

	class WAVEEXPORT WaveManager
	{
	protected:

		WaveManager()
		{
		}

		virtual ~WaveManager()
		{

		}

		virtual void Init()
		{

		}

		virtual void LateInit()
		{

		}

		virtual void Update()
		{

		}

		virtual void Dispose()
		{

		}

		friend class Engine;
	};
}