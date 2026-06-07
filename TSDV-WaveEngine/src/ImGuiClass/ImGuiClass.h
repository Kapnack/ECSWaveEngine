#pragma once

#include "Window/Window.h"
#include "Input/Input.h"
#include <ECS/WaveObject/WaveObjectRegistry.h>
#include <WaveMath/Vector3/Vector3.h>

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

		Vector3 newPos = Vector3::Zero();
		Vector3 newRot = Vector3::Zero();
		Vector3 newScale = Vector3::Zero();

		void Init();
		void Update();
		void Draw();
		void Unload();

		ImGuiClass();
		~ImGuiClass();

		WaveObjectRegistry* GetWaveObjectRegistry();

		friend class BaseGame;
		friend class ServiceProvider;

	public:

		static bool thirdPersonCamera;
	};
}