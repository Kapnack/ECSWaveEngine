#pragma once

#include "Mesh/MeshManager/MeshManager.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "Renderer/Renderer.h"
#include "Mesh/Mesh.h"
#include "BoundingBox/BoundingBox.h"
#include "ECS/WaveObject/WaveObject.h"

namespace WaveEngine
{
	class MeshLogic final
	{
	private:

		MeshManager* GetMeshManager();
		ComponentRegistry* GetComponentRegistry();
		WaveObjectRegistry* GetWaveObjectRegistry();

		Renderer* GetRenderer();

		void SubmitBoundingBox(WaveObject& waveObject);

		BoundingBox UpdateBoundingBox(WaveObject& waveObject);
		BoundingBox EncapsulateMeshVerts(WaveObject& waveObject, BoundingBox box);

	public:

		void Update();
	};
}