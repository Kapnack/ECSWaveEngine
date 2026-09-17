#pragma once

#include "Time/Time.h"
#include "ImGuiClass/ImGuiClass.h"
#include "WaveMath/Vector3/Vector3.h"
#include "ECS/WaveObject/WaveObject.h"
#include "ECS/WaveBehaviour/WaveBehaviour.h"
#include <ModelImporter/ModelImporter.h>
#include <ECS/Camera/Camera.h>
#include <ECS/WaveObject/WaveObjectRegistry.h>
#include <ECS/Managers/BinarySpacePartition/BinarySpacePartition.h>
#include <string>
#include <vector>
#include <ECS/Transform/ECSTransform.h>
#include <Input/Input.h>

namespace WaveEngine
{
	class TestingBehaviour : public WaveBehaviour
	{
		WaveObject* tank = nullptr;

	public:

		TestingBehaviour(unsigned int ID) : WaveBehaviour(ID)
		{

		}

		void Init() override
		{
			const vector<string> modelsPaths
			{
				"Models/Tank.fbx",
				"Models/Binary/TestSpacePartition.fbx",
				"Models/Cube.fbx"
			};

			const unsigned int defaultSize = 32;

			ModelImporter modelImporter;
			
			modelImporter.LoadScene(modelsPaths[0]);

			tank = modelImporter.IntantiateModel();

			tank->GetTransform().SetPosition(Vector3::Right() * (defaultSize * 0.5f));
			tank->GetTransform().SetScale(Vector3::One() * defaultSize);

			Camera& camera = GetWaveObject().AddComponent<Camera>();
			camera.SetFarPlane(1000000.0f);
			camera.SetNearPlane(0.1f);
			camera.SetOrthographic(false);
			GetTransform().SetPosition(Vector3::Zero());

			modelImporter.LoadScene(modelsPaths.at(1));

			WaveObject& waveObject = *modelImporter.IntantiateModel();
			waveObject.GetTransform().SetScale(Vector3::One() * 0.1f);

			for (WaveObject* obj : WaveObjectRegistry::Get().GetWaveObject("Binary", ObjectNameSearch::Contains))
				BinarySpacePartition::Get().TurnObjectIntoPlane(obj->GetID());
		}

		void Update() override
		{
			const float camereSpeed = 180.0f * Time::Get().GetDeltaTime();
			ECSTransform& transform = tank->GetTransform();

			if (!ImGuiClass::thirdPersonCamera)
			{
				if (Input::Get().IsKeyPressed(Keys::W))
					GetTransform().Translate(GetTransform().GetForward() * camereSpeed);

				if (Input::Get().IsKeyPressed(Keys::S))
					GetTransform().Translate(GetTransform().GetBack() * camereSpeed);

				if (Input::Get().IsKeyPressed(Keys::A))
					GetTransform().Translate(GetTransform().GetLeft() * camereSpeed);

				if (Input::Get().IsKeyPressed(Keys::D))
					GetTransform().Translate(GetTransform().GetRight() * camereSpeed);

				if (Input::Get().IsKeyPressed(Keys::SPACE))
					GetTransform().Translate(Vector3::Up() * camereSpeed);

				if (Input::Get().IsKeyPressed(Keys::LEFT_CONTROL))
					GetTransform().Translate(Vector3::Down() * camereSpeed);

				if (Input::Get().IsKeyPressed(Keys::Q))
					GetTransform().Rotate(Vector3::Up() * camereSpeed);

				if (Input::Get().IsKeyPressed(Keys::E))
					GetTransform().Rotate(Vector3::Down() * camereSpeed);

				if (Input::Get().IsKeyPressed(Keys::Z))
					GetTransform().Rotate(Vector3::Left() * camereSpeed);

				if (Input::Get().IsKeyPressed(Keys::X))
					GetTransform().Rotate(Vector3::Right() * camereSpeed);
			}
			else
			{
				if (Input::Get().IsKeyPressed(Keys::W))
				{
					transform.Rotate(Vector3::Up() * camereSpeed);
				}
				else if (Input::Get().IsKeyPressed(Keys::A))
				{
					transform.Rotate(Vector3::Left() * camereSpeed);
				}
				else if (Input::Get().IsKeyPressed(Keys::S))
				{
					transform.Rotate(Vector3::Down() * camereSpeed);
				}
				else if (Input::Get().IsKeyPressed(Keys::D))
				{
					transform.Rotate(Vector3::Right() * camereSpeed);
				}

				if (Input::Get().IsKeyPressed(Keys::UP))
				{
					transform.Scale(Vector3::Up() * camereSpeed);
				}
				else if (Input::Get().IsKeyPressed(Keys::LEFT))
				{
					transform.Scale(Vector3::Left() * camereSpeed);
				}
				else if (Input::Get().IsKeyPressed(Keys::DOWN))
				{
					transform.Scale(Vector3::Down() * camereSpeed);
				}
				else if (Input::Get().IsKeyPressed(Keys::RIGHT))
				{
					transform.Scale(Vector3::Right() * camereSpeed);
				}

				if (Input::Get().IsKeyPressed(Keys::Z))
				{
					transform.Rotate(Vector3::Left() * camereSpeed);
				}
				else if (Input::Get().IsKeyPressed(Keys::X))
				{
					transform.Rotate(Vector3::Right() * camereSpeed);
				}

				if (Input::Get().IsKeyPressed(Keys::Q))
				{
					transform.Rotate(Vector3::Up() * camereSpeed);
				}
				else if (Input::Get().IsKeyPressed(Keys::E))
				{
					transform.Rotate(Vector3::Down() * camereSpeed);
				}

				if (Input::Get().IsKeyPressed(Keys::SPACE))
				{
					transform.Translate(Vector3::Foward() * camereSpeed);
				}
				else if (Input::Get().IsKeyPressed(Keys::LEFT_CONTROL))
				{
					transform.Translate(Vector3::Back() * camereSpeed);
				}

				ECSTransform& childsTransform = transform.GetChild(0).GetTransform().GetChild(0).GetTransform().GetChild(0).GetTransform();
				const int dived = 2;
				if (Input::Get().IsKeyPressed(Keys::I))
				{
					childsTransform.Rotate(Vector3::Up() / dived);
				}
				else if (Input::Get().IsKeyPressed(Keys::J))
				{
					childsTransform.Rotate(Vector3::Left() / dived);
				}
				else if (Input::Get().IsKeyPressed(Keys::K))
				{
					childsTransform.Rotate(Vector3::Down() / dived);
				}
				else if (Input::Get().IsKeyPressed(Keys::L))
				{
					childsTransform.Rotate(Vector3::Right() / dived);
				}

				if (Input::Get().IsKeyPressed(Keys::T))
				{
					childsTransform.Scale(Vector3::Up() / dived);
				}
				else if (Input::Get().IsKeyPressed(Keys::F))
				{
					childsTransform.Scale(Vector3::Left() / dived);
				}
				else if (Input::Get().IsKeyPressed(Keys::G))
				{
					childsTransform.Scale(Vector3::Down() / dived);
				}
				else if (Input::Get().IsKeyPressed(Keys::H))
				{
					childsTransform.Scale(Vector3::Right() / dived);
				}

				GetTransform().LookAt(transform.GetPosition());
			}
		}
	};
}