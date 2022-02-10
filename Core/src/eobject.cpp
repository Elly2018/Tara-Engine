#include "eobject.h"
#include <Scene.h>
#include <components/allcomponents.h>

namespace Tara {
	EObject::EObject()
	{
		Scene* cs = CurrentScene();
		cs->AddObject(this);
		m_hostScene = cs;
		Init();
		SetEnable(true);
	}
	EObject::~EObject()
	{
		TARA_DEBUG_LEVEL("EObject destroy! %s", 2, Name());
		size_t c = Count();
		for (int32_t i = 0; i < c; i++) {
			delete GetChild(i);
		}
		Destroy();
	}

	bool EObject::SetParent(EObject* target)
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
	EObject* EObject::Parent()
	{
		return m_parent;
	}
	Scene* EObject::HostScene()
	{
		return m_hostScene;
	}
	EObject* EObject::GetChild(int32_t index)
	{
		if (index < 0 || index > m_children.size() - 1) {
			TARA_ERROR("%s: 'remove_child' index out of range", m_name);
			return nullptr;
		}
		return m_children.at(index);
	}
	bool EObject::AddChild(EObject* target)
	{
		m_children.push_back(target);
		return true;
	}
	bool EObject::RemoveChild(EObject* target)
	{
		m_children.erase(std::remove(m_children.begin(), m_children.end(), target), m_children.end());
		return true;
	}
	bool EObject::RemoveChild(int32_t index)
	{
		if (index < 0 || index > m_children.size() - 1) {
			TARA_ERROR("%s: 'remove_child' index out of range", m_name);
			return false;
		}
		EObject* buffer = m_children[index];
		m_children.erase(m_children.begin() + index);
		CurrentScene()->AddObject(buffer);
		return true;
	}
	size_t EObject::Count()
	{
		return m_children.size();
	}

	void EObject::SetEnable(bool e)
	{
		m_enable = e;
		if (m_enable) Enable();
		else Disable();
	}
	bool EObject::GetEnable()
	{
		return m_enable;
	}

	void EObject::Render()
	{
		for (EObject* i : m_children) {
			i->Render();
		}
		for (EComponent* i : m_components) {
			if (i->GetEnable()) {
				if (i->m_init) {
					i->Render();
				}
				else {
					i->Start();
					i->m_init = true;
				}
			}
		}
	}
	void EObject::Gizmo()
	{
		for (EComponent* i : m_components) {
			i->Gizmo();
		}
	}
	void EObject::Update()
	{
		for (EObject* i : m_children) {
			i->Update();
		}
		if (m_init) {
			for (EComponent* i : m_components) {
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
	void EObject::Init()
	{
		for (EComponent* i : m_components) {
			if (i->GetEnable())
				i->Init();
		}
		m_init = true;
	}
	void EObject::Start()
	{
		for (EComponent* i : m_components) {
			i->Start();
		}
	}
	void EObject::Destroy()
	{
		for (EComponent* i : m_components) {
			delete i;
		}
	}
	void EObject::Enable()
	{
		for (EComponent* i : m_components) {
			if (i->GetEnable())
				i->Enable();
		}
	}
	void EObject::Disable()
	{
		for (EComponent* i : m_components) {
			if (i->GetEnable())
				i->Disable();
		}
	}
	EObject* ObjectFactory::CreateEmpty()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
	EObject* ObjectFactory::CreateActor()
	{
		EObject* buffer = new EObject();
		buffer->AddComponent<CTransformation>();
		return buffer;
	}
	EObject* ObjectFactory::CreatePawn()
	{
		EObject* buffer = new EObject();
		buffer->AddComponent<CTransformation>();
		buffer->AddComponent<CMeshRenderer>();
		return buffer;
	}
	EObject* ObjectFactoryViewer::CreateFreeCamera()
	{
		EObject* buffer = new EObject();
		buffer->AddComponent<CTransformation>();
		buffer->AddComponent<CFreeCamera>();
		return buffer;
	}
	EObject* ObjectFactoryViewer::CreateCamera()
	{
		EObject* buffer = new EObject();
		buffer->AddComponent<CTransformation>();
		buffer->AddComponent<CCamera>();
		return buffer;
	}
	EObject* ObjectFactory3D::CreateMesh(CommomMesh mesh)
	{
		EObject* buffer = new EObject();
		buffer->AddComponent<CTransformation>();
		CMeshRenderer* m = buffer->AddComponent<CMeshRenderer>();
		m->SetMesh(Mesh::GetCommon(mesh));
		m->SetMaterial(new Material(*Shader::GetCommon(CommonShader::Color)));
		return buffer;
	}
	EObject* ObjectFactory3D::CreateMeshWithPhysics(CommomMesh mesh)
	{
		EObject* buffer = new EObject();
		buffer->AddComponent<CTransformation>();
		buffer->AddComponent<CPhysics>();
		CMeshRenderer* m = buffer->AddComponent<CMeshRenderer>();
		m->SetMesh(Mesh::GetCommon(mesh));
		m->SetMaterial(new Material(*Shader::GetCommon(CommonShader::Color)));
		return buffer;
	}
	EObject* ObjectFactory2D::CreateSprite()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
	EObject* ObjectFactory2D::CreateSpriteWithPhysics()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
	EObject* ObjectFactorySystem::CreatePostProcessSystem()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
	EObject* ObjectFactorySystem::CreateVoxelSystem()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
	EObject* ObjectFactoryParticle::CreateDefaultParticleSystem()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
	EObject* ObjectFactoryParticle::CreateGPUParticleSystem()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
}