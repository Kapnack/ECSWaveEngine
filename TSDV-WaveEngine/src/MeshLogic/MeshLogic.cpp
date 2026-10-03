#include "MeshLogic.h"

#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ECS/BoundingBoxComp/BoundingBoxComp.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Mesh/MeshManager/MeshManager.h"
#include "ECS/Transform/ECSTransform.h"
#include "ECS/WaveObject/WaveObject.h"
#include "WaveMath/Vector3/Vector3.h"
#include "BoundingBox/BoundingBox.h"
#include "ECS/Mesh/MeshID.h"
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

		const Matrix4x4& m = waveObject.GetTransform().GetGlobalModel();
		Mesh& mesh = GetMeshManager()->Get(meshID->meshID);

		Vector3 center = mesh.GetCenter();
		Vector3 extents = mesh.GetExtends();

		Vector3 worldCenter = m * center;

		Vector3 worldExtents = m.ArvosMethod(extents);

		box.Encapsulate(worldCenter - worldExtents);
		box.Encapsulate(worldCenter + worldExtents);
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

		waveObject.GetComponent<BoundingBoxComp>().bounds = box;

		return box;
	}
}