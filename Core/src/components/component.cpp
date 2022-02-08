#include "components/component.h"
#include <eobject.h>
#include <components/transformation.h>

namespace Tara {
	#ifndef TARA_NO_IMGUI
	bool EComponent::m_debugMenu = false;
	void EComponent::SetDebugMenu(bool v) {
		m_debugMenu = v;
	}
	bool EComponent::GetDebugMenu() {
		return m_debugMenu;
	}
	#endif
	EComponent::EComponent(EObject* _host)
	{
		m_host = _host;
		Init();
	}
	EComponent::~EComponent()
	{
	}

	void EComponent::Init() {}
	void EComponent::Start() {}
	void EComponent::GUI() {}
	void EComponent::Render() {}
	void EComponent::Update() {}
	void EComponent::Destroy() {}
	void EComponent::Enable() {}
	void EComponent::Disable() {}

	void EComponent::SetEnable(bool _enable)
	{
		m_enable = _enable;
		if (_enable) Enable();
		else Disable();
	}
	bool EComponent::GetEnable()
	{
		return m_enable;
	}
	EObject* EComponent::Host()
	{
		return m_host;
	}
	CTransformation* EComponent::TransformComponent()
	{
		return m_host->GetRelateComponent<CTransformation>();
	}
};