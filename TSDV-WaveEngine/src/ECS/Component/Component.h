#pragma once

namespace WaveEngine
{
	class WaveObject;
	class ECSTransform;

	class Component
	{
	private:

		unsigned int ownerID = 0;
		bool isActive = true;

	public:

		static const unsigned int NULL_COMPONENT = 0;

		Component(const unsigned int ID);
		~Component();

		WaveObject& GetWaveObject() const;

		ECSTransform& GetTransform() const;

		const unsigned int& GetID() const;

		virtual void SetIsActive(bool isActive);
		bool GetIsActive() const;
	};
}