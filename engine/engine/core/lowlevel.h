#pragma once
#include "config.h"

namespace Tara {
	class TARA_API LowLevel {
	public:
		static void Viewport(int32_t w, int32_t h);
		static void Viewport(int32_t x, int32_t y, int32_t w, int32_t h);
		static void DepthTest(bool e);
		static void WireframeMode(bool e);
		static glm::ivec2 FramebufferSize();
		static void* GetWindowConext();
		static void SetWindowConext(void* ptr);
	};
}

