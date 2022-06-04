#pragma once
// Import Tara engine library
#include "camera.h"

namespace Tara {
	/*
		Summary:
			Free moving camera.
			The very basic scene viewer camera.
	*/
	class TARA_API FreeCameraComponent : public CameraComponent {
	public:
		DEFAULT_CTOR_INHERIT_IMPLE(FreeCameraComponent, CameraComponent);
		virtual ~FreeCameraComponent();
		void Start() override;
		void Update() override;
	private:
		TransformationComponent* trans;
	};
}