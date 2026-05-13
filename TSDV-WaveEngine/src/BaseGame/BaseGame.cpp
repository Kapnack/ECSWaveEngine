#include "BaseGame.h"

#include "Input/Input.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialFactory.h"
#include "TextureImporter/TextureImporter.h"
#include "TextureImporter/TextureManager.h"
#include "ECS/Camera/Camera.h"
#include <ECS/Mesh/MeshID.h>
#include <ECS/MaterialID.h>
#include <ECS/Transform/ECSTransform.h>
#include <ModelImporter/ModelImporter.h>

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

		ServiceProvider::Instance().Register(new EventSystem());
		ServiceProvider::Instance().Register(new ComponentRegistry());
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
		imGui = new ImGuiClass();

		transformLogic.Init();
		drawLogic.Init();

		unsigned int textureIndex = GetTextureImporter()->LoadTextureAbsolutePath("Sprites/whiteImage.png");
		unsigned int MatID = GetMaterialFactory()->CreateMaterial("Test", GetFileReader()->ReadFile("Shaders/ECS/newShader.vert"), GetFileReader()->ReadFile("Shaders/ECS/newShader.frag"));

		unsigned int textureGPUID = GetTextureManager()->GetTexture(textureIndex)->GetGPUID();

		ModelImporter modelImporter;

		vector<unsigned int> models;

		models.push_back(modelImporter.LoadMesh("Models/Rata_mutante_low.fbx"));
		models.push_back(modelImporter.LoadMesh("Models/girl OBJ.obj"));
		models.push_back(modelImporter.LoadMesh("Models/gold_headed_buddha_-_photogrammetry_test_2019.glb"));
		models.push_back(modelImporter.LoadMesh("Models/Cube.fbx"));

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
			.position = { - 100, 0.0f, 0.0f },

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

		GetMaterialManager()->GetMaterial(MatID)->SetTexture("uTexture", textureGPUID);

		const unsigned int defaultSize = 32;

		GetComponentRegistry()->AddComponent<ECSTransform>(0);
		GetComponentRegistry()->AddComponent<Camera>(0);
		GetComponentRegistry()->GetComponentStorage<Camera>().Get(0).SetFarPlane(10000);
		GetComponentRegistry()->GetComponentStorage<Camera>().Get(0).SetOrthographic(false);
		GetComponentRegistry()->Get<ECSTransform>(0).SetPosition(Vector3::Right()* ((models.size() - 1)* defaultSize) + Vector3::Foward() * 150);

		for (unsigned int i = 1; i <= models.size() + 2; ++i)
		{
			GetComponentRegistry()->AddComponent<ECSTransform>(i);
			GetComponentRegistry()->AddComponent<MeshID>(i);
			GetComponentRegistry()->AddComponent<MeshRenderer>(i);

			GetComponentRegistry()->Get<ECSTransform>(i).SetPosition(Vector3::Right() * (i * defaultSize));

			GetComponentRegistry()->Get<MeshID>(i).meshID = i < models.size() ? models[i - 1] : models[models.size() - 1];

			GetComponentRegistry()->Get<MeshRenderer>(i).materialID = MatID;
		}

		GetComponentRegistry()->Get<ECSTransform>(1).Translate(Vector3::Up() * defaultSize);
		GetComponentRegistry()->Get<ECSTransform>(1).SetScale(Vector3::One() * defaultSize * 0.5f);

		GetComponentRegistry()->Get<ECSTransform>(2).SetScale(Vector3::One() * defaultSize);

		GetComponentRegistry()->Get<ECSTransform>(3).SetScale(Vector3::One() * defaultSize * 4);
		GetComponentRegistry()->Get<ECSTransform>(3).SetRotation(Vector3::Y() * (40 + 90));

		GetComponentRegistry()->Get<ECSTransform>(4).SetPosition(GetComponentRegistry()->Get<ECSTransform>(models.size() * 0.5f).GetPosition() + Vector3::Down() * defaultSize);
		GetComponentRegistry()->Get<ECSTransform>(4).SetScale((Vector3::Z() + Vector3::X()) * defaultSize * 10 + Vector3::Y());
		GetMeshManager()->GetMesh("Cube.fbx")->SetVertexColor(Color::White());

		GetComponentRegistry()->Get<ECSTransform>(models.size() + 1).SetPosition(Renderer::pointLight[0].position + Vector3::Back() * 25);
		GetComponentRegistry()->Get<ECSTransform>(models.size() + 1).SetScale((Vector3::Y() + Vector3::X()) * 10 + Vector3::Z());

		GetComponentRegistry()->Get<ECSTransform>(models.size() + 2).SetPosition(Renderer::pointLight[1].position + Vector3::Back() * 25);
		GetComponentRegistry()->Get<ECSTransform>(models.size() + 2).SetScale((Vector3::Y() + Vector3::X()) * 10 + Vector3::Z());

		GetComponentRegistry()->GetComponentStorage<ECSTransform>().Get(0).AddChild(1);
		GetComponentRegistry()->GetComponentStorage<ECSTransform>().Get(1).SetParent(0);
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

		Camera& camera = GetComponentRegistry()->Get<Camera>(0);
		ECSTransform& transform = GetComponentRegistry()->Get<ECSTransform>(0);
		const float camereSpeed = 300;

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

		if (GetInput()->IsKeyPressed(Keys::SPACE))
		{
			transform.Translate(Vector3::Foward() * GetDeltaTime() * camereSpeed);
		}
		else if (GetInput()->IsKeyPressed(Keys::LEFT_CONTROL))
		{
			transform.Translate(Vector3::Back() * GetDeltaTime() * camereSpeed);
		}

		transformLogic.Update();

		camera.CalculateMatrixes();

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

	ComponentRegistry* BaseGame::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
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
}