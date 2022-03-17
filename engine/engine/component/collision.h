#pragma once
// Import Third party library
#include <glm/glm.hpp>

// Import Tara engine library
#include "../core/config.h"
#include "component.h"
#include "../core/scene_object/scene_object.h"

namespace Tara {
	/*
		Summary:
			The pack of information contains all the collision event data.
	*/
	struct TARA_API CollisionData {
	public:
		SceneObject* target;
		glm::vec3 point;
	};

	/*
		Collision detection base class
	*/
	class TARA_API ColiisionComponent : public Component {
	public:
		DEFAULT_CTOR_IMPLE(ColiisionComponent);
		virtual ~ColiisionComponent();
		/*
			Summary:
				Called when physics object enter the area.
		*/
		virtual void OnCollisionEnter(CollisionData data);
		/*
			Summary:
				Called when physics object leave the area.
		*/
		virtual void OnCollisionLeave(CollisionData data);
		/*
			Summary:
				Called when physics object in the area.
		*/
		virtual void OnCollisionStay(CollisionData data);
		/*
			Summary:
				Called when trigger object enter the area.
		*/
		virtual void OnTriggerEnter(CollisionData data);
		/*
			Summary:
				Called when trigger object leave the area.
		*/
		virtual void OnTriggerLeave(CollisionData data);
		/*
			Summary:
				Called when trigger object in the area.
		*/
		virtual void OnTriggerStay(CollisionData data);

		// Is collision trigger type.
		bool m_trigger = false;
	};
}