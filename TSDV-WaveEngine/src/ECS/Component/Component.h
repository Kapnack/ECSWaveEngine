#pragma once

namespace WaveEngine
{
	class WaveObject;
	class ECSTransform;

	class Component
	{
	private:

		unsigned int ownerID = 0;

	public:

		Component(const unsigned int& ID);
		~Component();

		WaveObject& GetWaveObject() const;

		ECSTransform& GetTransform() const;

		const unsigned int& GetID() const;
	};
}