#include "Draw.h"

#include "ServiceProvider/ServiceProvider.h"

#include "ECS/Transform/ECSTransform.h"
#include "ECS/Mesh/MeshID.h"
#include "ECS/MaterialID.h"
#include "ECS/ComponentContainer/ComponentContainer.h"

#include <vector>

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

		for (size_t i = 0; i < components.size(); ++i)
		{
			int entityID = entities[i];
			const MeshRenderer& meshRenderer = components[i];

			const MeshID* meshComp = meshIDRendererStorage.TryGet(entityID);
			const ECSTransform* transform = transfromStorage.TryGet(entityID);

			if (!meshComp || !transform)
				continue;

			GetRenderer()->Submit(*transform, *meshComp, meshRenderer);
		}
	}

	Renderer* DrawLogic::GetRenderer()
	{
		return ServiceProvider::Instance().Get<Renderer>();
	}

	ComponentRegistry* DrawLogic::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}
}