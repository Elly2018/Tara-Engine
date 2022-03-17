#pragma once
// Import Tara engine library
#include "../core/config.h"
#include "component.h"

namespace Tara {
	class TARA_API SceneObject;

	/*
		Summary:
			Physics constraint will lock the specific axis of rotation or position.
	*/
	enum class TARA_API PhysicsConstraint {
		Position_x = 1,
		Position_y = 2,
		Position_z = 4,
		Rotation_x = 8,
		Rotation_y = 16,
		Rotation_z = 32,
	};
	/*
		Summary:
			Physics component will decide that if object should apply force.
			The global physics parameters is in world class. in case user want to change it.
	*/
	class TARA_API PhysicsComponent : public Component {
	public:
		DEFAULT_CTOR_IMPLE(PhysicsComponent);
		virtual ~PhysicsComponent();
		// Apply global force
		bool apply_physics = true;
		// Contsraint flags
		int32_t constraint = 0;
	};
}