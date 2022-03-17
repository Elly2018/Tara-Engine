#pragma once
#include "../../editor/editor_container.h"

namespace Tara {
    namespace UI {
        class PropertiesWindow : public ImGui_WindowBase {
        public:
            ImGui_WindiwFlags flags = ImGui_WindiwFlags();
            PropertiesWindow();
            void Content() override;

        private:
            std::string MenuPath();
            std::string search = "";
            std::vector<std::string> menupath;
        };
    }
}