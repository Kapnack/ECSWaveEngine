#pragma once

#include "ServiceProvider/Service.h"

#include "Export.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "EventSystem/Action.h"
#include "TextureImporter/Texture.h"
#include "WaveMath/Vector2/Vector2.h"

namespace WaveEngine
{
	class Engine;
	class ServiceProvider;

	class WAVEEXPORT Window final : public Service
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
		void Dispose();

		static void FrameBufferCallBack(GLFWwindow* window, int width, int height);

		Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
		~Window();

		friend class Engine;
		friend class ServiceProvider;

	public:

		static Window& Get();

		GLFWwindow* GetGLFWindow();
		int GetWidth() const;
		int GetHeight() const;
		int GetBaseWidth() const;
		int GetBaseHeight() const;
		Vector2 GetSize() const;
		Vector2 GetPosition() const;

		void HideWindow() const;
		void ShowWindow() const;

		void SetTitle(const char* title);
		void SetIcon(const Texture& texture);
		void SetPosition(Vector2 position);
		void SetPosition(int x, int y);
		void Translate(Vector2 position);
		void Translate(int x, int y);
		void SetSize(Vector2 size);
		void SetSize(int width, int height);

		void SwapBuffer();
		void HandleInput();

		float GetGLTime();
	};
}