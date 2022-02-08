#pragma once
#include <components/camera.h>
#include <components/transformation.h>

namespace Tara {
	/*
		Summary:
			Free moving camera.
			The very basic scene viewer camera.
	*/
	class DllExport CFreeCamera : public CCamera {
	public:
		DEFAULT_CTOR_INHERIT_IMPLE(CFreeCamera, CCamera);
		void Start() override;
		void Update() override;
	private:
		CTransformation* trans;
	};
}