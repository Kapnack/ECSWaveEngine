#pragma once

#include "Export.h"
#include "Time/Time.h"
#include "WaveManager.h"
#include "Input/Input.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "MeshLogic/MeshLogic.h"
#include "FileReader/FileReader.h"
#include "WaveRandom/WaveRandom.h"
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
#include "ECS/Managers/WaveBehaviourLogic/WaveBehaviourLogic.h"
#include "ECS/Managers/BinarySpacePartition/BinarySpacePartition.h"


namespace WaveEngine
{
	class WAVEEXPORT Engine
	{
	private:

		Engine(WaveManager* waveManager);
		virtual ~Engine();

		void Run();

		void Init();

		void LateInit();

		void Dispose();

		void Update();

		void Draw();

		WaveManager* waveManager;

		WaveObject* tank;

		DrawLogic drawLogic;
		TransformLogic transformLogic;
		MeshLogic meshLogic;
		RigidBodyLogic rigidBodyLogic;
		WaveBehaviourLogic waveBehaviourLogic;

		ImGuiClass imGui;

		WaveObject* cameraObject;

	protected:

		float GetDeltaTime() const;

		Renderer* GetRenderer() const;
		BinarySpacePartition* GetBinarySpacePartition() const;
		CameraManager* GetCameraManager() const;
		MaterialManager* GetMaterialManager() const;
		MaterialFactory* GetMaterialFactory() const;
		Input* GetInput() const;
		Time* GetTime() const;
		TextureManager* GetTextureManager() const;
		FileReader* GetFileReader() const;
		EventSystem* GetEventSystem() const;
		MeshFactory* GetMeshFactory() const;
		MeshManager* GetMeshManager() const;
		WaveObjectRegistry* GetWaveObjectRegistry() const;
		WaveObjectFactory* GetWaveObjectFactory() const;
		WaveRandom* GetWaveRandom() const;

	public:

		static bool isRunning;

		template<typename T>
		static void StartEngine();

		static Window* GetWindow();
		static TextureImporter* GetTextureImporter();
	};
}

#include "Engine.tpp"