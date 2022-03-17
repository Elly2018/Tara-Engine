#pragma once
// Import Tara engine library
#include "../core/config.h"
#include "component.h"

namespace Tara {
	enum class Space;
	class TARA_API SceneObject;

	/*
		Summary:
			Character controller base class.
			With basic movement functionality.
	*/
	class TARA_API CharacterControlComponent : public Component {
	public:
		DEFAULT_CTOR_IMPLE(CharacterControlComponent);
		virtual ~CharacterControlComponent();
		void Start() override;
		void Update() override;
		void Move(glm::vec3 dir, Space _space);
		void Look(glm::vec2 dir);
		void Jump();

		float_t m_mouseSensitivity = 1;
		float_t m_movingSpeed = 0.5f;
		float_t m_jumpForce = 2;

	private:
		SceneObject* m_cameraObject = nullptr;
		TransformationComponent* m_trans = nullptr;
	};
}