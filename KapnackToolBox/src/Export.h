#pragma once

#ifdef MAKEDLL
#  define WAVEEXPORT __declspec(dllexport)
#else
#  define WAVEEXPORT __declspec(dllimport)
#endif
#define IMGUI_DEFINE_MATH_OPERATORS