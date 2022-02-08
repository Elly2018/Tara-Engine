#include "components/character_control.h"
#include <components/transformation.h>
#include <einput.h>

namespace Tara {
	void CCharacterControl::Start()
	{
		m_trans = m_host->GetRelateComponent<CTransformation>();
	}
	void CCharacterControl::Update()
	{
		glm::vec3 movedir = glm::vec3(0);
		if (EInput::IsKey(keycode::W)) movedir += glm::vec3(0, 0, m_movingSpeed);
		if (EInput::IsKey(keycode::S)) movedir += glm::vec3(0, 0, -m_movingSpeed);
		if (EInput::IsKey(keycode::A)) movedir += glm::vec3(-m_movingSpeed, 0, 0);
		if (EInput::IsKey(keycode::D)) movedir += glm::vec3(m_movingSpeed, 0, 0);
		Move(movedir, Space::Local);
		if (EInput::IsKeyDown(keycode::SPACE)) Jump();
		Look(EInput::GetMouseDelta());
	}
	void CCharacterControl::Move(glm::vec3 dir, Space _space)
	{
		//EVIE_DEBUG("moving: %f %f %f", dir.x, dir.y, dir.z);
	}
	void CCharacterControl::Look(glm::vec2 dir)
	{
	}
	void CCharacterControl::Jump()
	{
	}
}