#include "hierarchy_win.h"
#include <glm/glm.hpp>
#include "../../editor/editor_lowlevel.h"
#include "../../engine/core/scene/scene.h"
#include "../../engine/component/camera.h"
#include "../../engine/core/scene_object/scene_object.h"
#include "global_state.h"

namespace Tara {
    namespace UI {
        HierarchyWindow::HierarchyWindow() : ImGui_WindowBase("Hierarchy") {
            childWinFlags.MenuBar = true;
            childWinFlags.AlwaysAutoResize = true;
            fieldPopup.UnSave = true;
            fieldPopup.NoMove = true;
            fieldPopup.AlwaysAutoResize = true;
            events.OnClick = std::bind(&HierarchyWindow::OnClickField, this, std::placeholders::_1, std::placeholders::_2);
            events.Always = std::bind(&HierarchyWindow::OnAlways, this, std::placeholders::_1);
        }
        void HierarchyWindow::Content() {
            PanelGlobalState& pg = PanelGlobalState::Singleton();
            stateIndex = -1;
            state = false;
            current = nullptr;
            startRecord = false;
            record.clear();
            for (auto s : pg.allScene) {
                if (!m_Search.count(s)) {
                    m_Search[s] = "";
                }
                if (!m_UpdateSearch.count(s)) {
                    m_UpdateSearch[s] = false;
                }
                if (!m_sceneFilteredTree.count(s)) {
                    m_sceneFilteredTree[s] = tree<SceneObject*>();
                }

                if (!s) continue;
                if (UI::ImGui_CollapsingHeader(s->Name.c_str())) {
                    UI::ImGui_BeginChild((s->Name + "##").c_str(), 0, 0, false, childWinFlags);
                    TopMenu(s);
                    UI::ImGui_Indent();

                    if (m_Search[s].size() > 0) {
                        // Filter apply
                        for (auto& eo : m_sceneFilteredTree[s]) {
                            SceneObject* so = ImGui_SceneObjectHierarchy(eo, selects, pg.focusedSceneObject, events);
                        }
                    }
                    else {
                        // Render all nodes
                        size_t c = s->TopLayerCount();
                        for (size_t i = 0; i < c; i++) {
                            SceneObject* eo = s->GetChild(i);
                            if (eo) {
                                SceneObject* so = ImGui_SceneObjectHierarchy(eo, selects, pg.focusedSceneObject, events);
                            }
                        }
                    }

                    if (pg.focusedSceneObject)
                        pg.selectCameraObject = pg.focusedSceneObject->GetRelateComponent<CameraComponent>();
                    UI::ImGui_UnIndent();
                    UI::ImGui_EndChild();

                    if (m_UpdateSearch.at(s)) {
                        m_sceneFilteredTree[s] = GetSearchTree(s);
                    }
                }
            }

            if (state) {
                switch (stateIndex) {
                case 0:
                    for (auto& i : record) {
                        if (!i) continue;
                        if (pg.focusedSceneObject == current) {
                            MultipleSelect(i, true);
                            break;
                        }

                        if ((pg.focusedSceneObject == i || current == i) && !startRecord) {
                            startRecord = true;
                        }
                        else if ((pg.focusedSceneObject == i || current == i) && startRecord) {
                            startRecord = false;
                            MultipleSelect(i, true);
                            break;
                        }

                        if (startRecord) {
                            MultipleSelect(i, true);
                        }
                    }
                    break;
                case 1:
                    MultipleSelect(current);
                    break;
                case 2:
                    selects.clear();
                    MultipleSelect(current, true);
                    pg.focusedObject = current;
                    pg.focusedSceneObject = current;
                    break;
                case 3:
                    selects.clear();
                    pg.focusedObject = nullptr;
                    pg.focusedSceneObject = nullptr;
                    break;
                }
                state = false;
            }

            if (open) {
                ImGui_OpenPopup("Menu##HierarchySceneObject");
                open = false;
            }
            if (ImGui_BeginPopup("Menu##HierarchySceneObject", fieldPopup)) {
                UI::ImGui_BeginDisabled(selects.size() > 1);
                if (ImGui_Selectable("Duplicate")) {
                    ImGui_ClosePopup();
                }
                UI::ImGui_EndDisabled();
                if (ImGui_Selectable("Remove")) {
                    EditDelete();
                    ImGui_ClosePopup();
                }
                ImGui_EndPopup();
            }
        }
        void HierarchyWindow::TopMenu(Scene* scene)
        {
            PanelGlobalState& pg = PanelGlobalState::Singleton();
            ObjectFactory& of = ObjectFactory::Singleton();
            if (UI::ImGui_BeginMenubar()) {
                if (UI::ImGui_BeginMenu("New")) {
                    if (UI::ImGui_MenuItem("Empty")) {
                        of.CreateEmpty();
                    }
                    if (UI::ImGui_MenuItem("Actor")) {
                        of.CreateActor();
                    }
                    if (UI::ImGui_MenuItem("Pawn")) {
                        of.CreatePawn();
                    }
                    if (UI::ImGui_BeginMenu("Camera")) {
                        if (UI::ImGui_MenuItem("Camera")) {
                            of.m_Viewer.CreateCamera();
                        }
                        UI::ImGui_EndMenu();
                    }
                    if (UI::ImGui_BeginMenu("Light")) {
                        if (UI::ImGui_MenuItem("Directional Light")) {
                            of.m_Lighting.CreateDirection();
                        }
                        if (UI::ImGui_MenuItem("Point Light")) {
                            of.m_Lighting.CreatePointLight();
                        }
                        UI::ImGui_EndMenu();
                    }
                    UI::ImGui_EndMenu();
                }
                if (UI::ImGui_BeginMenu("Edit")) {
                    if (UI::ImGui_MenuItem("Deselect")) {
                        pg.focusedSceneObject = nullptr;
                        pg.focusedObject = nullptr;
                    }
                    UI::ImGui_BeginDisabled(selects.size() > 1);
                    if (UI::ImGui_MenuItem("Duplicate")) {
                        
                    }
                    UI::ImGui_EndDisabled();
                    UI::ImGui_BeginDisabled(pg.focusedSceneObject == nullptr);
                    if (UI::ImGui_MenuItem("Delete")) {
                        EditDelete();
                    }
                    UI::ImGui_EndDisabled();
                    UI::ImGui_EndMenu();
                }
                m_UpdateSearch[scene] = UI::ImGui_TextField("Search", &m_Search[scene]);
                UI::ImGui_EndMenubar();
            }
        }
        void HierarchyWindow::OnClickField(SceneObject* so, MouseButton button)
        {
            if (button == MouseButton::Left) {
                if (ImGui_IsModifieKeyDown(EditorModifieKey::Shift) && so) {
                    state = true;
                    stateIndex = 0;
                }
                else if (ImGui_IsModifieKeyDown(EditorModifieKey::Ctrl) && so) {
                    state = true;
                    stateIndex = 1;
                }
                else if (!ImGui_IsModifieKeyDown(EditorModifieKey::Shift) && !ImGui_IsModifieKeyDown(EditorModifieKey::Ctrl) && so) {
                    state = true;
                    stateIndex = 2;
                }
                else if (!so) {
                    state = true;
                    stateIndex = 3;
                }
                if (state) current = so;
            }

            if (button == MouseButton::Right) {
                open = true;
            }
        }
        void HierarchyWindow::MultipleSelect(SceneObject* so)
        {
            PanelGlobalState& pg = PanelGlobalState::Singleton();

            std::vector<SceneObject*>::iterator index = std::find(selects.begin(), selects.end(), so);
            bool inside = index != selects.end();
            MultipleSelect(so, !inside, true);
        }
        void HierarchyWindow::MultipleSelect(SceneObject* so, bool state)
        {
            PanelGlobalState& pg = PanelGlobalState::Singleton();
            MultipleSelect(so, state, false);
        }
        void HierarchyWindow::MultipleSelect(SceneObject* so, bool state, bool effectGlobal)
        {
            PanelGlobalState& pg = PanelGlobalState::Singleton();

            std::vector<SceneObject*>::iterator index = std::find(selects.begin(), selects.end(), so);
            bool inside = index != selects.end();
            if (inside && !state) {
                if (selects.size() > 1) {
                    selects.erase(index, selects.end());
                    std::vector<SceneObject*>::iterator last = std::find_if(selects.begin(), selects.end(), [](SceneObject* t) -> bool { return t != nullptr; });
                    if (pg.focusedSceneObject == so && effectGlobal) {
                        pg.focusedSceneObject = *last;
                        pg.focusedObject = *last;
                    }
                }
                else {
                    selects.erase(index, selects.end());
                    if (effectGlobal) {
                        pg.focusedSceneObject = nullptr;
                        pg.focusedObject = nullptr;
                    }
                }
            }
            else if (!inside && state) {
                selects.push_back(so);
                if (effectGlobal) {
                    pg.focusedSceneObject = so;
                    pg.focusedObject = so;
                }
            }
        }

        void HierarchyWindow::OnAlways(SceneObject* so)
        {
            record.push_back(so);
        }
        
        void HierarchyWindow::EditDuplicate()
        {
        }
        void HierarchyWindow::EditDelete()
        {
            PanelGlobalState& pg = PanelGlobalState::Singleton();
            for (auto& i : selects)
            {
                delete i;
            }
            pg.focusedObject = nullptr;
            pg.focusedSceneObject = nullptr;
            selects.clear();
        }
        tree<SceneObject*> HierarchyWindow::GetSearchTree(Scene* scene)
        {
            // ! 1. Get all the match name objects first
            // All the scene objects with match search string
            std::vector<SceneObject*> matches = std::vector<SceneObject*>();
            std::string searchString = m_Search.at(scene);
            for (size_t i = 0; i < scene->Count(); i++)
            {
                SceneObject* target = scene->GetChild(i);
                if (!target) continue;
                if (target->Name.find(searchString.c_str()) != std::string::npos) {
                    matches.push_back(target);
                }
                if (target->Count() > 0) {
                    std::vector<SceneObject*> searchResult = GetSearchTree(target, searchString);
                    matches.insert(matches.end(), searchResult.begin(), searchResult.end());
                }
            }

            // ! 2. Then we form a path from the match scene objects
            // ! 3. Travel from top to bottom
            // Calcualte result tree structure.
            tree<SceneObject*>* result = new tree<SceneObject*>();
            for (auto& i : matches) {
                // Path from Bottom to top.
                std::vector<SceneObject*> path = std::vector<SceneObject*>();
                SceneObject* s_ptr = i;
                while (s_ptr)
                {
                    path.push_back(s_ptr);
                    s_ptr = s_ptr->Parent();
                }
                // Now path is top to bottom
                std::reverse(path.begin(), path.end());

                tree<SceneObject*>* t_ptr = result;

                for (auto& j : path) {
                    std::vector<tree<SceneObject*>>::iterator find_it = std::find(t_ptr->begin(), t_ptr->end(), j);
                    bool inside = find_it != t_ptr->end();
                    if (inside) {
                        t_ptr = &*find_it;
                    }
                    else {
                        tree<SceneObject*>* new_t = new tree<SceneObject*>(j);
                        t_ptr->push_back(*new_t);
                        t_ptr = new_t;
                    }
                }
            }
            TARA_DEBUG("%zu", result->count());
            return *result;
        }
        std::vector<SceneObject*> HierarchyWindow::GetSearchTree(SceneObject* so, std::string search)
        {
            std::vector<SceneObject*> result = std::vector<SceneObject*>();
            for (size_t i = 0; i < so->Count(); i++)
            {
                SceneObject* target = so->GetChild(i);
                if (!target) continue;
                if (target->Name.find(search.c_str()) != std::string::npos) {
                    result.push_back(target);
                }
                if (target->Count() > 0) {
                    std::vector<SceneObject*> searchResult = GetSearchTree(target, search);
                    result.insert(result.end(), searchResult.begin(), searchResult.end());
                }
            }
            return result;
        }
    }
}