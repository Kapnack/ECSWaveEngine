#include "DrawLogic.h"

#include "ServiceProvider/ServiceProvider.h"

#include "ECS/Transform/ECSTransform.h"
#include "ECS/Mesh/MeshID.h"
#include "ECS/MaterialID.h"
#include "ECS/ComponentContainer/ComponentContainer.h"

#include <vector>
#include "ECS/Camera/Camera.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/WaveObject/WaveObject.h"
#include <Renderer/Renderer.h>
#include <ECS/CompontRegistry/ComponentRegistry.h>

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
		ComponentContainer<MeshRenderer>& meshRendererContainer = GetComponentRegistry()->GetComponentStorage<MeshRenderer>();
		vector<MeshRenderer>& components = meshRendererContainer.GetComponents();
		const vector<unsigned int>& entities = meshRendererContainer.GetEntities();

		ComponentContainer<MeshID>& meshIDRendererStorage = GetComponentRegistry()->GetComponentStorage<MeshID>();
		ComponentContainer<ECSTransform>& transfromStorage = GetComponentRegistry()->GetComponentStorage<ECSTransform>();

		for (Camera& camera : GetComponentRegistry()->CreateOrGetComponentStorage<Camera>().GetComponents())
			for (WaveObject* waveObject : ServiceProvider::Instance().Get<WaveObjectRegistry>()->GetParentWaveObjects())
				CheckChildsAreInFrustum(*waveObject, camera);
	}

	Renderer* DrawLogic::GetRenderer()
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

	ComponentRegistry* DrawLogic::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}
}