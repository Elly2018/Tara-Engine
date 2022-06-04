#pragma once
// Include third party library
#include <glm/glm.hpp>

// Include tara library
#include "../config.h"

namespace Tara {

	class TARA_API PhysicsSetting {
	public:
		glm::vec3 gravity;
	private:
		friend class World;
		PhysicsSetting();
		~PhysicsSetting();
	};


	class TARA_API LightSetting {
	public:
		/*
			The w axis represent the intensity.
		*/
		glm::vec4 ambientLight;
	private:
		friend class World;
		LightSetting();
		~LightSetting();
	};


	class TARA_API World {
	public:
		static World* Instance();
		void SetDefault();
		PhysicsSetting* m_physicsSetting = new PhysicsSetting();
		LightSetting* m_lightSetting = new LightSetting();
	private:
		World();
		~World();
	};
}