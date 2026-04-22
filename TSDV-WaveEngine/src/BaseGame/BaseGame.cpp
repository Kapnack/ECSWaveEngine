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

		//Random::Init();

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

		transformLogic.Init();
		drawLogic.Init();

		imGui = new ImGuiClass();

		const unsigned int vertexSize = 24;

		VertexData* vertex = new VertexData[24]
		{
			VertexData(Vector3(-0.5f,-0.5f, 0.5f), Vector4(1,1,1,1), Vector2(0,0), Vector3(0,0,1)),
			VertexData(Vector3(0.5f,-0.5f, 0.5f), Vector4(1,1,1,1), Vector2(1,0), Vector3(0,0,1)),
			VertexData(Vector3(0.5f, 0.5f, 0.5f), Vector4(1,1,1,1), Vector2(1,1), Vector3(0,0,1)),
			VertexData(Vector3(-0.5f, 0.5f, 0.5f), Vector4(1,1,1,1), Vector2(0,1), Vector3(0,0,1)),

			VertexData(Vector3(0.5f,-0.5f,-0.5f), Vector4(1,1,1,1), Vector2(0,0), Vector3(0,0,-1)),
			VertexData(Vector3(-0.5f,-0.5f,-0.5f), Vector4(1,1,1,1), Vector2(1,0), Vector3(0,0,-1)),
			VertexData(Vector3(-0.5f, 0.5f,-0.5f), Vector4(1,1,1,1), Vector2(1,1), Vector3(0,0,-1)),
			VertexData(Vector3(0.5f, 0.5f,-0.5f), Vector4(1,1,1,1), Vector2(0,1), Vector3(0,0,-1)),

			VertexData(Vector3(-0.5f,-0.5f,-0.5f), Vector4(1,1,1,1), Vector2(0,0), Vector3(-1,0,0)),
			VertexData(Vector3(-0.5f,-0.5f, 0.5f), Vector4(1,1,1,1), Vector2(1,0), Vector3(-1,0,0)),
			VertexData(Vector3(-0.5f, 0.5f, 0.5f), Vector4(1,1,1,1), Vector2(1,1), Vector3(-1,0,0)),
			VertexData(Vector3(-0.5f, 0.5f,-0.5f), Vector4(1,1,1,1), Vector2(0,1), Vector3(-1,0,0)),

			VertexData(Vector3(0.5f,-0.5f, 0.5f), Vector4(1,1,1,1), Vector2(0,0), Vector3(1,0,0)),
			VertexData(Vector3(0.5f,-0.5f,-0.5f), Vector4(1,1,1,1), Vector2(1,0), Vector3(1,0,0)),
			VertexData(Vector3(0.5f, 0.5f,-0.5f), Vector4(1,1,1,1), Vector2(1,1), Vector3(1,0,0)),
			VertexData(Vector3(0.5f, 0.5f, 0.5f), Vector4(1,1,1,1), Vector2(0,1), Vector3(1,0,0)),

			VertexData(Vector3(-0.5f, 0.5f, 0.5f), Vector4(1,1,1,1), Vector2(0,0), Vector3(0,1,0)),
			VertexData(Vector3(0.5f, 0.5f, 0.5f), Vector4(1,1,1,1), Vector2(1,0), Vector3(0,1,0)),
			VertexData(Vector3(0.5f, 0.5f,-0.5f), Vector4(1,1,1,1), Vector2(1,1), Vector3(0,1,0)),
			VertexData(Vector3(-0.5f, 0.5f,-0.5f), Vector4(1,1,1,1), Vector2(0,1), Vector3(0,1,0)),

			VertexData(Vector3(-0.5f,-0.5f,-0.5f), Vector4(1,1,1,1), Vector2(0,0), Vector3(0,-1,0)),
			VertexData(Vector3(0.5f,-0.5f,-0.5f), Vector4(1,1,1,1), Vector2(1,0), Vector3(0,-1,0)),
			VertexData(Vector3(0.5f,-0.5f, 0.5f), Vector4(1,1,1,1), Vector2(1,1), Vector3(0,-1,0)),
			VertexData(Vector3(-0.5f,-0.5f, 0.5f), Vector4(1,1,1,1), Vector2(0,1), Vector3(0,-1,0))
		};

		const unsigned int indexSize = 36;
		unsigned int* indices = new unsigned[indexSize]
		{
			0,1,2, 2,3,0,        // front
			4,5,6, 6,7,4,        // back
			8,9,10, 10,11,8,     // left
			12,13,14, 14,15,12,  // right
			16,17,18, 18,19,16,  // top
			20,21,22, 22,23,20   // bottom
		};

		GetComponentRegistry()->AddComponent<ECSTransform>(0);
		GetComponentRegistry()->AddComponent<Camera>(0);
		GetComponentRegistry()->GetComponentStorage<Camera>().Get(0).SetFarPlane(10000);
		GetComponentRegistry()->GetComponentStorage<Camera>().Get(0).SetOrthographic(false);

		GetComponentRegistry()->Get<ECSTransform>(0).SetPosition(0, 0, 1000);

		int MatID = GetMaterialFactory()->CreateMaterial("Test", GetFileReader()->ReadFile("Shaders/ECS/newShader.vert"), GetFileReader()->ReadFile("Shaders/ECS/newShader.frag"));

		unsigned int textureIndex = GetTextureImporter()->LoadTextureAbsolutePath("Sprites/battlecity_general.png");
		unsigned int albedo = GetTextureManager()->GetTexture(textureIndex)->GetTextureID();

		unsigned int meshID = GetMeshFactory()->CreateMesh("Square", vertex, vertexSize, indices, indexSize);

		GetMaterialManager()->GetMaterial(MatID)->SetTexture("uAlbedo", albedo);

		for (int i = 1; i <= 5000; ++i)
		{
			GetComponentRegistry()->AddComponent<ECSTransform>(i);
			GetComponentRegistry()->AddComponent<MeshID>(i);
			GetComponentRegistry()->AddComponent<MeshRenderer>(i);

			GetComponentRegistry()->Get<ECSTransform>(i).SetScale(32, 32, 32);

			GetComponentRegistry()->Get<MeshID>(i).meshID = meshID;
			GetComponentRegistry()->Get<MeshRenderer>(i).materialID = MatID;
		}

		//GetComponentRegistry()->GetComponent<ECSTransform>(3).SetParent(1);
		//GetComponentRegistry()->GetComponent<ECSTransform>(1).AddChild(3);
		//
		//GetComponentRegistry()->GetComponent<ECSTransform>(3).SetPosition(10,0,0);
		//GetComponentRegistry()->GetComponent<ECSTransform>(3).SetScale(1,1,1);
		//

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

		auto& transformEntity = GetComponentRegistry()->Get<ECSTransform>(1);

		if (GetInput()->IsKeyPressed(Keys::UP))
		{
			transformEntity.Translate(Vector3::Up() * GetDeltaTime() * 100);
		}
		else if (GetInput()->IsKeyPressed(Keys::LEFT))
		{
			transformEntity.Translate(Vector3::Left() * GetDeltaTime() * 100);
		}
		else if (GetInput()->IsKeyPressed(Keys::DOWN))
		{
			transformEntity.Translate(Vector3::Down() * GetDeltaTime() * 100);
		}
		else if (GetInput()->IsKeyPressed(Keys::RIGHT))
		{
			transformEntity.Translate(Vector3::Right() * GetDeltaTime() * 100);
		}

		auto& camera = GetComponentRegistry()->Get<Camera>(0);
		auto& transform = GetComponentRegistry()->Get<ECSTransform>(0);

		if (GetInput()->IsKeyPressed(Keys::W))
		{
			transform.Translate(Vector3::Up() * GetDeltaTime() * 100);
		}
		else if (GetInput()->IsKeyPressed(Keys::A))
		{
			transform.Translate(Vector3::Left() * GetDeltaTime() * 100);
		}
		else if (GetInput()->IsKeyPressed(Keys::S))
		{
			transform.Translate(Vector3::Down() * GetDeltaTime() * 100);
		}
		else if (GetInput()->IsKeyPressed(Keys::D))
		{
			transform.Translate(Vector3::Right() * GetDeltaTime() * 100);
		}

		if (GetInput()->IsKeyPressed(Keys::Z))
		{
			transform.Rotate(Vector3::Left() * GetDeltaTime() * 100);
		}
		else if (GetInput()->IsKeyPressed(Keys::X))
		{
			transform.Rotate(Vector3::Right() * GetDeltaTime() * 100);
		}

		if (GetInput()->IsKeyPressed(Keys::SPACE))
		{
			transform.Translate(Vector3::Foward() * GetDeltaTime() * 100);
		}
		else if (GetInput()->IsKeyPressed(Keys::LEFT_CONTROL))
		{
			transform.Translate(Vector3::Back() * GetDeltaTime() * 100);
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