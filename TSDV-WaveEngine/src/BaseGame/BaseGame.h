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

		DrawLogic drawLogic;
		TransformLogic transformLogic;

		ImGuiClass* imGui;

	protected:

		WAVEEXPORT	virtual void Init(const int& width, const int& height) = 0;
		WAVEEXPORT	virtual void Unload() = 0;

		WAVEEXPORT float GetDeltaTime();

		WAVEEXPORT MaterialManager* GetMaterialManager();
		WAVEEXPORT ComponentRegistry* GetComponentRegistry();
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

	public:

		WAVEEXPORT BaseGame(const int& width, const int& height);
		WAVEEXPORT virtual ~BaseGame();

		WAVEEXPORT	void Run();
	};
}

