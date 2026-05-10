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


		GetComponentRegistry()->AddComponent<ECSTransform>(0);
		GetComponentRegistry()->AddComponent<Camera>(0);
		GetComponentRegistry()->GetComponentStorage<Camera>().Get(0).SetFarPlane(10000);
		GetComponentRegistry()->GetComponentStorage<Camera>().Get(0).SetOrthographic(false);
		GetComponentRegistry()->Get<ECSTransform>(0).SetPosition(0, 0, 1000);

		unsigned int textureIndex = GetTextureImporter()->LoadTextureAbsolutePath("Sprites/whiteImage.png");
		unsigned int MatID = GetMaterialFactory()->CreateMaterial("Test", GetFileReader()->ReadFile("Shaders/ECS/newShader.vert"), GetFileReader()->ReadFile("Shaders/ECS/newShader.frag"));


		unsigned int albedo = GetTextureManager()->GetTexture(textureIndex)->GetGPUID();

		unsigned int meshID = GetModelImporter()->LoadMesh("Rata", "C:\\Users\\Kapnack\\Downloads\\PlayerCharacter.fbx");

		GetMaterialManager()->GetMaterial(MatID)->SetTexture("uTexture", albedo);

		for (unsigned int i = 1; i <= 2; ++i)
		{
			GetComponentRegistry()->AddComponent<ECSTransform>(i);
			GetComponentRegistry()->AddComponent<MeshID>(i);
			GetComponentRegistry()->AddComponent<MeshRenderer>(i);

			GetComponentRegistry()->Get<ECSTransform>(i).SetPosition(rand() % 200 - 100, rand() % 200 - 100, rand() % 200 - 100);
			GetComponentRegistry()->Get<ECSTransform>(i).SetScale(100, 100, 100);

			GetComponentRegistry()->Get<MeshID>(i).meshID = meshID;
			GetComponentRegistry()->Get<MeshRenderer>(i).materialID = MatID;
		}
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

		auto& camera = GetComponentRegistry()->Get<Camera>(0);
		auto& transform = GetComponentRegistry()->Get<ECSTransform>(0);
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

		camera.CalculateMatrixes(transform.GetPosition(), transform.GetRotation());

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