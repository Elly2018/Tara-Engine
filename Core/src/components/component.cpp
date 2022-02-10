#include "components/component.h"
#include <eobject.h>
#include <components/transformation.h>

namespace Tara {
	#ifndef TARA_NO_IMGUI
	bool EComponent::m_debugMenu = false;
	bool& EComponent::DebugMenu() {
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

	void EComponent::SetEnable(const bool _enable)
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
	CTransformation* EComponent::Transform()
	{
		return m_host->GetRelateComponent<CTransformation>();
	}
};