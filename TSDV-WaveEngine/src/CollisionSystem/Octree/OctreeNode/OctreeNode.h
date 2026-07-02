#pragma once

#include <list>
#include <unordered_set>

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "BoundingBox/BoundingBox.h"
#include "WaveMath/Vector3/Vector3.h"
#include <ECS/Mesh/MeshID.h>

using namespace std;

namespace WaveEngine
{
	class OctreeNode
	{
	private:

		WaveObjectRegistry* GetWaveObjectRegistry()
		{
			return ServiceProvider::Instance().Get<WaveObjectRegistry>();
		}

		static constexpr int MaxChilds = 8;
		int maxObjects = 1;
		float minNodeSize = 0.0f;

		list<unsigned int> octreeObjects;

		BoundingBox bounds;
		BoundingBox childBounds[MaxChilds];

		OctreeNode* children = nullptr;

		void Subdivide()
		{
			if (children == nullptr)
			{
				children = new OctreeNode[MaxChilds];
				for (int i = 0; i < MaxChilds; ++i)
					children[i] = OctreeNode(childBounds[i], minNodeSize, maxObjects);
			}

			std::list<unsigned int> remainingHere;

			for (unsigned int id : octreeObjects)
			{
				WaveObject& waveObj = GetWaveObjectRegistry()->GetWaveObject(id);

				InsertIntoChildren(waveObj, remainingHere);
			}

			if (remainingHere.size() == octreeObjects.size())
			{
				ClearChildren();
				return;
			}

			octreeObjects = std::move(remainingHere);
		}

		void InsertIntoChildren(const WaveObject& octreeObject, std::list<unsigned int>& fallback)
		{
			bool intersectedChild = false;

			MeshID meshID = octreeObject.GetComponent<MeshID>();

			for (int i = 0; i < MaxChilds; ++i)
			{
				if (meshID.boundingBox.Intersects(childBounds[i]))
				{
					if (children != nullptr)
					{
						children[i].Insert(octreeObject);
						intersectedChild = true;
					}
				}
			}

			if (!intersectedChild)
				fallback.push_back(octreeObject.GetID());
		}

		void TryMerge()
		{
			if (children == nullptr)
				return;

			unordered_set<unsigned int> allIds;
			CollectIds(allIds);

			if (allIds.size() > static_cast<size_t>(maxObjects))
				return;

			octreeObjects.clear();
			for (unsigned int id : allIds)
			{
				octreeObjects.push_back(id);
			}

			ClearChildren();
		}

		void CollectIds(std::unordered_set<unsigned int>& result)
		{
			if (children == nullptr)
				return;

			for (int i = 0; i < MaxChilds; ++i)
			{
				for (unsigned int id : children[i].octreeObjects)
				{
					result.insert(id);
				}
				children[i].CollectIds(result);
			}
		}

		void ClearChildren()
		{
			if (children != nullptr)
			{
				delete[] children;
				children = nullptr;
			}
		}

	public:

		OctreeNode()
		{

		}

		OctreeNode(BoundingBox bounds, float minNodeSize, int maxObjects)
		{
			this->maxObjects = maxObjects;
			this->bounds = bounds;
			this->minNodeSize = minNodeSize;
			this->children = nullptr;

			const int divsX = 2;
			const int divsY = 2;
			const int divsZ = 2;

			Vector3 childSize(
				bounds.GetSize().x / divsX,
				bounds.GetSize().y / divsY,
				bounds.GetSize().z / divsZ
			);

			int index = 0;
			for (int x = 0; x < divsX; x++)
			{
				for (int y = 0; y < divsY; y++)
				{
					for (int z = 0; z < divsZ; z++)
					{
						Vector3 childCenter = bounds.GetMin() + Vector3(
							childSize.x * (x + 0.5f),
							childSize.y * (y + 0.5f),
							childSize.z * (z + 0.5f)
						);
						childBounds[index++] = BoundingBox(childCenter, childSize);
					}
				}
			}
		}

		~OctreeNode()
		{
			ClearChildren();
		}

		OctreeNode(const OctreeNode&) = delete;

		OctreeNode& operator=(const OctreeNode&) = delete;

		OctreeNode(OctreeNode&& other) noexcept : octreeObjects(std::move(other.octreeObjects)), bounds(other.bounds), minNodeSize(other.minNodeSize), maxObjects(other.maxObjects), children(other.children)
		{
			for (int i = 0; i < MaxChilds; ++i) childBounds[i] = other.childBounds[i];
			other.children = nullptr;
		}

		OctreeNode& operator=(OctreeNode&& other) noexcept
		{
			if (this != &other)
			{
				ClearChildren();
				octreeObjects = std::move(other.octreeObjects);
				bounds = other.bounds;
				for (int i = 0; i < MaxChilds; ++i) childBounds[i] = other.childBounds[i];
				minNodeSize = other.minNodeSize;
				maxObjects = other.maxObjects;
				children = other.children;
				other.children = nullptr;
			}

			return *this;
		}

		//void Tick()
		//{
		//	if (!octreeObjects.empty())
		//	{
		//		std::vector<TObject*> objs;
		//		objs.reserve(octreeObjects.size());
		//
		//		for (unsigned int id : octreeObjects)
		//		{
		//			auto waveObj = GetWaveObjectRegistry()->GetWaveObject(id);
		//			TObject* obj = waveObj.template TryGetComponent<TObject>();
		//			if (obj != nullptr)
		//				objs.push_back(obj);
		//		}
		//
		//		if (!objs.empty())
		//		{
		//			updateLogic(objs, parameters...);
		//		}
		//	}
		//
		//	if (!GetIsLeaf())
		//	{
		//		if (children != nullptr)
		//		{
		//			for (int i = 0; i < MaxChilds; ++i)
		//			{
		//				children[i].Tick(updateLogic, parameters...);
		//			}
		//		}
		//	}
		//}

		void Insert(const WaveObject& octreeObject)
		{
			if (!GetIsLeaf())
			{
				InsertIntoChildren(octreeObject, octreeObjects);
				return;
			}

			octreeObjects.push_back(octreeObject.GetID());

			if (bounds.GetSize().x > minNodeSize && octreeObjects.size() >= maxObjects)
				Subdivide();
		}

		bool Remove(const WaveObject& obj)
		{
			octreeObjects.remove(obj.GetID());

			if (children != nullptr)
			{
				bool allChildrenEmpty = true;

				for (int i = 0; i < MaxChilds; i++)
				{
					bool childEmpty = children[i].Remove(obj);
					if (!childEmpty)
					{
						allChildrenEmpty = false;
					}
				}

				if (allChildrenEmpty)
				{
					ClearChildren();
				}
				else
				{
					TryMerge();
				}
			}

			return octreeObjects.empty() && children == nullptr;
		}

		bool GetIsLeaf() const
		{
			return children == nullptr;
		}
	};
}