#pragma once
// Import Tara engine library
#include "../core/config.h"
#include "../component/camera.h"
#include "system.h"

namespace Tara {
	class TARA_API CameraSystem : public System<CameraComponent> {
	public:
		std::vector<CameraComponent*> GetUseCamera();
	};
}