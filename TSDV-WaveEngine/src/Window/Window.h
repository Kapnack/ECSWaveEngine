#pragma once

#include "ServiceProvider/Service.h"

#include "Export.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace WaveEngine
{
	class BaseGame;
	class ServiceProvider;

	WAVEEXPORT class Window final : public Service
	{
	private:

		GLFWwindow* window = nullptr;

		int width = 0;
		int height = 0;

		int baseWidth = 0;
		int baseHeight = 0;

		const char* title;
		GLFWmonitor* monitor;
		GLFWwindow* share;

		void Init();
		void Unload();

		static void FrameBufferCallBack(GLFWwindow* window, int width, int height);

		Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
		~Window();

		friend class BaseGame;
		friend class ServiceProvider;

	public:

		GLFWwindow* GetGLFWindow();
		WAVEEXPORT int GetWidth();
		WAVEEXPORT int GetHeight();
		WAVEEXPORT int GetBaseWidth();
		WAVEEXPORT int GetBaseHeight();

		WAVEEXPORT void SwapBuffer();
		WAVEEXPORT void HandleInput();

		WAVEEXPORT float GetGLTime();
	};
}