#pragma once

#ifdef _WIN32
#  ifdef MAKEDLL
#    define WAVEEXPORT __declspec(dllexport)
#  else
#    define WAVEEXPORT __declspec(dllimport)
#  endif
#else
#  define WAVEEXPORT __attribute__((visibility("default")))
#endif

#define IMGUI_DEFINE_MATH_OPERATORS