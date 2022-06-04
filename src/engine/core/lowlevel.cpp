#include "lowlevel.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window/ewindow.h"

namespace Tara {
	void LowLevel::Viewport(int32_t w, int32_t h)
	{
		Viewport(0, 0, w, h);
	}
	void LowLevel::Viewport(int32_t x, int32_t y, int32_t w, int32_t h)
	{
		glViewport(x, y, w, h);
	}
	void LowLevel::DepthTest(bool e)
	{
		if(e) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);
	}
	void LowLevel::WireframeMode(bool e)
	{
		if (e) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glm::ivec2 LowLevel::FramebufferSize()
	{
		EWindow* wptr = CurrentWindow();
		GLFWwindow* w = (GLFWwindow*)wptr->WindowPtr();
		if (!w) {
			TARA_RUNTIME_ERROR("ImGui window casting error.");
			return glm::ivec2();
		}

		int32_t display_w, display_h;
		glfwGetFramebufferSize(w, &display_w, &display_h);
		return glm::ivec2(display_w, display_h);
	}
	void* LowLevel::GetWindowConext()
	{
		return glfwGetCurrentContext();
	}
	void LowLevel::SetWindowConext(void* ptr)
	{
		glfwMakeContextCurrent((GLFWwindow*)ptr);
	}
}