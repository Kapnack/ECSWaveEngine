#pragma once

#include "Window/Window.h"
#include "Input/Input.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "Material/MaterialManager.h"

using namespace std;

class BaseGame;

namespace WaveEngine
{
	class ImGuiClass final
	{
	private:

		Window* GetWindow();

		Input* GetInput();

		Color color = Color::White();

		void Init();
		void Update();
		void Draw();
		void Unload();

		ImGuiClass();
		~ImGuiClass();

		WaveObjectRegistry* GetWaveObjectRegistry();
		MaterialManager* GetMaterialManager();

		friend class BaseGame;
		friend class ServiceProvider;

	public:

		static bool thirdPersonCamera;
	};
}