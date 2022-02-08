#pragma once
#include <config.h>
#include <components/component.h>

namespace Tara {
	/*
		Summary:
			The pack of information contains all the collision event data.
	*/
	struct DllExport CollisionData {
	public:
		EObject* target;
		glm::vec3 point;
	};

	/*
		Collision detection base class
	*/
	class DllExport CColiision : public EComponent {
	public:
		DEFAULT_CTOR_IMPLE(CColiision);
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