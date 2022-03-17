#pragma once
#include "../../editor/editor_container.h"

namespace Tara {
    namespace UI {
        class HelperWindow : public ImGui_WindowBase {
        public:
            HelperWindow() : ImGui_WindowBase("Helper") {}
            void Content() override;
        };
    }
}