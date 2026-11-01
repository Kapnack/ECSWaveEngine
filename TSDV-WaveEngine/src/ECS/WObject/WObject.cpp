#include "WObject.h"

#include <typeindex>

#include "Mesh/Mesh.h"
#include "Material/Material.h"
#include "ECS/Component/Component.h"
#include "TextureImporter/Texture.h"
#include "Material/MaterialManager.h"
#include "ECS/WaveObject/WaveObject.h"
#include "ModelImporter/ModelImporter.h"
#include "Mesh/MeshManager/MeshManager.h"
#include "TextureImporter/TextureManager.h"
#include "ServiceProvider/ServiceProvider.h"
#include "ECS/WaveObject/WaveObjectRegistry.h"
#include "ECS/CompontRegistry/ComponentRegistry.h"

namespace WaveEngine
{
	const unsigned int WObject::NULL_WAVE_OBJECT = 0;

	WObject::WObject()
	{
	}

	WObject::~WObject()
	{
	}

	void WObject::SetID(unsigned int ID)
	{
		this->ID = ID;
	}

	unsigned int WObject::GetID() const
	{
		return ID;
	}

	WaveObject& WObject::Instantiate(const char* modelDir, bool useAbsolutePath, const char* rootName)
	{
		ServiceProvider::Instance().Get<ModelImporter>()->LoadScene(modelDir, useAbsolutePath);
		return *ServiceProvider::Instance().Get<ModelImporter>()->IntantiateModel(rootName);
	}

	void WObject::Destroy(WObject& wObject)
	{
		if (Component* component = dynamic_cast<Component*>(&wObject))
			Destroy(*component);
		else if (WaveObject* waveObject = dynamic_cast<WaveObject*>(&wObject))
			Destroy(*waveObject);
		else if (Material* material = dynamic_cast<Material*>(&wObject))
			Destroy(*material);
		else if (Texture* texture = dynamic_cast<Texture*>(&wObject))
			Destroy(*texture);
		else if (Mesh* mesh = dynamic_cast<Mesh*>(&wObject))
			Destroy(*mesh);
	}

	void WObject::Destroy(Component& component)
	{
		ServiceProvider::Instance().Get<ComponentRegistry>()->RemoveComponent(component.GetID(), typeid(component));
	}

	void WObject::Destroy(WaveObject& waveObject)
	{
		ServiceProvider::Instance().Get<WaveObjectRegistry>()->Destroy(waveObject);
	}

	void WObject::Destroy(Material& material)
	{
		ServiceProvider::Instance().Get<MaterialManager>()->Destroy(material);
	}

	void WObject::Destroy(Texture& texture)
	{
		ServiceProvider::Instance().Get<TextureManager>()->Destroy(texture);
	}

	void WObject::Destroy(Mesh& mesh)
	{
		ServiceProvider::Instance().Get<MeshManager>()->Destroy(mesh);
	}

	void WObject::DestroyImmediate(WObject& wObject)
	{
		if (Component* component = dynamic_cast<Component*>(&wObject))
			DestroyImmediate(*component);
		else if (WaveObject* waveObject = dynamic_cast<WaveObject*>(&wObject))
			DestroyImmediate(*waveObject);
		else if (Material* material = dynamic_cast<Material*>(&wObject))
			DestroyImmediate(*material);
		else if (Texture* texture = dynamic_cast<Texture*>(&wObject))
			DestroyImmediate(*texture);
		else if (Mesh* mesh = dynamic_cast<Mesh*>(&wObject))
			DestroyImmediate(*mesh);
	}

	void WObject::DestroyImmediate(Component& component)
	{
		ServiceProvider::Instance().Get<ComponentRegistry>()->RemoveComponentImmediate(component.GetID(), typeid(component));
	}

	void WObject::DestroyImmediate(WaveObject& waveObject)
	{
		ServiceProvider::Instance().Get<WaveObjectRegistry>()->DestroyImmediate(waveObject);
	}

	void WObject::DestroyImmediate(Material& material)
	{
		ServiceProvider::Instance().Get<MaterialManager>()->DestroyImmediate(material);
	}

	void WObject::DestroyImmediate(Texture& texture)
	{
		ServiceProvider::Instance().Get<TextureManager>()->DestroyImmediate(texture);
	}

	void WObject::DestroyImmediate(Mesh& mesh)
	{
		ServiceProvider::Instance().Get<MeshManager>()->DestroyImmediate(mesh);
	}
}