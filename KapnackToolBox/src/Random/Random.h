#pragma once

#include <random>
#include <typeindex>
#include <type_traits>
#include <unordered_map>

#include "EventSystem/Func.h"
#include "EventSystem/Delegate.h"
#include "ServiceProvider/Service.h"
#include "WaveMath/Vector2/Vector2.h"
#include "WaveMath/Vector3/Vector3.h"
#include "WaveMath/Vector4/Vector4.h"

using namespace std;

namespace WaveEngine
{
	class Random : public Service
	{
	private:

		mt19937 randomEngine;
		uniform_int_distribution<mt19937::result_type> distribution;

		unordered_map<type_index, Delegate*> randomStrategy;
		unordered_map<type_index, Delegate*> randomRangeStrategy;

	protected:

		template<typename TValue, typename TClass>
		void AddToTemplateRandom(TValue(TClass::* func)())
		{
			randomStrategy[typeid(TValue)] = new Func<TValue>();
			static_cast<Func<TValue>*>(randomStrategy[typeid(TValue)])->Subscribe(this, func);
		}

		template<typename TValue, typename TClass>
		void AddToTemplateRandomRange(TValue(TClass::* func)(TValue, TValue))
		{
			randomRangeStrategy[typeid(TValue)] = new Func<TValue, TValue, TValue>();
			static_cast<Func<TValue, TValue, TValue>*>(randomRangeStrategy[typeid(TValue)])->Subscribe(this, func);
		}

	public:

		Random()
		{
		}

		~Random()
		{
			for (unordered_map<type_index, Delegate*>::iterator it = randomStrategy.begin(); it != randomStrategy.end(); ++it)
				delete it->second;

			for (unordered_map<type_index, Delegate*>::iterator it = randomRangeStrategy.begin(); it != randomRangeStrategy.end(); ++it)
				delete it->second;
		}

		virtual void Init()
		{
			randomEngine.seed(random_device()());

			const int randomizableTypes = 13;
			const int rangeRandomizableTypes = randomizableTypes - 1;

			randomStrategy.reserve(randomizableTypes);
			randomRangeStrategy.reserve(rangeRandomizableTypes);

			AddToTemplateRandom(&Random::Bool);

			AddToTemplateRandom(&Random::Int);
			AddToTemplateRandomRange(&Random::IntRange);

			AddToTemplateRandom(&Random::Char);
			AddToTemplateRandomRange(&Random::CharRange);

			AddToTemplateRandom(&Random::ShortInt);
			AddToTemplateRandomRange(&Random::ShortIntRange);

			AddToTemplateRandom(&Random::UnsignedInt);
			AddToTemplateRandomRange(&Random::UnsignedIntRange);

			AddToTemplateRandom(&Random::Long);
			AddToTemplateRandomRange(&Random::LongRange);

			AddToTemplateRandom(&Random::LongLong);
			AddToTemplateRandomRange(&Random::LongLongRange);

			AddToTemplateRandom(&Random::Float);
			AddToTemplateRandomRange(&Random::FloatRange);

			AddToTemplateRandom(&Random::Double);
			AddToTemplateRandomRange(&Random::DoubleRange);

			AddToTemplateRandom(&Random::RandomVector2);
			AddToTemplateRandomRange(&Random::Vector2Range);

			AddToTemplateRandom(&Random::RandomVector3);
			AddToTemplateRandomRange(&Random::Vector3Range);

			AddToTemplateRandom(&Random::RandomVector4);
			AddToTemplateRandomRange(&Random::Vector4Range);
		}

		template <typename TValue>
		TValue RandomRange(TValue min, TValue max)
		{
			return static_cast<Func<TValue, TValue, TValue>*>(randomRangeStrategy[typeid(TValue)])->Invoke(min, max);
		}

		template <typename TValue>
		TValue RandomValue()
		{
			return static_cast<Func<TValue>*>(randomStrategy[typeid(TValue)])->Invoke();
		}

		bool Bool()
		{
			uniform_int_distribution<int> boolDist(0, 1);
			return boolDist(randomEngine);
		}

		int Int()
		{
			return IntRange(numeric_limits<int>::min(), numeric_limits<int>::max());
		}

		int IntRange(int min, int max)
		{
			uniform_int_distribution<int> intDist(min, max);
			return intDist(randomEngine);
		}

		char Char()
		{
			return CharRange(numeric_limits<char>::min(), numeric_limits<char>::max());
		}

		char CharRange(char min, char max)
		{
			uniform_int_distribution<int> charDist(static_cast<int>(min), static_cast<int>(max));
			return static_cast<char>(charDist(randomEngine));
		}

		short int ShortInt()
		{
			return ShortIntRange(numeric_limits<short int>::min(), numeric_limits<short int>::max());
		}

		short int ShortIntRange(short int min, short int max)
		{
			uniform_int_distribution<short int> shortIntDist(min, max);
			return shortIntDist(randomEngine);
		}

		unsigned int UnsignedInt()
		{
			return UnsignedIntRange(0u, numeric_limits<unsigned int>::max());
		}

		unsigned int UnsignedIntRange(unsigned int min, unsigned int max)
		{
			uniform_int_distribution<unsigned int> unsignedIntDist(min, max);
			return unsignedIntDist(randomEngine);
		}

		long Long()
		{
			return LongRange(numeric_limits<long>::min(), numeric_limits<long>::max());
		}

		long LongRange(long min, long max)
		{
			uniform_int_distribution<long> longDist(min, max);
			return longDist(randomEngine);
		}

		long long LongLong()
		{
			return LongLongRange(numeric_limits<long long>::min(), numeric_limits<long long>::max());
		}

		long long LongLongRange(long long min, long long max)
		{
			uniform_int_distribution<long long> longLongDist(min, max);
			return longLongDist(randomEngine);
		}

		float Float()
		{
			return FloatRange(numeric_limits<float>::min(), numeric_limits<float>::max());
		}

		float FloatRange(float min, float max)
		{
			uniform_real_distribution<float> floatDist(min, max);
			return floatDist(randomEngine);
		}

		double Double()
		{
			return DoubleRange(numeric_limits<double>::min(), numeric_limits<double>::max());
		}

		double DoubleRange(double min, double max)
		{
			uniform_real_distribution<double> doubleDist(min, max);
			return doubleDist(randomEngine);
		}

		Vector2 RandomVector2()
		{
			return Vector2Range(Vector2::NMax(), Vector2::Max());
		}

		Vector2 Vector2Range(Vector2 min, Vector2 max)
		{
			return Vector2(FloatRange(min.x, max.x), FloatRange(min.y, max.y));
		}

		Vector3 RandomVector3()
		{
			return Vector3Range(Vector3::Min(), Vector3::Max());
		}

		Vector3 Vector3Range(Vector3 min, Vector3 max)
		{
			return Vector3(FloatRange(min.x, max.x), FloatRange(min.y, max.y), FloatRange(min.z, max.z));
		}

		Vector4 RandomVector4()
		{
			return Vector4Range(Vector4::Min(), Vector4::Max());
		}

		Vector4 Vector4Range(Vector4 min, Vector4 max)
		{
			return Vector4(FloatRange(min.x, max.x), FloatRange(min.y, max.y), FloatRange(min.z, max.z), FloatRange(min.w, max.w));
		}
	};
}