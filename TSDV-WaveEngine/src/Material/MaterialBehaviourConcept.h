#pragma once

#include <type_traits>

using namespace std;

namespace WaveEngine
{
	class WaveMaterialBehaviour;

	template<typename T>
	concept MaterialBehaviourConcept = is_base_of_v<WaveMaterialBehaviour, T>;
}