#pragma once
#include "../../editor/editor_container.h"

namespace Tara {
	namespace UI {

		class FrameBuffer;

		class FramebufferViewerWindow : public ImGui_WindowBase {
			FramebufferViewerWindow();
			~FramebufferViewerWindow();

			void SetFrame(FrameBuffer* target);

		private:
			FrameBuffer* frame = nullptr;
		};
	}
}
