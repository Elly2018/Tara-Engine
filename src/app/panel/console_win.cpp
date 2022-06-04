#include "console_win.h"
#include <map>
#include <glm/glm.hpp>
#include "../../engine/core/utility.h"
#include "../../editor/editor_lowlevel.h"
#include "../../editor/editor_style.h"

namespace Tara {
	namespace UI {
        const std::map<LoggerType, const char*> LogType = {
            { LoggerType::Log, "Log" },
            { LoggerType::Warning, "Warning" },
            { LoggerType::Error, "Error" },
            { LoggerType::Exception, "Exception" },
        };
        ConsoleWindow::ConsoleWindow() : ImGui_WindowBase("Console")
        {
            flag.MenuBar = true;
            tableflags.BordersInnerV = true; tableflags.BordersOuterV = true;
            tableflags.BordersOuterV = true; tableflags.ReSizeble = true;
            tableflags.RowBG = true;
            tags.push_back("Tara");
            tags.push_back("Compile");
            tags.push_back("Blueprint");
            tags.push_back("Graphics");
        }
        void ConsoleWindow::Content() {
            // We can display different type of log
            if (ImGui_BeginMenubar()) {
                DrawClear();
                DrawFilter();
                DrawTagAdding();
                DrawSearch();
                ImGui_EndMenubar();
            }
            if (tagFilter == -1)
                DrawContent();
            else
                if (tagFilter < tags.size())
                    DrawContent(tags[tagFilter]);
                else
                    DrawContent();
        }
        void ConsoleWindow::AddMessage(LogMessage n) {
            messages.push_back(n);
            updateMessages = true;
        }
        void ConsoleWindow::DrawClear()
        {
            if (ImGui_MenuItem("Clear")) {
                messages.clear();
            }
        }
        void ConsoleWindow::DrawFilter()
        {
            if (ImGui_MenuItem("Type Filter")) {
                ImGui_OpenPopup("Console Type Filter");
            }
            if (ImGui_BeginPopup("Console Type Filter")) {
                for (auto& log : LogType) {
                    bool isselect = (int32_t)log.first & typeFilter;
                    ImGui_Checkbox(log.second, &isselect);
                    if (isselect) {
                        typeFilter |= (int32_t)log.first;
                    }
                    else {
                        typeFilter &= ~(int32_t)log.first;
                    }
                }
                ImGui_EndPopup();
            }
        }
        void ConsoleWindow::DrawSearch()
        {
            ImGui_TextField("Search", &m_Search);
        }
        void ConsoleWindow::DrawTagAdding()
        {
            if (ImGui_MenuItem("Tag Filter")) {
                ImGui_OpenPopup("Console Tag Filter");
            }
            if (ImGui_BeginPopup("Console Tag Filter")) {
                if (ImGui_ColumnButton("Remove filter")) {
                    tagFilter = -1;
                }
                int32_t era = -1;
                ImGui_Column(3, false);
                for (int32_t c = 0; c < tags.size(); c++) {
                    ImGui_Text(tags[c].c_str());
                    ImGui_NextColumn();
                    if (ImGui_Button(Utility::String::FormatString("Select##Console Tag Option %s", tags[c].c_str()).c_str())) {
                        tagFilter = c;
                    }
                    ImGui_NextColumn();
                    if (ImGui_Button(Utility::String::FormatString("Delete##Console Tag Option %s", tags[c].c_str()).c_str())) {
                        if (tagFilter = c) tagFilter = -1;
                        era = c;
                    }
                    ImGui_NextColumn();
                }
                ImGui_Column(1, false);
                if (era != -1) {
                    tags.erase(std::remove(tags.begin(), tags.end(), tags[era].c_str()), tags.end());
                }
                ImGui_TextField("New Tag", &newtag);
                bool have = std::find(tags.begin(), tags.end(), newtag.c_str()) != tags.end();
                ImGui_BeginDisabled(have || newtag.size() <= 0);
                if (ImGui_ColumnButton("Add Tag")) {
                    tags.push_back(newtag);
                    newtag.clear();
                }
                ImGui_EndDisabled();
                ImGui_EndPopup();
            }
        }
        void ConsoleWindow::DrawContent(std::string tag)
        {
            if (ImGui_BeginTable("Regular Logs", 1, tableflags)) {
                ImGui_BeginChild("Regular Logs Frame", 0, 0, false);
                for (auto m : messages) {
                    if (m_Search.size() > 0 && m.message.find(m_Search) == std::string::npos) continue;
                    if (typeFilter != -1 && !((int32_t)m.type & typeFilter)) continue;
                    if (tag.size() > 0 && m.tag != tag) continue;
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
        }
	}
}