#pragma once
#include "engine/core/config.h"
#include "engine/core/logger.h"
#include "editor/editor_container.h"

namespace Tara {
	namespace UI {
        class TARA_APP_API ConsoleWindow : public ImGui_WindowBase {
        public:
            ConsoleWindow();
            void Content() override;
            void AddMessage(LogMessage n);

        private:
            void DrawClear();
            void DrawFilter();
            void DrawSearch();
            void DrawTagAdding();
            void DrawContent(std::string tag = "");

            std::vector<LogMessage> messages = std::vector<LogMessage>();
            ImGui_TableFlags tableflags = ImGui_TableFlags();
            std::vector<std::string> tags = std::vector<std::string>();
            std::string newtag = "";
            int32_t tagFilter = -1;
            int32_t typeFilter = -1;
            bool updateMessages = true;
            std::string m_Search;
        };
	}
}