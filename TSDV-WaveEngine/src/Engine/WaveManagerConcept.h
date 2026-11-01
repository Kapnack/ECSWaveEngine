#pragma once

#include <type_traits>

#include "Engine/WaveManager.h"

using namespace std;

namespace WaveEngine
{
	template<typename T>
	concept WaveManagerConcept = is_base_of_v<WaveManager, T>;
}