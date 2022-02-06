#pragma once
#include <config.h>
#include <framebuffer.h>
#include <glm/glm.hpp>

namespace Tara {
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
	};
}