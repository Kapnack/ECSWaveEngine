#include "MeshLogic.h"

#include <vector>

#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Mesh/MeshManager/MeshManager.h"
#include "ECS/Transform/ECSTransform.h"
#include "ECS/WaveObject/WaveObject.h"
#include "WaveMath/Vector3/Vector3.h"
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

	Renderer* MeshLogic::GetRenderer()
	{
		return ServiceProvider::Instance().Get<Renderer>();
	}

	void MeshLogic::SubmitBoundingBox(WaveObject& waveObject)
	{
		MeshID* meshID = waveObject.TryGetComponent<MeshID>();

		if (meshID && !meshID->boundingBox.IsEmpty())
			GetRenderer()->SubmitWireBox(meshID->boundingBox);

		for (int childID : waveObject.GetTransform().GetChildren())
		{
			WaveObject& child = GetWaveObjectRegistry()->GetWaveObject(childID);
			SubmitBoundingBox(child);
		}
	}

	void MeshLogic::Update()
	{
		for (std::pair<const unsigned int, WaveObject*> pair : GetWaveObjectRegistry()->GetWaveObjects())
		{
			ECSTransform& transform = pair.second->GetTransform();

			if (transform.GetParent() != WaveObject::NULL_OBJECT)
				continue;

			if (transform.WasDirty())
				UpdateBoundingBox(*pair.second);

			SubmitBoundingBox(*pair.second);
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

		const vector<int>& children = transform.GetChildren();

		BoundingBox box;
		box.Reset();

		if (children.empty())
		{
			// Leaf node: box is just this object's own mesh, if any.
			box = EncapsulateMeshVerts(waveObject, box);
		}
		else
		{
			// Internal node: merge every child's box first, regardless of
			// whether the child itself has a MeshID component. This is the
			// fix - previously children without a MeshID were skipped
			// entirely, which left parent boxes stuck at Reset() (huge boxes)
			// whenever any group/empty node sat between a parent and its
			// mesh-bearing descendants.
			for (unsigned int childID : children)
			{
				WaveObject& childObj = GetWaveObjectRegistry()->GetWaveObject(childID);
				box.Encapsulate(UpdateBoundingBox(childObj));
			}

			// Also fold in this node's own mesh, if it happens to have one.
			box = EncapsulateMeshVerts(waveObject, box);
		}

		transform.ClearDirtFlags();

		// Only store/submit the box on objects that actually carry a MeshID
		// component (i.e. objects that are meant to track a bounding box).
		if (meshID)
		{
			meshID->boundingBox = box;

			if (!box.IsEmpty())
			{
				printf("Submitting box min(%.2f %.2f %.2f) max(%.2f %.2f %.2f)\n",
					box.GetMin().x, box.GetMin().y, box.GetMin().z,
					box.GetMax().x, box.GetMax().y, box.GetMax().z);

				GetRenderer()->SubmitWireBox(box);
			}
		}

		// Always return the computed box up the call stack so parents can
		// merge it, even if this node has no MeshID component to persist it.
		return box;
	}
}