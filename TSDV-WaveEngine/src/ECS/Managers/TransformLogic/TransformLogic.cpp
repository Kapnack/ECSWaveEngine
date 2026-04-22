#include "TransformLogic.h"

#include "ServiceProvider/ServiceProvider.h"
#include "ECS/Transform/ECSTransform.h"

namespace WaveEngine
{
	TransformLogic::TransformLogic()
	{
	}

	TransformLogic::~TransformLogic()
	{
	}

	void TransformLogic::Init()
	{
	}

    void TransformLogic::Update()
    {
        ComponentContainer<ECSTransform>& transforStorage =
            GetComponentRegistry()->CreateOrGetComponentStorage<ECSTransform>();

        vector<ECSTransform>& transformComponents =
            transforStorage.GetComponents();

        for (ECSTransform& transform : transformComponents)
        {
            if (!transform.IsDirty())
                continue;

            transform.CalculateTRS();
        }

        for (ECSTransform& transform : transformComponents)
        {
            if (transform.GetParent() == -1)
            {
                UpdateHierarchy(transforStorage, transform, glm::mat4(1.0f));
            }
        }
    }

    void TransformLogic::UpdateHierarchy(ComponentContainer<ECSTransform>& storage,
        ECSTransform& transform,
        const glm::mat4& parentMatrix)
    {
        glm::mat4 global = parentMatrix * transform.GetLocalModel();

        transform.SetGlobalModel(global);

        for (unsigned int childID : transform.GetChildren())
        {
            ECSTransform* child = storage.TryGet(childID);
            if (!child)
                continue;

            UpdateHierarchy(storage, *child, global);
        }
    }

	ComponentRegistry* TransformLogic::GetComponentRegistry()
	{
		return ServiceProvider::Instance().Get<ComponentRegistry>();
	}
}