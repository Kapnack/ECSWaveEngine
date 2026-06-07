#pragma once

namespace WaveEngine
{
	class WaveObject;

	class Component
	{
	private:

		unsigned int ownerID = 0;

	public:

		Component(const unsigned int& ID);
		~Component();

		WaveObject& GetWaveObject() const;

		const unsigned int& GetID() const;
	};
}