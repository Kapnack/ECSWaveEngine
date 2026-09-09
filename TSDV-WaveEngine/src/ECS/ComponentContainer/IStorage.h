#pragma once

namespace WaveEngine
{
	class WaveBehaviour;

	class IStorage
	{
	public:

		IStorage()
		{
		}

		~IStorage()
		{
		}

		virtual WaveBehaviour* GetAsWaveBehaviour(unsigned int entity);
	};
}