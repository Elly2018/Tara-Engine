#include "base.h"
#include <functional>

namespace Tara {
	TaraObjectEventBase::TaraObjectEventBase()
	{
		m_InitDelegate.push_back(std::bind(&TaraEventBase::Init, this));
		m_StartDelegate.push_back(std::bind(&TaraEventBase::Start, this));
		m_UpdateDelegate.push_back(std::bind(&TaraEventBase::Update, this));
		m_DestroyDelegate.push_back(std::bind(&TaraEventBase::Destroy, this));
		m_EnableDelegate.push_back(std::bind(&TaraEventBase::Enable, this));
		m_DisableDelegate.push_back(std::bind(&TaraEventBase::Disable, this));
	}
}