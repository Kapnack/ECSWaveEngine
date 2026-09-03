#include "DrawLogic.h"

#include "ECS/MaterialID.h"
#include "ECS/Mesh/MeshID.h"
#include "Renderer/Renderer.h"
#include "ECS/Camera/Camera.h"
#include "ECS/Component/Component.h"
#include "ECS/WaveObject/WaveObject.h"
#include "ECS/Transform/ECSTransform.h"
#include "CameraManager/CameraManager.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "BinarySpacePartition/BinarySpacePartition.h"

namespace WaveEngine
{
	DrawLogic::DrawLogic()
	{
	}

	DrawLogic::~DrawLogic()
	{
	}

	void DrawLogic::Init()
	{
	}

	void DrawLogic::Update()
	{
		for (Camera* camera : GetCameraManager()->GetActiveCameras())
			for (WaveObject* waveObject : ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetParentWaveObjects())
				if (GetBinarySpacePartition()->ObjectsShareSpace(camera->GetTransform().GetPosition(), waveObject->GetTransform().GetPosition()))
					CheckChildsAreInFrustum(*waveObject, *camera);
	}

	Renderer* DrawLogic::GetRenderer() const
	{
		return ServiceProvider::Instance().Get<Renderer>();
	}

	void DrawLogic::CheckChildsAreInFrustum(WaveObject& waveObject, Camera& camera)
	{
		const MeshID& meshComp = waveObject.GetComponent<MeshID>();
		const ECSTransform& transform = waveObject.GetTransform();

		GetRenderer()->SubmitWireBox(meshComp.boundingBox, Color::Yellow());

		if (!camera.IsInsideFrustum(meshComp.boundingBox))
			return;

		const MeshRenderer* meshRenderer = waveObject.TryGetComponent<MeshRenderer>();

		if (meshRenderer)
			GetRenderer()->Submit(transform, meshComp, *meshRenderer, camera.GetID());

		for (WaveObject* childWaveObject : waveObject.GetTransform().GetChilds())
			CheckChildsAreInFrustum(*childWaveObject, camera);
	}

	CameraManager* DrawLogic::GetCameraManager() const
	{
		return ServiceProvider::Instance().Get<CameraManager>();
	}

	BinarySpacePartition* DrawLogic::GetBinarySpacePartition() const
	{
		return ServiceProvider::Instance().Get<BinarySpacePartition>();
	}

	ComponentRegistry* DrawLogic::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}
}