#include "Window.h"

#include <iostream>

using namespace std;

namespace WaveEngine
{
	Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) : Service()
	{
		this->width = width;
		this->height = height;
		this->title = title;
		this->monitor = monitor;
		this->share = share;

		baseWidth = width;
		baseHeight = height;

		Init();
	}

	Window::~Window()
	{
		Unload();
	}

	void Window::Init()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, title, monitor, share);
		if (!window)
		{
			cout << "Failed to create GLFW window" << endl;
			glfwTerminate();

			exit(-1);
		}

		glfwMakeContextCurrent(window);

		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, Window::FrameBufferCallBack);

		if (glewInit() != GLEW_OK)
			cout << "GLEW FAILED TO INIT!!!";
	}

	GLFWwindow* Window::GetGLFWindow()
	{
		return window;
	}

	int Window::GetWidth()
	{
		return width;
	}

	int Window::GetHeight()
	{
		return height;
	}

	int Window::GetBaseWidth()
	{
		return baseWidth;
	}

	int Window::GetBaseHeight()
	{
		return baseHeight;
	}

	void Window::SwapBuffer()
	{
		glfwSwapBuffers(window);
	}

	void Window::HandleInput()
	{
		glfwPollEvents();
	}

	float Window::GetGLTime()
	{
		return static_cast<float>(glfwGetTime());
	}

	void Window::Unload()
	{
		glfwTerminate();
	}

	void Window::FrameBufferCallBack(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);

		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (!win)
			return;

		win->width = width;
		win->height = height;
	}
}