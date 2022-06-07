#include "setting_win.h"
#include "editor/editor_lowlevel.h"
#include "editor/editor_style.h"
#include "engine/core/utility.h"

namespace Tara {
    namespace UI {
        void AppSetting_App::DrawListFields()
        {
            EditorStyle& es = EditorStyle::Singleton();
            ImGui_Text("App setting...");
        }

        AppSetting_Style::AppSetting_Style()
        {
            m_ThemeRegister = ImGui_RegisteredTheme();
        }

        void AppSetting_Style::DrawListFields()
        {
            EditorStyle& es = EditorStyle::Singleton();
            int32_t select = -1;
            std::string useTheme = "";

            for (int32_t i = 0; i < m_ThemeRegister.size(); i++) {
                std::pair<std::string, StyleColor*> reg = m_ThemeRegister[i];
                bool match = es.colors == *reg.second;
                if (match) {
                    select = i;
                    useTheme = reg.first;
                    break;
                }
            }

            if (ImGui_BeginCombo("Template", select == -1 ? "Customized" : useTheme.c_str())) {
                for (auto& reg : m_ThemeRegister) {
                    bool matchOne = reg.first == useTheme;
                    if (ImGui_Selectable(reg.first.c_str(), matchOne)) {
                        // Update setting data
                        es.SubmitStyle(*reg.second);
                        ImGui_SetItemDefaultFocus();
                    }
                }
                ImGui_EndCombo();
            }

            if (ImGui_CollapsingHeader("General")) {
                ImGui_ColorEditor4("TextColor", &es.colors.m_TextColor);
                ImGui_ColorEditor4("TextDisabled", &es.colors.m_TextDisabled);
                ImGui_ColorEditor4("Separator", &es.colors.m_Separator);
                ImGui_ColorEditor4("SeparatorHovered", &es.colors.m_SeparatorHovered);
                ImGui_ColorEditor4("SeparatorActive", &es.colors.m_SeparatorActive);
                ImGui_ColorEditor4("DockingPreview", &es.colors.m_DockingPreview);
                ImGui_ColorEditor4("DockingEmptyBg", &es.colors.m_DockingEmptyBg);
                ImGui_ColorEditor4("DragDropTarget", &es.colors.m_DragDropTarget);
                ImGui_Separator();
                ImGui_DragFloat("Alpha", &es.vars.Alpha, 0.001f, 0.1f, 1);
                ImGui_DragFloat("DisabledAlpha", &es.vars.DisabledAlpha, 0.001f, 0.1f, 1);
                ImGui_Checkbox("AntiAliasedLines", &es.vars.AntiAliasedLines);
                ImGui_Checkbox("AntiAliasedLinesUseTex", &es.vars.AntiAliasedLinesUseTex);
                ImGui_Checkbox("AntiAliasedFill", &es.vars.AntiAliasedFill);
                ImGui_DragFloat("CurveTessellationTol", &es.vars.CurveTessellationTol, 0.001f);
                ImGui_DragFloat("CircleTessellationMaxError", &es.vars.CircleTessellationMaxError, 0.001f);
                ImGui_DragVec2("MouseCursorScale", &es.vars.MouseCursorScale, 0.001f);
                ImGui_DragVec2("DisplaySafeAreaPadding", &es.vars.DisplaySafeAreaPadding, 0.001f);
            }
            if (ImGui_CollapsingHeader("Window")) {
                ImGui_ColorEditor4("WindowBg", &es.colors.m_WindowBg);
                ImGui_ColorEditor4("ChildBg", &es.colors.m_ChildBg);
                ImGui_ColorEditor4("MenuBarBg", &es.colors.m_MenuBarBg);
                ImGui_ColorEditor4("PopupBg", &es.colors.m_PopupBg);
                ImGui_ColorEditor4("NavHighlight", &es.colors.m_NavHighlight);
                ImGui_ColorEditor4("NavWindowingHighlight", &es.colors.m_NavWindowingHighlight);
                ImGui_ColorEditor4("NavWindowingDimBg", &es.colors.m_NavWindowingDimBg);
                ImGui_ColorEditor4("ModalWindowDimBg", &es.colors.m_ModalWindowDimBg);
                ImGui_ColorEditor4("ResizeGrip", &es.colors.m_ResizeGrip);
                ImGui_ColorEditor4("ResizeGripHovered", &es.colors.m_ResizeGripHovered);
                ImGui_ColorEditor4("ResizeGripActive", &es.colors.m_ResizeGripActive);
                ImGui_Separator();
                ImGui_DragVec2("WindowPadding", &es.vars.WindowPadding, 0.001f);
                ImGui_DragFloat("WindowRounding", &es.vars.WindowRounding, 0.001f);
                ImGui_DragFloat("WindowBorderSize", &es.vars.WindowBorderSize, 0.001f);
                ImGui_DragVec2("WindowMinSize", &es.vars.WindowMinSize, 0.001f);
                ImGui_DragVec2("WindowTitleAlign", &es.vars.WindowTitleAlign, 0.001f);
                ImGui_DragFloat("ChildRounding", &es.vars.ChildRounding, 0.001f);
                ImGui_DragFloat("ChildBorderSize", &es.vars.ChildBorderSize, 0.001f);
                ImGui_DragFloat("PopupRounding", &es.vars.PopupRounding, 0.001f);
                ImGui_DragFloat("PopupBorderSize", &es.vars.PopupBorderSize, 0.001f);
                ImGui_DragVec2("DisplayWindowPadding", &es.vars.DisplayWindowPadding, 0.001f);
                ImGui_DragFloat("GrabMinSize", &es.vars.GrabMinSize, 0.001f);
                ImGui_DragFloat("GrabRounding", &es.vars.GrabRounding, 0.001f);
            }
            if (ImGui_CollapsingHeader("Frame")) {
                ImGui_ColorEditor4("FrameBg", &es.colors.m_FrameBg);
                ImGui_ColorEditor4("FrameBgHovered", &es.colors.m_FrameBgHovered);
                ImGui_ColorEditor4("FrameBgActive", &es.colors.m_FrameBgActive);
                ImGui_Separator();
                ImGui_DragVec2("FramePadding", &es.vars.FramePadding, 0.001f);
                ImGui_DragFloat("FrameRounding", &es.vars.FrameRounding, 0.001f);
                ImGui_DragFloat("FrameBorderSize", &es.vars.FrameBorderSize, 0.001f);
            }
            if (ImGui_CollapsingHeader("Border")) {
                ImGui_ColorEditor4("Border", &es.colors.m_Border);
                ImGui_ColorEditor4("BorderShadow", &es.colors.m_BorderShadow);
                ImGui_Separator();
                ImGui_DragVec2("ItemSpacing", &es.vars.ItemSpacing, 0.001f);
                ImGui_DragVec2("ItemInnerSpacing", &es.vars.ItemInnerSpacing, 0.001f);
                ImGui_DragVec2("CellPadding", &es.vars.CellPadding, 0.001f);
                ImGui_DragVec2("TouchExtraPadding", &es.vars.TouchExtraPadding, 0.001f);
                ImGui_DragFloat("IndentSpacing", &es.vars.IndentSpacing, 0.001f);
                ImGui_DragFloat("ColumnsMinSpacing", &es.vars.ColumnsMinSpacing, 0.001f);
                ImGui_DragFloat("LogSliderDeadzone", &es.vars.LogSliderDeadzone, 0.001f);
            }
            if (ImGui_CollapsingHeader("Text")) {
                ImGui_ColorEditor4("TitleBg", &es.colors.m_TitleBg);
                ImGui_ColorEditor4("TitleBgActive", &es.colors.m_TitleBgActive);
                ImGui_ColorEditor4("TitleBgCollapsed", &es.colors.m_TitleBgCollapsed);
                ImGui_ColorEditor4("Header", &es.colors.m_Header);
                ImGui_ColorEditor4("HeaderHovered", &es.colors.m_HeaderHovered);
                ImGui_ColorEditor4("HeaderActive", &es.colors.m_HeaderActive);
                ImGui_ColorEditor4("TextSelectedBg", &es.colors.m_TextSelectedBg);
            }
            if (ImGui_CollapsingHeader("Scrollbar")) {
                ImGui_ColorEditor4("ScrollbarBg", &es.colors.m_ScrollbarBg);
                ImGui_ColorEditor4("ScrollbarGrab", &es.colors.m_ScrollbarGrab);
                ImGui_ColorEditor4("ScrollbarGrabHovered", &es.colors.m_ScrollbarGrabHovered);
                ImGui_ColorEditor4("ScrollbarGrabActive", &es.colors.m_ScrollbarGrabActive);
                ImGui_Separator();
                ImGui_DragFloat("ScrollbarSize", &es.vars.ScrollbarSize, 0.001f);
                ImGui_DragFloat("ScrollbarRounding", &es.vars.ScrollbarRounding, 0.001f);
            }
            if (ImGui_CollapsingHeader("Interactive")) {
                ImGui_ColorEditor4("Button", &es.colors.m_Button);
                ImGui_ColorEditor4("ButtonHovered", &es.colors.m_ButtonHovered);
                ImGui_ColorEditor4("ButtonActive", &es.colors.m_ButtonActive);
                ImGui_ColorEditor4("CheckMark", &es.colors.m_CheckMark);
                ImGui_ColorEditor4("SliderGrab", &es.colors.m_SliderGrab);
                ImGui_ColorEditor4("SliderGrabActive", &es.colors.m_SliderGrabActive);
                ImGui_Separator();
                ImGui_DragVec2("ButtonTextAlign", &es.vars.ButtonTextAlign, 0.001f);
                ImGui_DragVec2("SelectableTextAlign", &es.vars.SelectableTextAlign, 0.001f);
            }
            if (ImGui_CollapsingHeader("Tab")) {
                ImGui_ColorEditor4("Tab", &es.colors.m_Tab);
                ImGui_ColorEditor4("TabHovered", &es.colors.m_TabHovered);
                ImGui_ColorEditor4("TabActive", &es.colors.m_TabActive);
                ImGui_ColorEditor4("TabUnfocused", &es.colors.m_TabUnfocused);
                ImGui_ColorEditor4("TabUnfocusedActive", &es.colors.m_TabUnfocusedActive);
                ImGui_Separator();
                ImGui_DragFloat("TabRounding", &es.vars.TabRounding, 0.001f);
                ImGui_DragFloat("TabBorderSize", &es.vars.TabBorderSize, 0.001f);
                ImGui_DragFloat("TabMinWidthForCloseButton", &es.vars.TabMinWidthForCloseButton, 0.001f);
            }
            if (ImGui_CollapsingHeader("Table")) {
                ImGui_ColorEditor4("TableHeaderBg", &es.colors.m_TableHeaderBg);
                ImGui_ColorEditor4("TableBorderStrong", &es.colors.m_TableBorderStrong);
                ImGui_ColorEditor4("TableBorderLight", &es.colors.m_TableBorderLight);
                ImGui_ColorEditor4("TableRowBg", &es.colors.m_TableRowBg);
                ImGui_ColorEditor4("TableRowBgAlt", &es.colors.m_TableRowBgAlt);
            }
            if (ImGui_CollapsingHeader("Chart")) {
                ImGui_ColorEditor4("PlotLines", &es.colors.m_PlotLines);
                ImGui_ColorEditor4("PlotLinesHovered", &es.colors.m_PlotLinesHovered);
                ImGui_ColorEditor4("PlotHistogram", &es.colors.m_PlotHistogram);
                ImGui_ColorEditor4("PlotHistogramHovered", &es.colors.m_PlotHistogramHovered);
            }
        }

        void AppSetting_Editor::DrawListFields()
        {
            ImGui_Text("Editor setting...");
        }

        void AppSetting_Plugin::DrawListFields()
        {
            ImGui_Text("Plugin setting...");
        }

        AppSettingWindow::AppSettingWindow() : ImGui_WindowBase("Preference")
        {
            SetVisible(false);
            flag.NoDocking = true;
            flag.UnSave = true;
        }
        void AppSettingWindow::LeftMenu()
        {
            if (ImGui_Selectable("Application", m_Select == 0)) {
                m_Select = 0;
                UpdateContent();
            }
            if (ImGui_Selectable("Style", m_Select == 1)) {
                m_Select = 1;
                UpdateContent();
            }
            if (ImGui_Selectable("Editor", m_Select == 2)) {
                m_Select = 2;
                UpdateContent();
            }
            if (ImGui_Selectable("Plugin", m_Select == 3)) {
                m_Select = 3;
                UpdateContent();
            }
        }
        void AppSettingWindow::RightContent()
        {
            if (m_CurrentContent == nullptr) {
                if (m_Select < 0 || m_Select > 3) {
                    m_Select = 0;
                }
                UpdateContent();
            }
            if (m_CurrentContent) {
                m_CurrentContent->DrawListFields();
            }
        }
        void AppSettingWindow::Content()
        {
            EditorStyle& es = EditorStyle::Singleton();
            if (ImGui_Button("Save", glm::vec2(50, 0))) {
                es.Apply();
                es.Save(EDITOR_STYLE_FILE);
                ImGui_Notify("Preference", "Your setting is saved !");
            }
            ImGui_Sameline(60, 1);
            if (ImGui_Button("Load", glm::vec2(50, 0))) {
                es.Load(EDITOR_STYLE_FILE);
                es.Apply();
                ImGui_Notify("Preference", Utility::String::FormatString("Load preference from %s !", EDITOR_STYLE_FILE));
            }
            ImGui_Sameline(120, 1);
            if (ImGui_Button("Cancel", glm::vec2(50, 0))) {
                es.LoadInstance();
                SetVisible(false);
            }
            ImGui_Sameline(180, 1);
            if (ImGui_Button("Apply", glm::vec2(50, 0))) {
                es.Apply();
            }
            ImGui_Column(2, true);
            if (m_First) {
                ImGui_SetColumnWidth(0, 200);
                m_First = false;
            }
            ImGui_BeginChild("Preference Left", 0, 0, true);
            LeftMenu();
            ImGui_EndChild();
            ImGui_NextColumn();
            ImGui_BeginChild("Preference Right", 0, 0, true);
            RightContent();
            ImGui_EndChild();
            ImGui_Column(1, false);
        }
        void AppSettingWindow::SetSelect(int32_t index)
        {
            m_Select = index;
            UpdateContent();
        }
        void AppSettingWindow::UpdateContent()
        {
            if (m_CurrentContent) delete m_CurrentContent;
            switch (m_Select) {
            case 0:
                m_CurrentContent = new AppSetting_App();
                break;
            case 1:
                m_CurrentContent = new AppSetting_Style();
                break;
            case 2:
                m_CurrentContent = new AppSetting_Editor();
                break;
            case 3:
                m_CurrentContent = new AppSetting_Plugin();
                break;
            }
        }
    }
}