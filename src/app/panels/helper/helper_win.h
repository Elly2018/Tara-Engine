#pragma once
#include "engine/core/config.h"
#include "editor/editor_container.h"

namespace Tara {
    namespace UI {
        class TARA_APP_API HelperWindow : public ImGui_WindowBase {
        public:
            HelperWindow() : ImGui_WindowBase("Helper") {}
            void Content() override;
        };
    }
}