#include "renderer.h"

Tara::FrameBuffer* Tara::renderer::primarydisplay = nullptr;
glm::mat4 Tara::renderer::view = glm::mat4(1);
glm::mat4 Tara::renderer::projection = glm::mat4(1);