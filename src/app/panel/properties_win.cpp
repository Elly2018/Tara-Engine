#include "properties_win.h"
#include "../../engine/core/utility.h"
#include "../../engine/core/scene_object/scene_object.h"
#include "../../engine/component/component.h"
#include "../../editor/editor_lowlevel.h"
#include "../../editor/component/editor_component.h"
#include "../../editor/asset/filebase.h"
#include "global_state.h"

namespace Tara {
	namespace UI {
        PropertiesWindow::PropertiesWindow() : UI::ImGui_WindowBase("Properties") {
            flags.AlwaysAutoResize = true;
        }
        void PropertiesWindow::Content() {
            using namespace FileSystem;
            UI::ImGui_BeginChild("Hierarchy Frame", 0, 0, true, flags);
            PanelGlobalState& pg = PanelGlobalState::Singleton();
            EditorComponentManager& ecomp = EditorComponentManager::Singleton();

            if (UI::ImGui_Checkbox("Debug", &pg.debug)) {
                TARA_DEBUG("Toggle Debug");
            }
            if (!pg.focusedObject) {
                UI::ImGui_EndChild();
                return;
            }

            // Scene object view
            if (static_cast<SceneObject*>(pg.focusedObject)) {
                SceneObject* so = static_cast<SceneObject*>(pg.focusedObject);
                std::vector<Component*> comps = so->GetRelateComponents<Component>();
                int32_t count = 0;
                for (auto comp : comps) {
                    count++;
                    std::string id = typeid(*comp).name();
                    Utility::String::RemoveString(id, "class ");
                    Utility::String::RemoveString(id, "Tara::");
                    if (UI::ImGui_CollapsingHeader(id.c_str())) {
                        EditorComponentBase* ed = ecomp.GetEditor(comp);
                        if (!ed) continue;
                        ed->SetComponent(comp);
                        ed->GUI();
                    }
                }
                if (ImGui_ColumnButton("Add Component", 24, 10)) {
                    ImGui_OpenPopup("Menu##Add Component");
                }
                ImGui_WindiwFlags f = ImGui_WindiwFlags();
                f.NoMove = true;
                f.NoResize = true;
                if (ImGui_BeginPopup("Menu##Add Component", f)) {
                    f.AlwaysAutoResize = true;
                    f.HorizontalScrollbar = true;
                    ImGui_TextField("search", &search);
                    if (ImGui_BeginChild("Menu##Add Component Child", 300, 200, false, f)) {
                        auto d = ecomp.GetComponents(MenuPath());
                        if (menupath.size() > 0) {
                            if (ImGui_Selectable("<...")) {
                                menupath.pop_back();
                            }
                        }
                        for (auto i : d) {
                            if (ImGui_Selectable(i.first.c_str())) {
                                if (!i.second) {
                                    menupath.push_back(i.first);
                                }
                                else {
                                    i.second->ApplyComponent(so);
                                    ImGui_ClosePopup();
                                }
                            }
                        }
                        ImGui_EndChild();
                    }
                    ImGui_EndPopup();
                }
            }
            // File object view
            else if (static_cast<FileBase*>(pg.focusedObject)) {
                FileBase* fb = static_cast<FileBase*>(pg.focusedObject);
                fb->DrawProp();
            }
            UI::ImGui_EndChild();
        }
        std::string PropertiesWindow::MenuPath()
        {
            if (menupath.size() == 0) return std::string();
            if (menupath.size() == 1) return menupath.at(0);
            std::string n = std::string();
            for (auto i : menupath) {
                n += i + "/";
            }
            n.pop_back();
            return n;
        }
	}
}