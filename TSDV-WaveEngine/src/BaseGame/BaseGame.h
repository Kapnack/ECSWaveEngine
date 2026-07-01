#pragma once

#include "Export.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Time/Time.h"
#include "Input/Input.h"
#include "Material/MaterialManager.h"
#include "FileReader/FileReader.h"
#include "Mesh/MeshFactory/MeshFactory.h"
#include "Mesh/MeshManager/MeshManager.h"

#include "EventSystem/EventSystem.h"
#include <ECS/CompontRegistry/ComponentRegistry.h>
#include <ImGuiClass/ImGuiClass.h>
#include "../ECS/Managers/Draw.h"
#include "ECS/Managers/TransformLogic/TransformLogic.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/WaveObject/WaveObjectFactory.h"
#include "ECS/Camera/Camera.h"
#include "ECS/WaveObject/WaveObject.h"
#include "MeshLogic/MeshLogic.h"

namespace WaveEngine
{
	WAVEEXPORT class BaseGame
	{
	private:

		void InitEngine(const int& width, const int& height);

		void EndEngine();

		void EngineUpdate();

		void EngineDraw();

		Renderer* GetRenderer();

		WaveObject* tank;

		DrawLogic drawLogic;
		TransformLogic transformLogic;
		MeshLogic meshLogic;

		ImGuiClass* imGui;

		WaveObject* cameraObject;
		Camera* camera;

	protected:

		WAVEEXPORT	virtual void Init(const int& width, const int& height) = 0;
		WAVEEXPORT	virtual void Unload() = 0;

		WAVEEXPORT float GetDeltaTime();

		WAVEEXPORT MaterialManager* GetMaterialManager();
		WAVEEXPORT MaterialFactory* GetMaterialFactory();
		WAVEEXPORT Input* GetInput();
		WAVEEXPORT Window* GetWindow();
		WAVEEXPORT Time* GetTime();
		WAVEEXPORT TextureImporter* GetTextureImporter();
		WAVEEXPORT TextureManager* GetTextureManager();
		WAVEEXPORT FileReader* GetFileReader();
		WAVEEXPORT EventSystem* GetEventSystem();
		WAVEEXPORT MeshFactory* GetMeshFactory();
		WAVEEXPORT MeshManager* GetMeshManager();
		WAVEEXPORT WaveObjectRegistry* GetWaveObjectRegistry();
		WAVEEXPORT WaveObjectFactory* GetWaveObjectFactory();

	public:

		WAVEEXPORT BaseGame(const int& width, const int& height);
		WAVEEXPORT virtual ~BaseGame();

		WAVEEXPORT	void Run();
	};
}

