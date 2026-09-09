#pragma once

#include <concepts>
#include "ECS/Component/Component.h"

namespace WaveEngine
{
	template<typename T>
	concept TypeComponent = std::derived_from<T, Component>;
}