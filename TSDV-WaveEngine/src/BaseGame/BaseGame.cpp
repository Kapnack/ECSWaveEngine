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
		ModelImporter modelImporter;
		vector<unsigned int> models;
		vector<unsigned int> materialPerModel;

		modelImporter.LoadScene("Models/Rata_mutante_low.fbx");
		models.push_back(modelImporter.LoadMesh());
		materialPerModel.push_back(modelImporter.LoadMaterial());

		modelImporter.LoadScene("Models/girl OBJ.obj");
		models.push_back(modelImporter.LoadMesh());
		materialPerModel.push_back(modelImporter.LoadMaterial());

		modelImporter.LoadScene("Models/gold_headed_buddha_-_photogrammetry_test_2019.glb");
		models.push_back(modelImporter.LoadMesh());
		materialPerModel.push_back(modelImporter.LoadMaterial());

		modelImporter.LoadScene("Models/Cube.fbx");
		models.push_back(modelImporter.LoadMesh());
		materialPerModel.push_back(modelImporter.LoadMaterial());

		modelImporter.LoadScene("Models/LowPoly_SpiderBot_Rzenn.fbx");
		models.push_back(modelImporter.LoadMesh());
		materialPerModel.push_back(modelImporter.LoadMaterial());
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

#pragma region CreateMaterial
		unsigned int textureIndex = GetTextureImporter()->LoadTextureAbsolutePath("Sprites/whiteImage.png");
		unsigned int MatID = GetMaterialFactory()->CreateMaterial("Test", GetFileReader()->ReadFile("Shaders/ECS/newShader.vert"), GetFileReader()->ReadFile("Shaders/ECS/newShader.frag"));

		unsigned int textureGPUID = GetTextureManager()->GetTexture(textureIndex)->GetGPUID();

		GetMaterialManager()->GetMaterial(MatID)->SetTexture("uTexture[0]", textureGPUID);
#pragma endregion

#pragma region SetUpEntitiesAndComponents
		const unsigned int defaultSize = 32;

		cameraObject = &GetWaveObjectFactory()->Instantiate();

		camera = &cameraObject->AddComponent<Camera>();
		camera->SetFarPlane(10000);
		camera->SetOrthographic(false);
		cameraObject->GetTransform().SetPosition(Vector3::Right() * ((models.size() - 1) * defaultSize) + Vector3::Foward() * 150);

		vector<WaveObject*> waveObject;

		for (unsigned int i = 1; i <= models.size() + 2; ++i)
		{
			waveObject.push_back(&GetWaveObjectFactory()->Instantiate());

			MeshRenderer& meshRenderer = waveObject[i - 1]->AddComponent<MeshRenderer>();

			waveObject[i - 1]->GetTransform().SetPosition(Vector3::Right() * (i * defaultSize));

			waveObject[i - 1]->AddComponent<MeshID>().meshID = i < models.size() ? models[i - 1] : models[models.size() - 1];

			if (i - 1 < models.size())
				meshRenderer.materialID = materialPerModel[i - 1] == Material::NULL_MATERIAL ? MatID : materialPerModel[i - 1];
		}

		waveObject[0]->GetTransform().Translate(Vector3::Up() * defaultSize);
		waveObject[0]->GetTransform().SetScale(Vector3::One() * defaultSize * 0.5f);

		waveObject[1]->GetTransform().SetScale(Vector3::One() * defaultSize);

		waveObject[2]->GetTransform().SetScale(Vector3::One() * defaultSize * 4);
		waveObject[2]->GetTransform().SetRotation(Vector3::Y() * (40 + 90));

		waveObject[3]->GetTransform().SetPosition(waveObject[models.size() * 0.5f]->GetTransform().GetPosition() + Vector3::Down() * defaultSize);
		waveObject[3]->GetTransform().SetScale((Vector3::Z() + Vector3::X()) * defaultSize * 10 + Vector3::Y());
		GetMeshManager()->GetMesh("Cube.fbx")->SetVertexColor(Color::White());

		waveObject[models.size()]->GetTransform().SetPosition(Renderer::pointLight[0].position + Vector3::Back() * 25);
		waveObject[models.size()]->GetTransform().SetScale((Vector3::Y() + Vector3::X()) * 10 + Vector3::Z());

		waveObject[models.size() + 1]->GetTransform().SetPosition(Renderer::pointLight[1].position + Vector3::Back() * 25);
		waveObject[models.size() + 1]->GetTransform().SetScale((Vector3::Y() + Vector3::X()) * 10 + Vector3::Z());
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
		const float camereSpeed = 150;

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