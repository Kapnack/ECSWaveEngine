#pragma once

#include "Random/Random.h"

#include "Material/Color/Color.h"
#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine
{
	class WaveRandom : public Random
	{
	public:

		WaveRandom() : Random()
		{

		}

		~WaveRandom()
		{

		}

		static WaveRandom* Get()
		{
			return ServiceProvider::Instance().Get<WaveRandom>();
		}

		void Init() override
		{
			Random::Init();

			AddToTemplateRandom(&WaveRandom::RandomColor);
			AddToTemplateRandomRange(&WaveRandom::ColorRange);
		}

		Color RandomColor()
		{
			return Color(Float(), Float(), Float(), Float());
		}

		Color ColorRange(Color min, Color max)
		{
			return Color(FloatRange(min.r, max.r), FloatRange(min.g, max.g), FloatRange(min.b, max.b), FloatRange(min.a, max.a));
		}
	};
}