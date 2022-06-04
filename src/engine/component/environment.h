#pragma once
// Import Tara engine library
#include "../core/config.h"
#include "component.h"

namespace Tara {
	class TARA_API LightComponent;
	class TARA_API Material;

	class TARA_API EnvironmentCoimponent : public Component {
	public:
		DEFAULT_HEADER_CTOR(EnvironmentCoimponent);
		virtual ~EnvironmentCoimponent();

		Material* Skybox = nullptr;
		glm::vec3 BackgroundColor = glm::vec3(0.2);
		LightComponent* SunLight = nullptr;
	};
}