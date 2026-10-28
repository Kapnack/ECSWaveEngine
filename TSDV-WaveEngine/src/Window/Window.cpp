#include "Window.h"

#include <vector>
#include <iostream>
#include <algorithm>

#include "EventSystem/Action.h"
#include "TextureImporter/Texture.h"
#include "WaveMath/Vector2/Vector2.h"

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

	Vector2 Window::GetSize()
	{
		return Vector2(static_cast<float>(width), static_cast<float>(height));
	}

	Vector2 Window::GetPosition()
	{
		int x = 0;
		int y = 0;

		glfwGetWindowPos(window, &x, &y);

		return Vector2(x, y);
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
		const int w = texture.GetWidth();
		const int h = texture.GetHeight();

		vector<unsigned char> pixels(w * h * 4);

		glBindTexture(GL_TEXTURE_2D, texture.GetGPUID());
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

		const int rowSize = w * 4;
		for (int y = 0; y < h / 2; ++y)
		{
			swap_ranges(
				pixels.begin() + y * rowSize,
				pixels.begin() + (y + 1) * rowSize,
				pixels.begin() + (h - 1 - y) * rowSize);
		}

		GLFWimage icon{ w, h, pixels.data() };
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
		this->width = width;
		this->height = height;

		glfwSetWindowSize(window, width, height);
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