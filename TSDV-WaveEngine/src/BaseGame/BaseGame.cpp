#include "BaseGame.h"

#include "Input/Input.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialFactory.h"
#include "TextureImporter/TextureImporter.h"
#include "TextureImporter/TextureManager.h"
#include "ECS/Camera/Camera.h"
#include "ECS/Mesh/MeshID.h"
#include "ECS/MaterialID.h"
#include "ECS/Transform/ECSTransform.h"
#include "ModelImporter/ModelImporter.h"

namespace WaveEngine
{
	BaseGame::BaseGame(const int& width, const int& height)
	{
		InitEngine(width, height);
	}

	BaseGame::~BaseGame()
	{
		EndEngine();
	}

	void BaseGame::InitEngine(const int& width, const int& height)
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
#pragma endregion

		imGui = new ImGuiClass();

		transformLogic.Init();
		drawLogic.Init();

#pragma region ImportModels

		const vector<string> modelsPaths
		{
			"Models/Cat/concrete_cat_statue_1k.fbx",
			"Models/gold_headed_buddha_-_photogrammetry_test_2019.glb",
			"Models/Statue/marble_bust_01_1k.fbx"
		};

		const unsigned int defaultSize = 32;

		ModelImporter modelImporter;
		for (int i = 0; i < modelsPaths.size(); ++i)
		{
			modelImporter.LoadScene(modelsPaths.at(i));

			WaveObject& waveObject = *modelImporter.IntantiateModel();

			waveObject.GetTransform().SetPosition(Vector3::Right() * (defaultSize * 0.5f * i));
			waveObject.GetTransform().SetScale(Vector3::One() * defaultSize);

			if (i != 1)
				waveObject.GetTransform().Rotate(Vector3::Left() * 90);
			else
				waveObject.GetTransform().Rotate(Vector3::Up() * (45 + 90));
		}

		cameraObject = &GetWaveObjectFactory()->Instantiate();

		camera = &cameraObject->AddComponent<Camera>();
		camera->SetFarPlane(10000);
		camera->SetOrthographic(false);
		cameraObject->GetTransform().SetPosition(Vector3::Right() * (modelsPaths.size() * 0.5f * defaultSize) + Vector3::Foward() * 150);

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
		delete imGui;
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
		const float camereSpeed = 80.0f;
		ECSTransform& transform = GetWaveObjectRegistry()->GetWaveObject(1).GetTransform();

		if (!ImGuiClass::thirdPersonCamera)
		{
			cameraObject->GetTransform().SetParent(-1);
			transform.RemoveChild(cameraObject->GetID());

			if (GetInput()->IsKeyPressed(Keys::W))
			{
				cameraObject->GetTransform().Translate(Vector3::Up() * GetDeltaTime() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::A))
			{
				cameraObject->GetTransform().Translate(Vector3::Left() * GetDeltaTime() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::S))
			{
				cameraObject->GetTransform().Translate(Vector3::Down() * GetDeltaTime() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::D))
			{
				cameraObject->GetTransform().Translate(Vector3::Right() * GetDeltaTime() * camereSpeed);
			}

			if (GetInput()->IsKeyPressed(Keys::Z))
			{
				cameraObject->GetTransform().Rotate(Vector3::Left() * GetDeltaTime() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::X))
			{
				cameraObject->GetTransform().Rotate(Vector3::Right() * GetDeltaTime() * camereSpeed);
			}

			if (GetInput()->IsKeyPressed(Keys::Q))
			{
				cameraObject->GetTransform().Rotate(Vector3::Up() * GetDeltaTime() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::E))
			{
				cameraObject->GetTransform().Rotate(Vector3::Down() * GetDeltaTime() * camereSpeed);
			}

			if (GetInput()->IsKeyPressed(Keys::SPACE))
			{
				cameraObject->GetTransform().Translate(Vector3::Foward() * GetDeltaTime() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::LEFT_CONTROL))
			{
				cameraObject->GetTransform().Translate(Vector3::Back() * GetDeltaTime() * camereSpeed);
			}
		}
		else
		{
			cameraObject->GetTransform().SetParent(1);
			transform.AddChild(cameraObject->GetID());

			if (GetInput()->IsKeyPressed(Keys::W))
			{
				transform.Translate(Vector3::Up() * GetDeltaTime() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::A))
			{
				transform.Translate(Vector3::Left() * GetDeltaTime() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::S))
			{
				transform.Translate(Vector3::Down() * GetDeltaTime() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::D))
			{
				transform.Translate(Vector3::Right() * GetDeltaTime() * camereSpeed);
			}

			if (GetInput()->IsKeyPressed(Keys::Z))
			{
				transform.Rotate(Vector3::Left() * GetDeltaTime() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::X))
			{
				transform.Rotate(Vector3::Right() * GetDeltaTime() * camereSpeed);
			}

			if (GetInput()->IsKeyPressed(Keys::Q))
			{
				transform.Rotate(Vector3::Up() * GetDeltaTime() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::E))
			{
				transform.Rotate(Vector3::Down() * GetDeltaTime() * camereSpeed);
			}

			if (GetInput()->IsKeyPressed(Keys::SPACE))
			{
				transform.Translate(Vector3::Foward() * GetDeltaTime() * camereSpeed);
			}
			else if (GetInput()->IsKeyPressed(Keys::LEFT_CONTROL))
			{
				transform.Translate(Vector3::Back() * GetDeltaTime() * camereSpeed);
			}
		}
#pragma endregion

		transformLogic.Update();

		camera->CalculateMatrixes();

		drawLogic.Update();

		imGui->Update();
	}

	void BaseGame::EngineDraw()
	{
		GetRenderer()->Clear();
		GetRenderer()->Flush();
		imGui->Draw();
	}

	Time* BaseGame::GetTime()
	{
		return ServiceProvider::Instance().Get<Time>();
	}

	Renderer* BaseGame::GetRenderer()
	{
		return ServiceProvider::Instance().Get<Renderer>();
	}

	float BaseGame::GetDeltaTime()
	{
		return GetTime()->GetDeltaTime();
	}

	Window* BaseGame::GetWindow()
	{
		return ServiceProvider::Instance().Get<Window>();
	}

	MaterialManager* BaseGame::GetMaterialManager()
	{
		return ServiceProvider::Instance().Get<MaterialManager>();
	}

	MaterialFactory* BaseGame::GetMaterialFactory()
	{
		return ServiceProvider::Instance().Get<MaterialFactory>();
	}

	Input* BaseGame::GetInput()
	{
		return ServiceProvider::Instance().Get<Input>();
	}

	TextureManager* BaseGame::GetTextureManager()
	{
		return ServiceProvider::Instance().Get<TextureManager>();
	}

	TextureImporter* BaseGame::GetTextureImporter()
	{
		return ServiceProvider::Instance().Get<TextureImporter>();
	}

	FileReader* BaseGame::GetFileReader()
	{
		return ServiceProvider::Instance().Get<FileReader>();
	}

	EventSystem* BaseGame::GetEventSystem()
	{
		return ServiceProvider::Instance().Get<EventSystem>();
	}

	MeshFactory* BaseGame::GetMeshFactory()
	{
		return ServiceProvider::Instance().Get<MeshFactory>();
	}

	MeshManager* BaseGame::GetMeshManager()
	{
		return ServiceProvider::Instance().Get<MeshManager>();
	}

	WaveObjectRegistry* BaseGame::GetWaveObjectRegistry()
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
	}

	WaveObjectFactory* BaseGame::GetWaveObjectFactory()
	{
		return ServiceProvider::Instance().Get<WaveObjectFactory>();
	}
}