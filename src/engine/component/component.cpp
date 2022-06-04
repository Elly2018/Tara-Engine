#include "component.h"
#include "../core/scene_object/scene_object.h"
#include "transformation.h"

namespace Tara {
	Component::Component(SceneObject* _host)
	{
		m_host = _host;
		Init();
	}
	Component::~Component()
	{
	}

	void Component::SetEnable(const bool _enable)
	{
		m_enable = _enable;
		if (_enable) Enable();
		else Disable();
	}
	bool Component::GetEnable()
	{
		return m_enable;
	}
	SceneObject& Component::Host()
	{
		return *m_host;
	}
	TransformationComponent& Component::Transform()
	{
		TransformationComponent* trans = m_host->GetRelateComponent<TransformationComponent>();
		if (!trans) {
			return *m_host->AddComponent<TransformationComponent>();
		}
		return *trans;
	}
};