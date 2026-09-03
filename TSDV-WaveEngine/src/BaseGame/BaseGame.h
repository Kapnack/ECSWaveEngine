#pragma once

#include "Export.h"
#include "Time/Time.h"
#include "Input/Input.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "MeshLogic/MeshLogic.h"
#include "FileReader/FileReader.h"
#include "ImGuiClass/ImGuiClass.h"
#include "ECS/Managers/DrawLogic.h"
#include "EventSystem/EventSystem.h"
#include "Material/MaterialManager.h"
#include "Material/MaterialFactory.h"
#include "ECS/WaveObject/WaveObject.h"
#include "CameraManager/CameraManager.h"
#include "Mesh/MeshFactory/MeshFactory.h"
#include "Mesh/MeshManager/MeshManager.h"
#include "ECS/RigidBody/RigidBodyLogic.h"
#include "TextureImporter/TextureManager.h"
#include "TextureImporter/TextureImporter.h"
#include "ECS/WaveObject/WaveObjectFactory.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/Managers/TransformLogic/TransformLogic.h"
#include "ECS/Managers/BinarySpacePartition/BinarySpacePartition.h"


namespace WaveEngine
{
	WAVEEXPORT class BaseGame
	{
	private:

		void InitEngine(int width, int height);

		void EndEngine();

		void EngineUpdate();

		void EngineDraw();

		WaveObject* tank;

		DrawLogic drawLogic;
		TransformLogic transformLogic;
		MeshLogic meshLogic;
		RigidBodyLogic rigidBodyLogic;

		ImGuiClass imGui;

		WaveObject* cameraObject;

	protected:

		WAVEEXPORT virtual void Init(int width, int height) = 0;
		WAVEEXPORT virtual void Unload() = 0;

		WAVEEXPORT float GetDeltaTime() const;

		WAVEEXPORT Renderer* GetRenderer() const;
		WAVEEXPORT BinarySpacePartition* GetBinarySpacePartition() const;
		WAVEEXPORT CameraManager* GetCameraManager() const;
		WAVEEXPORT MaterialManager* GetMaterialManager() const;
		WAVEEXPORT MaterialFactory* GetMaterialFactory() const;
		WAVEEXPORT Input* GetInput() const;
		WAVEEXPORT Window* GetWindow() const;
		WAVEEXPORT Time* GetTime() const;
		WAVEEXPORT TextureImporter* GetTextureImporter() const;
		WAVEEXPORT TextureManager* GetTextureManager() const;
		WAVEEXPORT FileReader* GetFileReader() const;
		WAVEEXPORT EventSystem* GetEventSystem() const;
		WAVEEXPORT MeshFactory* GetMeshFactory() const;
		WAVEEXPORT MeshManager* GetMeshManager() const;
		WAVEEXPORT WaveObjectRegistry* GetWaveObjectRegistry() const;
		WAVEEXPORT WaveObjectFactory* GetWaveObjectFactory() const;

	public:

		WAVEEXPORT BaseGame(int width, int height);
		WAVEEXPORT virtual ~BaseGame();

		WAVEEXPORT void Run();
	};
}

