#include "scene_object.h"
#include "../../component/allcomponents.h"
#include "../scene/scene.h"
#include "../event.h"
#include "../mesh/mesh.h"
#include "../material/material.h"
#include "../shader/shader.h"

namespace Tara {
	ObjectFactory* ObjectFactory::m_Singleton = nullptr;

	SceneObject::SceneObject()
	{
		m_init = false;
		m_enable = true;
		m_tag = "";
		m_layer = 0;
		m_parent = NULL;
		m_hostScene = NULL;
		m_children = std::vector<SceneObject*>();
		m_components = std::vector<Component*>();

		Scene* cs = CurrentScene();
		cs->AddObject(this);
		m_hostScene = cs;
		Init();
		SetEnable(true);
		TaraEvent::Singleton().OnSceneObjectCreate(this);
	}
	SceneObject::~SceneObject()
	{
		TARA_DEBUG_LEVEL("SceneObject destroy! %s", 2, Name.c_str());
		Disable();
		size_t c = Count();
		for (int32_t i = 0; i < c; i++) {
			SceneObject* so = GetChild(0);
			if (so) delete so;
		}
		c = m_components.size();
		for (int32_t i = 0; i < c; i++) {
			Component* so = m_components[i];
			if (so) {
				delete so;
				TARA_DEBUG("Delete component");
			}
		}
		TaraEvent::Singleton().OnSceneObjectDestroy(this);
		SceneObject* pare = Parent();
		if (pare) {
			pare->RemoveChild(this);
			TARA_DEBUG("Remove from parent");
		}
		else {
			Scene* hosts = HostScene();
			if (hosts) {
				hosts->Objects.erase(std::remove(hosts->Objects.begin(), hosts->Objects.end(), this), hosts->Objects.end());
				TARA_DEBUG("Remove from host scene");
			}
		}
	}

	bool SceneObject::SetParent(SceneObject* target)
	{
		if (target->m_hostScene != m_hostScene) {
			TARA_ERROR("The host Scene is differnt");
			return false;
		}
		if (target == m_parent) return true;
		if (!target) {
			if (m_parent != nullptr) m_parent->RemoveChild(this);
			m_hostScene->AddObject(target);
		}
		else {
			if (m_parent) {
				m_parent->RemoveChild(this);
			}
			else {
				m_hostScene->RemoveObject(this);
			}
			m_parent = target;
			target->AddChild(this);
		}
		return true;
	}
	SceneObject* SceneObject::Parent()
	{
		return m_parent;
	}
	Scene* SceneObject::HostScene()
	{
		return m_hostScene;
	}
	SceneObject* SceneObject::GetChild(int32_t index)
	{
		if (index < 0 || index > m_children.size() - 1) {
			TARA_ERROR("%s: 'remove_child' index out of range", Name.c_str());
			return nullptr;
		}
		return m_children.at(index);
	}
	bool SceneObject::AddChild(SceneObject* target)
	{
		m_children.push_back(target);
		return true;
	}
	bool SceneObject::RemoveChild(SceneObject* target)
	{
		m_children.erase(std::remove_if(m_children.begin(), m_children.end(), [&](SceneObject* c) -> bool { return c == target; }), m_children.end());
		return true;
	}
	bool SceneObject::RemoveChild(int32_t index)
	{
		if (index < 0 || index > m_children.size() - 1) {
			TARA_ERROR("%s: 'remove_child' index out of range", Name.c_str());
			return false;
		}
		SceneObject* buffer = m_children[index];
		m_children.erase(m_children.begin() + index);
		CurrentScene()->AddObject(buffer);
		return true;
	}
	size_t SceneObject::Count()
	{
		return m_children.size();
	}

	void SceneObject::SetEnable(bool e)
	{
		m_enable = e;
		if (m_enable) Enable();
		else Disable();
	}
	bool SceneObject::GetEnable()
	{
		return m_enable;
	}

	void SceneObject::Update()
	{
		for (SceneObject* i : m_children) {
			i->Update();
		}
		if (m_init) {
			for (Component* i : m_components) {
				if (i->GetEnable()) {
					if (i->m_init) {
						i->Update();
					}
					else {
						i->Start();
						i->m_init = true;
					}
				}
			}
		}
		else {
			Start();
		}
	}
	void SceneObject::Init()
	{
		for (Component* i : m_components) {
			if (i->GetEnable())
				i->Init();
		}
		m_init = true;
	}
	void SceneObject::Start()
	{
		for (Component* i : m_components) {
			i->Start();
		}
	}
	void SceneObject::Destroy()
	{
		
	}
	void SceneObject::Enable()
	{
		for (Component* i : m_components) {
			if (i->GetEnable())
				i->Enable();
		}
	}
	void SceneObject::Disable()
	{
		for (Component* i : m_components) {
			if (i->GetEnable())
				i->Disable();
		}
	}
	ObjectFactory::ObjectFactory()
	{
		m_Viewer = ObjectFactoryViewer();
		m_3D = ObjectFactory3D();
		m_Lighting = ObjectFactoryLight();
		m_2D = ObjectFactory2D();
		m_System = ObjectFactorySystem();
		m_UI = ObjectFactoryUI();
		m_Particle = ObjectFactoryParticle();
	}
	ObjectFactory::~ObjectFactory()
	{
		
	}
	ObjectFactory& ObjectFactory::Singleton()
	{
		if (!m_Singleton) m_Singleton  = new ObjectFactory();
		return *m_Singleton;
	}
	SceneObject* ObjectFactory::CreateEmpty()
	{
		SceneObject* buffer = new SceneObject();
		return buffer;
	}
	SceneObject* ObjectFactory::CreateActor()
	{
		SceneObject* buffer = new SceneObject();
		buffer->AddComponent<TransformationComponent>();
		return buffer;
	}
	SceneObject* ObjectFactory::CreatePawn()
	{
		SceneObject* buffer = new SceneObject();
		buffer->AddComponent<TransformationComponent>();
		buffer->AddComponent<MeshRendererComponent>();
		return buffer;
	}
	SceneObject* ObjectFactoryViewer::CreateFreeCamera()
	{
		SceneObject* buffer = new SceneObject();
		buffer->AddComponent<TransformationComponent>();
		buffer->AddComponent<FreeCameraComponent>();
		return buffer;
	}
	SceneObject* ObjectFactoryViewer::CreateCamera()
	{
		SceneObject* buffer = new SceneObject();
		buffer->AddComponent<TransformationComponent>();
		buffer->AddComponent<CameraComponent>();
		return buffer;
	}
	SceneObject* ObjectFactory3D::CreateMesh(Mesh* mesh, Material* mat)
	{
		SceneObject* buffer = new SceneObject();
		buffer->AddComponent<TransformationComponent>();
		MeshRendererComponent* m = buffer->AddComponent<MeshRendererComponent>();
		if (mesh) m->SetMesh(mesh);
		if (mat) m->SetMaterial(mat);
		return buffer;
	}
	SceneObject* ObjectFactory3D::CreateMeshWithPhysics(Mesh* mesh, Material* mat)
	{
		SceneObject* buffer = new SceneObject();
		buffer->AddComponent<TransformationComponent>();
		buffer->AddComponent<PhysicsComponent>();
		MeshRendererComponent* m = buffer->AddComponent<MeshRendererComponent>();
		if (mesh) m->SetMesh(mesh);
		if (mat) m->SetMaterial(mat);
		return buffer;
	}
	SceneObject* ObjectFactoryLight::CreateDirection()
	{
		SceneObject* buffer = new SceneObject();
		buffer->AddComponent<TransformationComponent>();
		LightComponent* light = buffer->AddComponent<LightComponent>();
		light->m_type = LightType::Direction;
		light->m_important = true;
		return buffer;
	}
	SceneObject* ObjectFactoryLight::CreatePointLight()
	{
		SceneObject* buffer = new SceneObject();
		buffer->AddComponent<TransformationComponent>();
		LightComponent* light = buffer->AddComponent<LightComponent>();
		light->m_type = LightType::Point;
		return buffer;
	}
	SceneObject* ObjectFactoryLight::CreateSpotLight()
	{
		SceneObject* buffer = new SceneObject();
		buffer->AddComponent<TransformationComponent>();
		LightComponent* light = buffer->AddComponent<LightComponent>();
		light->m_type = LightType::Spot;
		return buffer;
	}
	SceneObject* ObjectFactory2D::CreateSprite()
	{
		SceneObject* buffer = new SceneObject();
		return buffer;
	}
	SceneObject* ObjectFactory2D::CreateSpriteWithPhysics()
	{
		SceneObject* buffer = new SceneObject();
		return buffer;
	}
	SceneObject* ObjectFactorySystem::CreatePostProcessSystem()
	{
		SceneObject* buffer = new SceneObject();
		return buffer;
	}
	SceneObject* ObjectFactorySystem::CreateVoxelSystem()
	{
		SceneObject* buffer = new SceneObject();
		return buffer;
	}
	SceneObject* ObjectFactoryUI::CreateCanvas()
	{
		SceneObject* buffer = new SceneObject();
		return buffer;
	}
	SceneObject* ObjectFactoryParticle::CreateDefaultParticleSystem()
	{
		SceneObject* buffer = new SceneObject();
		return buffer;
	}
	SceneObject* ObjectFactoryParticle::CreateGPUParticleSystem()
	{
		SceneObject* buffer = new SceneObject();
		return buffer;
	}
}