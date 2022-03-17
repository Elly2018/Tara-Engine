#pragma once
#include "../../engine/core/logger.h"
#include "../../editor/editor_container.h"

namespace Tara {
	namespace UI {
        class ConsoleWindow : public ImGui_WindowBase {
        public:
            ConsoleWindow() : ImGui_WindowBase("Console") {}
            void Content() override;
            void AddMessage(std::vector<LogMessage> n);

        private:
            std::vector<LogMessage> messages = std::vector<LogMessage>();
            bool updateMessages = true;
        };
	}
}