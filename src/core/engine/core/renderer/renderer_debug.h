#pragma once
#include "../config.h"

namespace Tara {
	/*
		Render the debug view on screen.
		All the function call should during the Gizmo stage.
	*/
	class TARA_API RendererDebug {
	public:
		static RendererDebug& Singleton();
		float_t& Alpha();
		glm::vec3& Colro();
		void DrawLine(const glm::vec3 pos1, const glm::vec3 pos2);

	private:
		static RendererDebug* m_Singleton;
		glm::vec3 color = glm::vec3(1);
		float_t alpha = 1;
	};
}