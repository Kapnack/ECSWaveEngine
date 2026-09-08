#pragma once

#include <concepts>

namespace WaveEngine
{
	class Component;

	template<typename T>
	concept TypeComponent = std::derived_from<T, Component>;
}