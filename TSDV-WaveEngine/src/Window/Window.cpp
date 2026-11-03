#include "Window.h"

#include <vector>
#include <iostream>
#include <algorithm>

#include "EventSystem/Action.h"
#include "TextureImporter/Texture.h"
#include "WaveMath/Vector2/Vector2.h"
#include "ServiceProvider/ServiceProvider.h"

using namespace std;

namespace WaveEngine
{
	Window::Window(int width, int height, const char* title, bool vSync, GLFWmonitor* monitor, GLFWwindow* share) : Service()
	{
		this->width = width;
		this->height = height;
		this->title = title;
		this->monitor = monitor;
		this->share = share;

		baseWidth = width;
		baseHeight = height;
		this->vSyncMode = vSync;
	}

	Window::~Window()
	{
	}

	void Window::Init()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

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

		SetVSyncMode(vSyncMode);

		if (glewInit() != GLEW_OK)
			cout << "GLEW FAILED TO INIT!!!";
	}

	Window& Window::Get()
	{
		return *ServiceProvider::Instance().Get<Window>();
	}

	GLFWwindow* Window::GetGLFWindow()
	{
		return window;
	}

	int Window::GetWidth() const
	{
		return width;
	}

	int Window::GetHeight() const
	{
		return height;
	}

	int Window::GetBaseWidth() const
	{
		return baseWidth;
	}

	int Window::GetBaseHeight() const
	{
		return baseHeight;
	}

	Vector2 Window::GetSize() const
	{
		return Vector2(static_cast<float>(width), static_cast<float>(height));
	}

	Vector2 Window::GetPosition() const
	{
		int x = 0;
		int y = 0;

		glfwGetWindowPos(window, &x, &y);

		return Vector2(x, y);
	}

	int Window::GetVSyncMode() const
	{
		return vSyncMode;
	}

	void Window::HideWindow() const
	{
		glfwHideWindow(window);
	}

	void Window::ShowWindow() const
	{
		glfwShowWindow(window);
	}

	void Window::SetTitle(const char* title)
	{
		glfwSetWindowTitle(window, title);
	}

	void Window::SetIcon(const Texture& texture)
	{
		GLFWimage icon{ texture.GetWidth(), texture.GetHeight(), texture.GetPixels().data() };
		glfwSetWindowIcon(window, 1, &icon);
	}

	void Window::SetPosition(Vector2 position)
	{
		SetPosition(static_cast<int>(position.x), static_cast<int>(position.y));
	}

	void Window::SetPosition(int x, int y)
	{
		glfwSetWindowPos(window, x, y);
	}

	void Window::Translate(Vector2 position)
	{
		Translate(static_cast<int>(position.x), static_cast<int>(position.y));
	}

	void Window::Translate(int x, int y)
	{
		Vector2 currentPosition = GetPosition();
		glfwSetWindowPos(window, static_cast<int>(currentPosition.x) + static_cast<int>(x), static_cast<int>(currentPosition.y) + static_cast<int>(y));
	}

	void Window::SetSize(Vector2 size)
	{
		SetSize(static_cast<int>(size.x), static_cast<int>(size.y));
	}

	void Window::SetSize(int width, int height)
	{
		glfwSetWindowSize(window, this->width = width, this->height = height);
	}

	void Window::SetVSyncMode(int vSyncMode)
	{
		glfwSwapInterval(this->vSyncMode = vSyncMode);
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

	void Window::Dispose()
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