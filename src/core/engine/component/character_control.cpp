#include "character_control.h"
// Import Tara engine library
#include "transformation.h"
#include "../core/scene_object/scene_object.h"
#include "../core/input.h"

namespace Tara {
	CharacterControlComponent::~CharacterControlComponent()
	{
	}
	void CharacterControlComponent::Start()
	{
		m_trans = Host().GetRelateComponent<TransformationComponent>();
	}
	void CharacterControlComponent::Update()
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
	void CharacterControlComponent::Move(glm::vec3 dir, Space _space)
	{
		//EVIE_DEBUG("moving: %f %f %f", dir.x, dir.y, dir.z);
	}
	void CharacterControlComponent::Look(glm::vec2 dir)
	{
	}
	void CharacterControlComponent::Jump()
	{
	}
}