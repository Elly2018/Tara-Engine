#include "console_win.h"
#include <glm/glm.hpp>
#include "../../editor/editor_lowlevel.h"
#include "../../editor/editor_style.h"

namespace Tara {
	namespace UI {
        void ConsoleWindow::Content() {
            ImGui_TableFlags tableflags = ImGui_TableFlags();
            tableflags.BordersInnerV = true; tableflags.BordersOuterV = true;
            tableflags.BordersOuterV = true; tableflags.ReSizeble = true;
            tableflags.RowBG = true;
            // We can display different type of log
            if (ImGui_Button("Clear")) {
                messages.clear();
            }
            ImGui_TextField("Search", &m_Search);
            if (ImGui_BeginTabBar("ConsoleTab")) {
                if (ImGui_BeginTabitems("All Logs")) {
                    if (ImGui_BeginTable("Regular Logs", 1, tableflags)) {
                        ImGui_BeginChild("Regular Logs Frame", 0, 0, false);
                        for (auto m : messages) {
                            ImGui_TextColor(m.color);
                            ImGui_Text(m.message.c_str());
                            ImGui_PopColor();
                            ImGui_TableNextColumn();
                        }
                        // When updating, user's scroll bar will go to the bottom
                        if (updateMessages) {
                            ImGui_SetScrollHereY(0.999f);
                            updateMessages = false;
                        }
                        ImGui_EndChild();
                        ImGui_EndTable();
                    }
                    ImGui_EndTabitems();
                }
                ImGui_EndTabBar();
            }
        }
        void ConsoleWindow::AddMessage(LogMessage n) {
            messages.push_back(n);
            updateMessages = true;
        }
	}
}