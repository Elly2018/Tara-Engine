#include "renderer.h"
#include <material.h>

namespace Tara {
	FrameBuffer* Tara::renderer::primarydisplay = nullptr;
	glm::mat4 Tara::renderer::view = glm::mat4(1);
	glm::mat4 Tara::renderer::projection = glm::mat4(1);
	bool Tara::renderer::wireframeMode = false;
	Material* Tara::renderer::pureColor = nullptr;
	RenderState Tara::renderer::m_RenderState = RenderState();
}