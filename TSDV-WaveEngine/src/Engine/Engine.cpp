#include "Engine.h"

#include <ctime>
#include <cstdlib>
#include <GLFW/glfw3.h>

#include "Time/Time.h"
#include "Input/Input.h"
#include "Window/Window.h"
#include "TestingBehaviour.h"
#include "Renderer/Renderer.h"
#include "WaveRandom/WaveRandom.h"
#include "FileReader/FileReader.h"
#include "EventSystem/EventSystem.h"
#include "Material/MaterialFactory.h"
#include "Material/MaterialManager.h"
#include "ModelImporter/ModelImporter.h"
#include "CameraManager/CameraManager.h"
#include "Mesh/MeshManager/MeshManager.h"
#include "Mesh/MeshFactory/MeshFactory.h"
#include "TextureImporter/TextureManager.h"
#include "ServiceProvider/ServiceProvider.h"
#include "TextureImporter/TextureImporter.h"
#include "ECS/WaveObject/WaveObjectFactory.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ECS/Managers/BinarySpacePartition/BinarySpacePartition.h"

namespace WaveEngine
{
	Engine::Engine(int width, int height)
	{
		InitEngine(width, height);
	}

	Engine::~Engine()
	{
		EndEngine();
	}

	void Engine::InitEngine(int width, int height)
	{
		if (!glfwInit())
			exit(-1);

#pragma region InitServices
		ServiceProvider::Instance().Register(new EventSystem());
		ServiceProvider::Instance().Register(new ComponentRegistry());
		ServiceProvider::Instance().Register(new WaveObjectRegistry());
		ServiceProvider::Instance().Register(new WaveObjectFactory());
		ServiceProvider::Instance().Register(new Window(width, height, "WaveEngine", nullptr, nullptr));
		ServiceProvider::Instance().Register(new FileReader());
		ServiceProvider::Instance().Register(new MeshFactory());
		ServiceProvider::Instance().Register(new MeshManager());
		ServiceProvider::Instance().Register(new MaterialManager());
		ServiceProvider::Instance().Register(new MaterialFactory());
		ServiceProvider::Instance().Register(new TextureManager());
		ServiceProvider::Instance().Register(new TextureImporter());
		ServiceProvider::Instance().Register(new Renderer());
		ServiceProvider::Instance().Register(new Input());
		ServiceProvider::Instance().Register(new Time());
		ServiceProvider::Instance().Register(new CameraManager());
		ServiceProvider::Instance().Register(new BinarySpacePartition());
		ServiceProvider::Instance().Register(new WaveRandom());
		ServiceProvider::Instance().Register(new ModelImporter());
#pragma endregion

		GetWaveRandom()->Init();
		GetWaveObjectRegistry()->Init();
		GetCameraManager()->Init();

		drawLogic.Init();
		drawLogic.Init();
		transformLogic.Init();

		imGui.Init();

		waveBehaviourLogic.Init();
		waveBehaviourLogic.LateInit();

		GetWaveObjectFactory()->Instantiate<TestingBehaviour>();

#pragma region InitLights
		Renderer::dirLight.direction = Vector3::Back();

		Renderer::flashLights[0] =
		{
			.position = { 96, 64.0f, 0.0f },
			.direction = Vector3::Down(),

			.ambient = Vector3::One() * 0.1f,
			.diffuse = Vector3::One(),
			.specular = Vector3::One(),

			.constant = 1.0f,
			.linear = 0.00032f,
			.quadratic = 0.00032f,

			.cutOff = 12.5f,
			.outerCutOff = 15.5f
		};

		Renderer::flashLights[1] =
		{
			.position = { 0.0f, 0.0f, 0.0f },
			.direction = Vector3::Down(),

			.ambient = Vector3::One() * 0.1f,
			.diffuse = Vector3::One(),
			.specular = Vector3::One(),

			.constant = 1.0f,
			.linear = 0.00032f,
			.quadratic = 0.00032f,

			.cutOff = 12.5f,
			.outerCutOff = 15.5f
		};

		Renderer::pointLight[0] =
		{
			.position = { -100, 0.0f, 0.0f },

			.ambient = Vector3::Y() * 0.1f,
			.diffuse = Vector3::Y(),
			.specular = Vector3::Y(),

			.constant = 1.0f,
			.linear = 0.00032f,
			.quadratic = 0.00032f
		};

		Renderer::pointLight[1] =
		{
			.position = { 200, 0.0f, 0.0f },

			.ambient = Vector3::X() * 0.1f,
			.diffuse = Vector3::X(),
			.specular = Vector3::X(),

			.constant = 1.0f,
			.linear = 0.00032f,
			.quadratic = 0.00032f
		};
#pragma endregion
	}

	void Engine::EndEngine()
	{
		waveBehaviourLogic.Destroy();
		imGui.Unload();
		ServiceProvider::Instance().Clear();
	}

	void Engine::Run()
	{
		while (!glfwWindowShouldClose(GetWindow()->GetGLFWindow()))
		{
			EngineUpdate();

			EngineDraw();

			GetWindow()->SwapBuffer();
			GetWindow()->HandleInput();
		}
	}

	void Engine::EngineUpdate()
	{
		GetTime()->UpdateDeltaTime();

		waveBehaviourLogic.Update();
		transformLogic.Update();

		GetBinarySpacePartition()->Update();

		GetCameraManager()->Update();

		meshLogic.Update();

		rigidBodyLogic.Update(GetDeltaTime());

		drawLogic.Update();

		imGui.Update();

		waveBehaviourLogic.LateUpdate();
	}

	void Engine::EngineDraw()
	{
		GetRenderer()->Clear();
		GetRenderer()->Flush();
		GetRenderer()->FlushDebug();
		imGui.Draw();
	}

	Time* Engine::GetTime() const
	{
		return ServiceProvider::Instance().Get<Time>();
	}

	Renderer* Engine::GetRenderer() const
	{
		return ServiceProvider::Instance().Get<Renderer>();
	}

	CameraManager* Engine::GetCameraManager() const
	{
		return ServiceProvider::Instance().Get<CameraManager>();
	}

	BinarySpacePartition* Engine::GetBinarySpacePartition() const
	{
		return ServiceProvider::Instance().Get<BinarySpacePartition>();
	}

	float Engine::GetDeltaTime() const
	{
		return GetTime()->GetDeltaTime();
	}

	Window* Engine::GetWindow() const
	{
		return ServiceProvider::Instance().Get<Window>();
	}

	MaterialManager* Engine::GetMaterialManager() const
	{
		return ServiceProvider::Instance().Get<MaterialManager>();
	}

	MaterialFactory* Engine::GetMaterialFactory() const
	{
		return ServiceProvider::Instance().Get<MaterialFactory>();
	}

	Input* Engine::GetInput() const
	{
		return ServiceProvider::Instance().Get<Input>();
	}

	TextureManager* Engine::GetTextureManager() const
	{
		return ServiceProvider::Instance().Get<TextureManager>();
	}

	TextureImporter* Engine::GetTextureImporter() const
	{
		return ServiceProvider::Instance().Get<TextureImporter>();
	}

	FileReader* Engine::GetFileReader() const
	{
		return ServiceProvider::Instance().Get<FileReader>();
	}

	EventSystem* Engine::GetEventSystem() const
	{
		return ServiceProvider::Instance().Get<EventSystem>();
	}

	MeshFactory* Engine::GetMeshFactory() const
	{
		return ServiceProvider::Instance().Get<MeshFactory>();
	}

	MeshManager* Engine::GetMeshManager() const
	{
		return ServiceProvider::Instance().Get<MeshManager>();
	}

	WaveObjectRegistry* Engine::GetWaveObjectRegistry() const
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
	}

	WaveObjectFactory* Engine::GetWaveObjectFactory() const
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>();
	}

	WaveRandom* Engine::GetWaveRandom() const
	{
		return ServiceProvider::Instance().Get<WaveRandom>();
	}
}