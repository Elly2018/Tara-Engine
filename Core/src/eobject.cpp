#include "eobject.h"
#include <Scene.h>

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
		Destroy();
		for (EComponent* i : m_components) {
			delete i;
		}
	}

	bool EObject::SetParent(EObject* target)
	{
		if (target->m_hostScene != m_hostScene) {
			TARA_ERROR("The host Scene is differnt");
			return false;
		}
		if (target == m_parent) return true;
		if (target == nullptr) {
			if (m_parent != nullptr) m_parent->RemoveChild(this);
			m_hostScene->AddObject(target);
		}
		else {
			m_parent->RemoveChild(this);
			m_parent = target;
			target->AddChild(this);
		}
		return true;
	}
	EObject* EObject::Parent()
	{
		return m_parent;
	}
	EObject* EObject::GetChild(int32_t index)
	{
		if (index < 0 || index > m_children.size() - 1) {
			TARA_ERROR("%s: 'remove_child' index out of range", m_name);
			return nullptr;
		}
		return m_children[index];
	}
	bool EObject::AddChild(EObject* target)
	{
		m_children.push_back(target);
		return true;
	}
	bool EObject::RemoveChild(EObject* target)
	{
		std::remove(m_children.begin(), m_children.end(), target);
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
	void EObject::Update()
	{
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
			i->Destroy();
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
	EObject* ObjectFactory::OFViewer::CreateFreeCamera()
	{
		EObject* buffer = new EObject();
		buffer->AddComponent<CTransformation>();
		buffer->AddComponent<CFreeCamera>();
		return buffer;
	}
	EObject* ObjectFactory::OFViewer::CreateCamera()
	{
		EObject* buffer = new EObject();
		buffer->AddComponent<CTransformation>();
		buffer->AddComponent<CCamera>();
		return buffer;
	}
	EObject* ObjectFactory::OF3D::CreateMesh(CommomMesh mesh)
	{
		EObject* buffer = new EObject();
		buffer->AddComponent<CTransformation>();
		CMeshRenderer* m = buffer->AddComponent<CMeshRenderer>();
		m->SetMesh(Mesh::GetCommon(mesh));
		m->SetMaterial(new Material(Shader::GetCommon(CommonShader::Color)));
		return buffer;
	}
	EObject* ObjectFactory::OF3D::CreateMeshWithPhysics(CommomMesh mesh)
	{
		EObject* buffer = new EObject();
		buffer->AddComponent<CTransformation>();
		buffer->AddComponent<CPhysics>();
		CMeshRenderer* m = buffer->AddComponent<CMeshRenderer>();
		m->SetMesh(Mesh::GetCommon(mesh));
		m->SetMaterial(new Material(Shader::GetCommon(CommonShader::Color)));
		return buffer;
	}
	EObject* ObjectFactory::OF2D::CreateSprite()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
	EObject* ObjectFactory::OF2D::CreateSpriteWithPhysics()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
	EObject* ObjectFactory::OFSystem::CreatePostProcessSystem()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
	EObject* ObjectFactory::OFSystem::CreateVoxelSystem()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
	EObject* ObjectFactory::OFParticle::CreateDefaultParticleSystem()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
	EObject* ObjectFactory::OFParticle::CreateGPUParticleSystem()
	{
		EObject* buffer = new EObject();
		return buffer;
	}
}