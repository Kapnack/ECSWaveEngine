#pragma once

#include "ServiceProvider/Service.h"

#include "Window/Window.h"
#include "Input/Input.h"

using namespace std;

class BaseGame;

namespace WaveEngine
{
	class ImGuiClass final
	{
	private:

		Window* GetWindow();

		Input* GetInput();

		bool isActive = false;

		void Init();
		void Update();
		void Draw();
		void Unload();

		ImGuiClass();
		~ImGuiClass();

		friend class BaseGame;
		friend class ServiceProvider;

	public:

		static bool thirdPersonCamera;
	};
}