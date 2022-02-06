#pragma once
#include <config.h>
#include <ecomponent.h>
#include <glm/glm.hpp>

namespace Tara {
	class DllExport world
	{
	public:
		world();
		~world();

		glm::vec3 gravity = glm::vec3(0, 9.81f, 0);
	};

	DllExport world* current_world();
	DllExport void set_activeworld(world* target);
}