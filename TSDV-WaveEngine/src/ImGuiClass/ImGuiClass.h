#pragma once

#include "Input/Input.h"
#include "Window/Window.h"
#include "Material/Color/Color.h"
#include "Material/MaterialManager.h"
#include "WaveMath/Vector3/Vector3.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"

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

		Vector3 position;

		void Init();
		void Update();
		void Draw();
		void Dispose();

		ImGuiClass();
		~ImGuiClass();

		WaveObjectRegistry* GetWaveObjectRegistry();
		MaterialManager* GetMaterialManager();

		friend class Engine;
		friend class ServiceProvider;

	public:

		static bool thirdPersonCamera;
	};
}