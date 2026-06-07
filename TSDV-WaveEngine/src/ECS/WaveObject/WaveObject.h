#pragma once

#include <string>

#include "ECS/CompontRegistry/ComponentRegistry.h"
#include <ECS/Transform/ECSTransform.h>

using namespace std;

namespace WaveEngine
{
	class WaveObjectFactory;

	class WaveObject
	{
	private:

		string name = "";
		unsigned int ID = NULL_OBJECT;

		ComponentRegistry* GetComponentRegistry();

		friend class WaveObjectFactory;

	public:

		static const unsigned int NULL_OBJECT = 0;

		WaveObject(const unsigned int& ID);
		~WaveObject();

		void SetName(const string& name);
		const string& GetName();

		const unsigned int& GetID() const;

		ECSTransform& GetTransform();

		template<typename T>
		T& AddComponent()
		{
			return GetComponentRegistry()->AddComponent<T>(ID);
		}

		template<typename T>
		T& GetComponent()
		{
			return GetComponentRegistry()->GetComponent<T>(ID);
		}

		template<typename T>
		void RemoveComponent()
		{
			GetComponentRegistry()->RemoveComponent<T>(ID);
		}
	};
}