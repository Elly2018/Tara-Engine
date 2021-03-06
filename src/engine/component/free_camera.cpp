#include "free_camera.h"
// Import Tara engine library
#include "transformation.h"
#include "camera.h"
#include "../core/scene_object/scene_object.h"
#include "../core/input.h"

namespace Tara {
	FreeCameraComponent::~FreeCameraComponent()
	{
	}
	void FreeCameraComponent::Start()
	{
		trans = Host().GetRelateComponent<TransformationComponent>();
	}
	void FreeCameraComponent::Update()
	{
		const glm::vec2 delta = EInput::GetMouseDelta();
		if (EInput::IsMouseButton(button_action::Button2)) {
			trans->Rotate(-delta.y * 0.2f, delta.x * 0.2f);
		}
		glm::vec3 movedir = glm::vec3(0);
		if (EInput::IsKey(keycode::W)) movedir += glm::vec3(0, 0, -1);
		if (EInput::IsKey(keycode::S)) movedir += glm::vec3(0, 0, 1);
		if (EInput::IsKey(keycode::A)) movedir += glm::vec3(-1, 0, 0);
		if (EInput::IsKey(keycode::D)) movedir += glm::vec3(1, 0, 0);
		movedir *= EInput::Delta() * 20.0;
		trans->Translate(-movedir);
		movedir = glm::vec3(0);
		if (EInput::IsKey(keycode::LEFT_SHIFT)) movedir += glm::vec3(0, -1, 0);
		if (EInput::IsKey(keycode::SPACE)) movedir += glm::vec3(0, 1, 0);
		movedir *= EInput::Delta() * 20.0;
		trans->Translate(movedir, Space::World);
	}
}