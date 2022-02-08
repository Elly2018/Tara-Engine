#pragma once
#include <config.h>
#include <material.h>
#include <framebuffer.h>
#include <glm/glm.hpp>

namespace Tara {
	/*
		Summary:
			Each mainloop render result.
	*/
	struct DllExport RenderState {
	public:
		double_t FPS;
		double_t CPU_Usage;
		double_t GPU_Usage;
		int64_t RAM_Usage;
		int32_t DrawCall;
		int32_t Vertices;
		int32_t Triangle;
	};

	/*
		Summary:
			Renderer utilities.
	*/
	class DllExport renderer
	{
	public:
		/*
			Summary:
				Current use framebuffer.
		*/
		static FrameBuffer* primarydisplay;
		/*
			Summary:
				Current use view matrix.
		*/
		static glm::mat4 view;
		/*
			Summary:
				Current use projection matrix.
		*/
		static glm::mat4 projection;
		static bool wireframeMode;
		static Material* pureColor;
		static RenderState m_RenderState;
	};
}