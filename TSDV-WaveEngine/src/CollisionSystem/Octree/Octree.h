#pragma once

namespace WaveEngine
{
	template<typename T>
	class Octree
	{
		private OctreeNode<ObjectType> root;
		public BoundingBox boundingBox;
		private float minNodeSize = 0.0f;
		private int maxObjectsPerNode = 0;

		private Dictionary<ObjectType, Vector3> lastPositions = new Dictionary<ObjectType, Vector3>();

		public Octree(ObjectType[] worldObjects, BoundingBox boundingBox, float minNodeSize, int maxObjectsPerNode)
		{
			this.maxObjectsPerNode = maxObjectsPerNode;
			this.boundingBox = boundingBox;
			this.minNodeSize = minNodeSize;
			CreateTree(worldObjects);
		}

		public Octree(ObjectType[] worldObjects, float minNodeSize, int maxObjectsPerNode)
		{
			this.maxObjectsPerNode = maxObjectsPerNode;
			this.minNodeSize = minNodeSize;
			CalculateBounds(worldObjects);
			CreateTree(worldObjects);
		}

		void CreateTree(ObjectType[] worldObjects)
		{
			root = new OctreeNode<ObjectType>(boundingBox, minNodeSize, maxObjectsPerNode);

			foreach(ObjectType obj in worldObjects)
			{
				root.Insert(obj);
				lastPositions[obj] = obj.Position;
			}
		}

		public void Tick(OctreeUpdate<ObjectType> updateLogic, ParallelOptions parallelOption, params object[] parameters)
		{
			ObjectType[] objects = new ObjectType[lastPositions.Count];
			lastPositions.Keys.CopyTo(objects, 0);

			foreach(ObjectType obj in objects)
			{
				if (obj == null) continue;

				if (obj.Position != lastPositions[obj])
				{
					root.Remove(obj);
					root.Insert(obj);
					lastPositions[obj] = obj.Position;
				}
			}

			root.Tick(updateLogic, parallelOption, parameters);
		}

		public void Insert(ObjectType obj)
		{
			root.Insert(obj);
			lastPositions[obj] = obj.Position;
		}

		public void Remove(ObjectType obj)
		{
			root.Remove(obj);
			lastPositions.Remove(obj);
		}

		private void CalculateBounds(ObjectType[] gameObjects)
		{
			foreach(ObjectType go in gameObjects)
				boundingBox.Encapsulate(go.BoundingBox);

			Vector3 size = Vector3.one * Mathf.Max(boundingBox.Size.x, boundingBox.Size.y, boundingBox.Size.z);
			boundingBox.SetMinMax(boundingBox.Center - size, boundingBox.Center + size);
		}

		public void Draw()
		{
			root.DrawNode();
		}
	}
}