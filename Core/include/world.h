#pragma once
#include <config.h>
#include <glm/glm.hpp>

namespace Tara {
	class DllExport World
	{
	public:
		World();
		~World();

		glm::vec3 gravity = glm::vec3(0, 9.81f, 0);
	};

	DllExport World* current_world();
	DllExport void set_activeworld(World* target);
}