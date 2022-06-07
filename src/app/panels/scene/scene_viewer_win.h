#pragma once
#include "engine/core/config.h"
#include "editor/editor_container.h"

namespace Tara {
    class CameraComponent;
	namespace UI {
        class TARA_APP_API SceneViewerWindow : public ImGui_SceneView {
        public:
            SceneViewerWindow();
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