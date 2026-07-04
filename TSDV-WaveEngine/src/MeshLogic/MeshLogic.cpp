#include "MeshLogic.h"

#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Mesh/MeshManager/MeshManager.h"
#include "ECS/Transform/ECSTransform.h"
#include "ECS/WaveObject/WaveObject.h"
#include "WaveMath/Vector3/Vector3.h"
#include "BoundingBox/BoundingBox.h"
#include "Renderer/Renderer.h"
#include "ECS/Mesh/MeshID.h"
#include "VertexData.h"
#include "Mesh/Mesh.h"

namespace WaveEngine
{
	MeshManager* MeshLogic::GetMeshManager()
	{
		return ServiceProvider::Instance().Get<MeshManager>();
	}

	ComponentRegistry* MeshLogic::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}

	WaveObjectRegistry* MeshLogic::GetWaveObjectRegistry()
	{
		return ServiceProvider::Instance().Get<WaveObjectRegistry>();
	}

	void MeshLogic::Update()
	{
		for (WaveObject* waveObject : GetWaveObjectRegistry()->GetParentWaveObjects())
		{
			ECSTransform& transform = waveObject->GetTransform();

			if (transform.IsDirty() || transform.HasChildDirty())
				UpdateBoundingBox(*waveObject);
		}
	}

	BoundingBox MeshLogic::EncapsulateMeshVerts(WaveObject& waveObject, BoundingBox box)
	{
		MeshID* meshID = waveObject.TryGetComponent<MeshID>();

		if (!meshID || meshID->meshID == Mesh::NULL_MESH)
			return box;

		ECSTransform& transform = waveObject.GetTransform();
		Mesh& mesh = GetMeshManager()->Get(meshID->meshID);

		for (int i = 0; i < mesh.GetVertexSize(); ++i)
		{
			glm::vec4 worldPos = transform.GetGlobalModel() * glm::vec4(
				mesh.GetVertexBuffer()[i].position.x,
				mesh.GetVertexBuffer()[i].position.y,
				mesh.GetVertexBuffer()[i].position.z,
				1.0f
			);

			box.Encapsulate(Vector3(worldPos.x, worldPos.y, worldPos.z));
		}

		return box;
	}

	BoundingBox MeshLogic::UpdateBoundingBox(WaveObject& waveObject)
	{
		ECSTransform& transform = waveObject.GetTransform();
		MeshID* meshID = waveObject.TryGetComponent<MeshID>();

		BoundingBox box;
		box.Reset();

		for (WaveObject* childObj : waveObject.GetTransform().GetChilds())
			box.Encapsulate(UpdateBoundingBox(*childObj));

		box = EncapsulateMeshVerts(waveObject, box);

		transform.ClearDirtFlags();

		if (meshID)
			meshID->boundingBox = box;

		return box;
	}
}