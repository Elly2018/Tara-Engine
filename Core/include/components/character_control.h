#pragma once
#include <config.h>
#include <components/component.h>
#include <components/transformation.h>

namespace Tara {
	/*
		Summary:
			Character controller base class.
			With basic movement functionality.
	*/
	class DllExport CCharacterControl : public EComponent {
	public:
		DEFAULT_CTOR_IMPLE(CCharacterControl);
		void Start() override;
		void Update() override;
		void Move(glm::vec3 dir, Space _space = Space::Local);
		void Look(glm::vec2 dir);
		void Jump();

		float_t m_mouseSensitivity = 1;
		float_t m_movingSpeed = 0.5f;
		float_t m_jumpForce = 2;

	private:
		EObject* m_cameraObject = nullptr;
		CTransformation* m_trans = nullptr;
	};
}