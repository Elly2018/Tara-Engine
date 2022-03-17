#pragma once
#include "../../editor/editor_container.h"

namespace Tara {
    class CameraComponent;
	namespace UI {
        class SceneViewerWindow : public ImGui_SceneView {
        public:
            SceneViewerWindow(const char* title);
            void MenuBar() override;
            void PostRender() override;
            void SetCam(CameraComponent* c);
            bool HaveCam();
            float near = 0;
            float far = 0;
            bool debugWin = 0;
        };
	}
}