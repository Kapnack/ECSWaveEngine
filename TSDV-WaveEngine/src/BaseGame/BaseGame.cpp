#include "BaseGame.h"

#include <ctime>
#include <cstdlib>

#include "Time/Time.h"
#include "Input/Input.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "ECS/Camera/Camera.h"
#include "FileReader/FileReader.h"
#include "EventSystem/EventSystem.h"
#include "Material/MaterialFactory.h"
#include "Material/MaterialManager.h"
#include "ECS/Transform/ECSTransform.h"
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
	BaseGame::BaseGame(int width, int height)
	{
		InitEngine(width, height);
	}

	BaseGame::~BaseGame()
	{
		EndEngine();
	}

	void BaseGame::InitEngine(int width, int height)
	{
		if (!glfwInit())
			exit(-1);

		srand(time(NULL));

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
#pragma endregion

		GetWaveObjectRegistry()->Init();
		GetCameraManager()->Init();

		drawLogic.Init();
		drawLogic.Init();
		transformLogic.Init();

		imGui.Init();

#pragma region ImportModels

		const vector<string> modelsPaths
		{
			"Models/Tank.fbx",
			"Models/Cube.fbx"
		};

		const unsigned int defaultSize = 32;

		ModelImporter modelImporter;

		modelImporter.LoadScene(modelsPaths.at(0));
		tank = modelImporter.IntantiateModel();

		tank->GetTransform().SetPosition(Vector3::Right() * (defaultSize * 0.5f));
		tank->GetTransform().SetScale(Vector3::One() * defaultSize);

		cameraObject = &GetWaveObjectFactory()->Instantiate();
		Camera& camera = cameraObject->AddComponent<Camera>();
		camera.SetFarPlane(1000000.0f);
		camera.SetNearPlane(0.1f);
		camera.SetOrthographic(false);
		cameraObject->GetTransform().SetPosition(Vector3::Right() * (modelsPaths.size() * 0.5f * defaultSize) + Vector3::Foward() * 300);

		modelImporter.LoadScene(modelsPaths.at(modelsPaths.size() - 1));

		WaveObject* waveObject = modelImporter.IntantiateModel();

		waveObject->GetTransform().SetPosition(Vector3::Down() * 150.000f);
		waveObject->GetTransform().Scale((Vector3::X() + Vector3::Z()) * 100.0f);

		waveObject = modelImporter.IntantiateModel();

		waveObject->GetTransform().SetPosition((camera.GetTransform().GetPosition() + tank->GetTransform().GetPosition()) * 0.5f);
		waveObject->GetTransform().SetScale(Vector3::One() * 0.2f);

		for (WaveObject* binaryObj : GetWaveObjectRegistry()->GetWaveObject("Tank", ObjectNameSearch::Contains))
			GetBinarySpacePartition()->TurnObjectIntoPlane(*binaryObj);

#pragma endregion

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

	void BaseGame::EndEngine()
	{
		imGui.Unload();
		ServiceProvider::Instance().Clear();
	}

	void BaseGame::Run()
	{
		while (!glfwWindowShouldClose(GetWindow()->GetGLFWindow()))
		{
			EngineUpdate();

			EngineDraw();

			GetWindow()->SwapBuffer();
			GetWindow()->HandleInput();
		}
	}

	void BaseGame::EngineUpdate()
	{
		GetTime()->UpdateDeltaTime();

#pragma region UpdateCameraPositionLogic
		const float camereSpeed = 180.0f * GetDeltaTime();
		ECSTransform& transform = tank->GetTransform();
		ECSTransform& cameraTransform = cameraObject->GetTransform();

		if (!ImGuiClass::thirdPersonCamera)
		{
			if (GetInput()->IsKeyPressed(Keys::W))
				cameraTransform.Translate(cameraTransform.GetForward() * camereSpeed);

			if (GetInput()->IsKeyPressed(Keys::S))
				cameraTransform.Translate(-cameraTransform.GetForward() * camereSpeed);

			if (GetInput()->IsKeyPressed(Keys::A))
				cameraTransform.Translate(-cameraTransform.GetRight() * camereSpeed);

			if (GetInput()->IsKeyPressed(Keys::D))
				cameraTransform.Translate(cameraTransform.GetRight() * camereSpeed);

			if (GetInput()->IsKeyPressed(Keys::SPACE))
				cameraTransform.Translate(Vector3::Up() * camereSpeed);

			if (GetInput()->IsKeyPressed(Keys::LEFT_CONTROL))
				cameraTransform.Translate(Vector3::Down() * camereSpeed);

			if (GetInput()->IsKeyPressed(Keys::Q))
				cameraTransform.Rotate(Vector3::Up() * camereSpeed);

			if (GetInput()->IsKeyPressed(Keys::E))
				cameraTransform.Rotate(Vector3::Down() * camereSpeed);

			if (GetInput()->IsKeyPressed(Keys::Z))
				cameraTransform.Rotate(Vector3::Left() * camereSpeed);

			if (GetInput()->IsKeyPressed(Keys::X))
				cameraTransform.Rotate(Vector3::Right() * camereSpeed);
		}
		else
		{
			if (GetInput()->IsKeyPressed(Keys::W))
			{
				transform.Rotate(Vector3::Up() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::A))
			{
				transform.Rotate(Vector3::Left() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::S))
			{
				transform.Rotate(Vector3::Down() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::D))
			{
				transform.Rotate(Vector3::Right() * camereSpeed);
			}

			if (GetInput()->IsKeyPressed(Keys::UP))
			{
				transform.Scale(Vector3::Up() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::LEFT))
			{
				transform.Scale(Vector3::Left() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::DOWN))
			{
				transform.Scale(Vector3::Down() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::RIGHT))
			{
				transform.Scale(Vector3::Right() * camereSpeed);
			}

			if (GetInput()->IsKeyPressed(Keys::Z))
			{
				transform.Rotate(Vector3::Left() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::X))
			{
				transform.Rotate(Vector3::Right() * camereSpeed);
			}

			if (GetInput()->IsKeyPressed(Keys::Q))
			{
				transform.Rotate(Vector3::Up() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::E))
			{
				transform.Rotate(Vector3::Down() * camereSpeed);
			}

			if (GetInput()->IsKeyPressed(Keys::SPACE))
			{
				transform.Translate(Vector3::Foward() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::LEFT_CONTROL))
			{
				transform.Translate(Vector3::Back() * camereSpeed);
			}

			ECSTransform& childsTransform = transform.GetChild(0).GetTransform().GetChild(0).GetTransform().GetChild(0).GetTransform();
			const int dived = 2;
			if (GetInput()->IsKeyPressed(Keys::I))
			{
				childsTransform.Rotate(Vector3::Up() / dived);
			}
			else if (GetInput()->IsKeyPressed(Keys::J))
			{
				childsTransform.Rotate(Vector3::Left() / dived);
			}
			else if (GetInput()->IsKeyPressed(Keys::K))
			{
				childsTransform.Rotate(Vector3::Down() / dived);
			}
			else if (GetInput()->IsKeyPressed(Keys::L))
			{
				childsTransform.Rotate(Vector3::Right() / dived);
			}

			if (GetInput()->IsKeyPressed(Keys::T))
			{
				childsTransform.Scale(Vector3::Up() / dived);
			}
			else if (GetInput()->IsKeyPressed(Keys::F))
			{
				childsTransform.Scale(Vector3::Left() / dived);
			}
			else if (GetInput()->IsKeyPressed(Keys::G))
			{
				childsTransform.Scale(Vector3::Down() / dived);
			}
			else if (GetInput()->IsKeyPressed(Keys::H))
			{
				childsTransform.Scale(Vector3::Right() / dived);
			}

			cameraObject->GetTransform().LookAt(transform.GetPosition());
		}
#pragma endregion

		transformLogic.Update();

		GetBinarySpacePartition()->Update();

		GetCameraManager()->Update();

		meshLogic.Update();

		rigidBodyLogic.Update(GetDeltaTime());

		drawLogic.Update();

		imGui.Update();
	}

	void BaseGame::EngineDraw()
	{
		GetRenderer()->Clear();
		GetRenderer()->Flush();
		GetRenderer()->FlushDebug();
		imGui.Draw();
	}

	Time* BaseGame::GetTime() const
	{
		return ServiceProvider::Instance().Get<Time>();
	}

	Renderer* BaseGame::GetRenderer() const
	{
		return ServiceProvider::Instance().Get<Renderer>();
	}

	CameraManager* BaseGame::GetCameraManager() const
	{
		return ServiceProvider::Instance().Get<CameraManager>();
	}

	BinarySpacePartition* BaseGame::GetBinarySpacePartition() const
	{
		return ServiceProvider::Instance().Get<BinarySpacePartition>();
	}

	float BaseGame::GetDeltaTime() const
	{
		return GetTime()->GetDeltaTime();
	}

	Window* BaseGame::GetWindow() const
	{
		return ServiceProvider::Instance().Get<Window>();
	}

	MaterialManager* BaseGame::GetMaterialManager() const
	{
		return ServiceProvider::Instance().Get<MaterialManager>();
	}

	MaterialFactory* BaseGame::GetMaterialFactory() const
	{
		return ServiceProvider::Instance().Get<MaterialFactory>();
	}

	Input* BaseGame::GetInput() const
	{
		return ServiceProvider::Instance().Get<Input>();
	}

	TextureManager* BaseGame::GetTextureManager() const
	{
		return ServiceProvider::Instance().Get<TextureManager>();
	}

	TextureImporter* BaseGame::GetTextureImporter() const
	{
		return ServiceProvider::Instance().Get<TextureImporter>();
	}

	FileReader* BaseGame::GetFileReader() const
	{
		return ServiceProvider::Instance().Get<FileReader>();
	}

	EventSystem* BaseGame::GetEventSystem() const
	{
		return ServiceProvider::Instance().Get<EventSystem>();
	}

	MeshFactory* BaseGame::GetMeshFactory() const
	{
		return ServiceProvider::Instance().Get<MeshFactory>();
	}

	MeshManager* BaseGame::GetMeshManager() const
	{
		return ServiceProvider::Instance().Get<MeshManager>();
	}

	WaveObjectRegistry* BaseGame::GetWaveObjectRegistry() const
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
	}

	WaveObjectFactory* BaseGame::GetWaveObjectFactory() const
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>();
	}
}