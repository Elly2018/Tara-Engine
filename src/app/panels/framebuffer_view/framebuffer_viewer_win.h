#pragma once
#include "engine/core/config.h"
#include "editor/editor_container.h"

namespace Tara {
	namespace UI {
		class FrameBuffer;

		class TARA_APP_API FramebufferViewerWindow : public ImGui_WindowBase {
		public:
			FramebufferViewerWindow();
			~FramebufferViewerWindow();

			void SetFrame(FrameBuffer* target);

		private:
			FrameBuffer* frame = nullptr;
		};
	}
}
