#include "editor_setting.h"
#include <imgui.h>
#include "../engine/core/utility.h"

namespace Tara {
	namespace UI {
		EditorStyle* EditorStyle::m_Singleton = nullptr;

#pragma region Utility Converter
		ImVec2 ToVec2(glm::vec2 v) {
			return ImVec2(v.x, v.y);
		}
		glm::vec2 ToVec2(ImVec2 v) {
			return glm::vec2(v.x, v.y);
		}
		ImVec4 ToVec4(glm::vec4 v) {
			return ImVec4(v.x, v.y, v.z, v.w);
		}
		glm::vec4 ToVec4(ImVec4 v) {
			return glm::vec4(v.x, v.y, v.z, v.w);
		}
		ImVec4 ToVec4(glm::vec3 v) {
			return ImVec4(v.x, v.y, v.z, 1);
		}
		std::list<float_t> GetVec4List(glm::vec4 v) {
			return { v.x, v.y, v.z, v.w };
		}
		std::list<float_t> GetVec3List(glm::vec3 v) {
			return { v.x, v.y, v.z };
		}
		std::list<float_t> GetVec2List(glm::vec2 v) {
			return { v.x, v.y };
		}
		glm::vec4 ListToVec4(nlohmann::json j, const char* key) {
			if (!j.contains(key)) {
				TARA_WARNING_LEVEL("Read json error, this key does not exist: %s", 4, key);
				return glm::vec4(1);
			}
			if (!j[key].is_array()) {
				TARA_WARNING_LEVEL("Read json error, this key is not array: %s", 4, key);
				return glm::vec4(1);
			}
			glm::vec4 r(1);
			int32_t count = 0;
			for (auto& i: j[key]) {
				if (i.is_number_float()) {
					r[count] = i;
				}
				count++;
			}
			return r;
		}
		glm::vec2 ListToVec2(nlohmann::json j, const char* key) {
			if (!j.contains(key)) {
				TARA_WARNING_LEVEL("Read json error, this key does not exist: %s", 4, key);
				return glm::vec2(0);
			}
			if (!j[key].is_array()) {
				TARA_WARNING_LEVEL("Read json error, this key is not array: %s", 4, key);
				return glm::vec2(0);
			}
			glm::vec4 r(1);
			int32_t count = 0;
			for (auto& i : j[key]) {
				if (i.is_number_float()) {
					r[count] = i;
				}
				count++;
			}
			return r;
		}
#pragma endregion

		void StyleColor::Set(int32_t index, glm::vec4 v)
		{
			if (index >= COUNT || index < 0) return;

			switch (index) {
			case 0: { m_TextColor = v; break; }
			case 1: { m_TextDisabled = v; break; }
			case 2: { m_WindowBg = v; break; }
			case 3: { m_ChildBg = v; break; }
			case 4: { m_PopupBg = v; break; }
			case 5: { m_Border = v; break; }
			case 6: { m_BorderShadow = v; break; }
			case 7: { m_FrameBg = v; break; }
			case 8: { m_FrameBgHovered = v; break; }
			case 9: { m_FrameBgActive = v; break; }
			case 10: { m_TitleBg = v; break; }
			case 11: { m_TitleBgActive = v; break; }
			case 12: { m_TitleBgCollapsed = v; break; }
			case 13: { m_MenuBarBg = v; break; }
			case 14: { m_ScrollbarBg = v; break; }
			case 15: { m_ScrollbarGrab = v; break; }
			case 16: { m_ScrollbarGrabHovered = v; break; }
			case 17: { m_ScrollbarGrabActive = v; break; }
			case 18: { m_CheckMark = v; break; }
			case 19: { m_SliderGrab = v; break; }
			case 20: { m_SliderGrabActive = v; break; }
			case 21: { m_Button = v; break; }
			case 22: { m_ButtonHovered = v; break; }
			case 23: { m_ButtonActive = v; break; }
			case 24: { m_Header = v; break; }
			case 25: { m_HeaderHovered = v; break; }
			case 26: { m_HeaderActive = v; break; }
			case 27: { m_Separator = v; break; }
			case 28: { m_SeparatorHovered = v; break; }
			case 29: { m_SeparatorActive = v; break; }
			case 30: { m_ResizeGrip = v; break; }
			case 31: { m_ResizeGripHovered = v; break; }
			case 32: { m_ResizeGripActive = v; break; }
			case 33: { m_Tab = v; break; }
			case 34: { m_TabHovered = v; break; }
			case 35: { m_TabActive = v; break; }
			case 36: { m_TabUnfocused = v; break; }
			case 37: { m_TabUnfocusedActive = v; break; }
			case 38: { m_DockingPreview = v; break; }
			case 39: { m_DockingEmptyBg = v; break; }
			case 40: { m_PlotLines = v; break; }
			case 41: { m_PlotLinesHovered = v; break; }
			case 42: { m_PlotHistogram = v; break; }
			case 43: { m_PlotHistogramHovered = v; break; }
			case 44: { m_TableHeaderBg = v; break; }
			case 45: { m_TableBorderStrong = v; break; }
			case 46: { m_TableBorderLight = v; break; }
			case 47: { m_TableRowBg = v; break; }
			case 48: { m_TableRowBgAlt = v; break; }
			case 49: { m_TextSelectedBg = v; break; }
			case 50: { m_DragDropTarget = v; break; }
			case 51: { m_NavHighlight = v; break; }
			case 52: { m_NavWindowingHighlight = v; break; }
			case 53: { m_NavWindowingDimBg = v; break; }
			case 54: { m_ModalWindowDimBg = v; break; }
			}
		}
		glm::vec4 StyleColor::Get(int32_t index)
		{
			if (index >= COUNT || index < 0) return glm::vec4(1.0f);

			switch (index) {
			case 0:  { return m_TextColor; }
			case 1:  { return m_TextDisabled; }
			case 2:  { return m_WindowBg; }
			case 3:  { return m_ChildBg; }
			case 4:  { return m_PopupBg; }
			case 5:  { return m_Border; }
			case 6:  { return m_BorderShadow; }
			case 7:  { return m_FrameBg; }
			case 8:  { return m_FrameBgHovered; }
			case 9:  { return m_FrameBgActive; }
			case 10: { return m_TitleBg; }
			case 11: { return m_TitleBgActive; }
			case 12: { return m_TitleBgCollapsed; }
			case 13: { return m_MenuBarBg; }
			case 14: { return m_ScrollbarBg; }
			case 15: { return m_ScrollbarGrab; }
			case 16: { return m_ScrollbarGrabHovered; }
			case 17: { return m_ScrollbarGrabActive; }
			case 18: { return m_CheckMark; }
			case 19: { return m_SliderGrab; }
			case 20: { return m_SliderGrabActive; }
			case 21: { return m_Button; }
			case 22: { return m_ButtonHovered; }
			case 23: { return m_ButtonActive; }
			case 24: { return m_Header; }
			case 25: { return m_HeaderHovered; }
			case 26: { return m_HeaderActive; }
			case 27: { return m_Separator; }
			case 28: { return m_SeparatorHovered; }
			case 29: { return m_SeparatorActive; }
			case 30: { return m_ResizeGrip; }
			case 31: { return m_ResizeGripHovered; }
			case 32: { return m_ResizeGripActive; }
			case 33: { return m_Tab; }
			case 34: { return m_TabHovered; }
			case 35: { return m_TabActive; }
			case 36: { return m_TabUnfocused; }
			case 37: { return m_TabUnfocusedActive; }
			case 38: { return m_DockingPreview; }
			case 39: { return m_DockingEmptyBg; }
			case 40: { return m_PlotLines; }
			case 41: { return m_PlotLinesHovered; }
			case 42: { return m_PlotHistogram; }
			case 43: { return m_PlotHistogramHovered; }
			case 44: { return m_TableHeaderBg; }
			case 45: { return m_TableBorderStrong; }
			case 46: { return m_TableBorderLight; }
			case 47: { return m_TableRowBg; }
			case 48: { return m_TableRowBgAlt; }
			case 49: { return m_TextSelectedBg; }
			case 50: { return m_DragDropTarget; }
			case 51: { return m_NavHighlight; }
			case 52: { return m_NavWindowingHighlight; }
			case 53: { return m_NavWindowingDimBg; }
			case 54: { return m_ModalWindowDimBg; }
			default: { return glm::vec4(1.0f); }
			}
		}
		bool StyleColor::operator==(const StyleColor& tar)
		{
			return m_TextColor == tar.m_TextColor &&
				m_TextDisabled == tar.m_TextDisabled &&
				m_WindowBg == tar.m_WindowBg &&
				m_ChildBg == tar.m_ChildBg &&
				m_PopupBg == tar.m_PopupBg &&
				m_Border == tar.m_Border &&
				m_BorderShadow == tar.m_BorderShadow &&
				m_FrameBg == tar.m_FrameBg &&
				m_FrameBgHovered == tar.m_FrameBgHovered &&
				m_FrameBgActive == tar.m_FrameBgActive &&
				m_TitleBg == tar.m_TitleBg &&
				m_TitleBgActive == tar.m_TitleBgActive &&
				m_TitleBgCollapsed == tar.m_TitleBgCollapsed &&
				m_MenuBarBg == tar.m_MenuBarBg &&
				m_ScrollbarBg == tar.m_ScrollbarBg &&
				m_ScrollbarGrab == tar.m_ScrollbarGrab &&
				m_ScrollbarGrabHovered == tar.m_ScrollbarGrabHovered &&
				m_ScrollbarGrabActive == tar.m_ScrollbarGrabActive &&
				m_CheckMark == tar.m_CheckMark &&
				m_SliderGrab == tar.m_SliderGrab &&
				m_SliderGrabActive == tar.m_SliderGrabActive &&
				m_Button == tar.m_Button &&
				m_ButtonHovered == tar.m_ButtonHovered &&
				m_ButtonActive == tar.m_ButtonActive &&
				m_Header == tar.m_Header &&
				m_HeaderHovered == tar.m_HeaderHovered &&
				m_HeaderActive == tar.m_HeaderActive &&
				m_Separator == tar.m_Separator &&
				m_SeparatorHovered == tar.m_SeparatorHovered &&
				m_SeparatorActive == tar.m_SeparatorActive &&
				m_ResizeGrip == tar.m_ResizeGrip &&
				m_ResizeGripHovered == tar.m_ResizeGripHovered &&
				m_ResizeGripActive == tar.m_ResizeGripActive &&
				m_Tab == tar.m_Tab &&
				m_TabHovered == tar.m_TabHovered &&
				m_TabActive == tar.m_TabActive &&
				m_TabUnfocused == tar.m_TabUnfocused &&
				m_TabUnfocusedActive == tar.m_TabUnfocusedActive &&
				m_DockingPreview == tar.m_DockingPreview &&
				m_DockingEmptyBg == tar.m_DockingEmptyBg &&
				m_PlotLines == tar.m_PlotLines &&
				m_PlotLinesHovered == tar.m_PlotLinesHovered &&
				m_PlotHistogram == tar.m_PlotHistogram &&
				m_PlotHistogramHovered == tar.m_PlotHistogramHovered &&
				m_TableHeaderBg == tar.m_TableHeaderBg &&
				m_TableBorderStrong == tar.m_TableBorderStrong &&
				m_TableBorderLight == tar.m_TableBorderLight &&
				m_TableRowBg == tar.m_TableRowBg &&
				m_TableRowBgAlt == tar.m_TableRowBgAlt &&
				m_TextSelectedBg == tar.m_TextSelectedBg &&
				m_DragDropTarget == tar.m_DragDropTarget &&
				m_NavHighlight == tar.m_NavHighlight &&
				m_NavWindowingHighlight == tar.m_NavWindowingHighlight &&
				m_NavWindowingDimBg == tar.m_NavWindowingDimBg &&
				m_ModalWindowDimBg == tar.m_ModalWindowDimBg;
		}
		bool StyleColor::operator!=(const StyleColor& tar)
		{
			return m_TextColor != tar.m_TextColor ||
				m_TextDisabled != tar.m_TextDisabled ||
				m_WindowBg != tar.m_WindowBg ||
				m_ChildBg != tar.m_ChildBg ||
				m_PopupBg != tar.m_PopupBg ||
				m_Border != tar.m_Border ||
				m_BorderShadow != tar.m_BorderShadow ||
				m_FrameBg != tar.m_FrameBg ||
				m_FrameBgHovered != tar.m_FrameBgHovered ||
				m_FrameBgActive != tar.m_FrameBgActive ||
				m_TitleBg != tar.m_TitleBg ||
				m_TitleBgActive != tar.m_TitleBgActive ||
				m_TitleBgCollapsed != tar.m_TitleBgCollapsed ||
				m_MenuBarBg != tar.m_MenuBarBg ||
				m_ScrollbarBg != tar.m_ScrollbarBg ||
				m_ScrollbarGrab != tar.m_ScrollbarGrab ||
				m_ScrollbarGrabHovered != tar.m_ScrollbarGrabHovered ||
				m_ScrollbarGrabActive != tar.m_ScrollbarGrabActive ||
				m_CheckMark != tar.m_CheckMark ||
				m_SliderGrab != tar.m_SliderGrab ||
				m_SliderGrabActive != tar.m_SliderGrabActive ||
				m_Button != tar.m_Button ||
				m_ButtonHovered != tar.m_ButtonHovered ||
				m_ButtonActive != tar.m_ButtonActive ||
				m_Header != tar.m_Header ||
				m_HeaderHovered != tar.m_HeaderHovered ||
				m_HeaderActive != tar.m_HeaderActive ||
				m_Separator != tar.m_Separator ||
				m_SeparatorHovered != tar.m_SeparatorHovered ||
				m_SeparatorActive != tar.m_SeparatorActive ||
				m_ResizeGrip != tar.m_ResizeGrip ||
				m_ResizeGripHovered != tar.m_ResizeGripHovered ||
				m_ResizeGripActive != tar.m_ResizeGripActive ||
				m_Tab != tar.m_Tab ||
				m_TabHovered != tar.m_TabHovered ||
				m_TabActive != tar.m_TabActive ||
				m_TabUnfocused != tar.m_TabUnfocused ||
				m_TabUnfocusedActive != tar.m_TabUnfocusedActive ||
				m_DockingPreview != tar.m_DockingPreview ||
				m_DockingEmptyBg != tar.m_DockingEmptyBg ||
				m_PlotLines != tar.m_PlotLines ||
				m_PlotLinesHovered != tar.m_PlotLinesHovered ||
				m_PlotHistogram != tar.m_PlotHistogram ||
				m_PlotHistogramHovered != tar.m_PlotHistogramHovered ||
				m_TableHeaderBg != tar.m_TableHeaderBg ||
				m_TableBorderStrong != tar.m_TableBorderStrong ||
				m_TableBorderLight != tar.m_TableBorderLight ||
				m_TableRowBg != tar.m_TableRowBg ||
				m_TableRowBgAlt != tar.m_TableRowBgAlt ||
				m_TextSelectedBg != tar.m_TextSelectedBg ||
				m_DragDropTarget != tar.m_DragDropTarget ||
				m_NavHighlight != tar.m_NavHighlight ||
				m_NavWindowingHighlight != tar.m_NavWindowingHighlight ||
				m_NavWindowingDimBg != tar.m_NavWindowingDimBg ||
				m_ModalWindowDimBg != tar.m_ModalWindowDimBg;
		}

		bool StyleVar::operator==(const StyleVar& tar)
		{
			return tar.Alpha == Alpha &&
				tar.DisabledAlpha == DisabledAlpha &&
				tar.WindowPadding == WindowPadding &&
				tar.WindowRounding == WindowRounding &&
				tar.WindowBorderSize == WindowBorderSize &&
				tar.WindowMinSize == WindowMinSize &&
				tar.WindowTitleAlign == WindowTitleAlign &&
				tar.WindowMenuButtonPosition == WindowMenuButtonPosition &&
				tar.ChildRounding == ChildRounding &&
				tar.ChildBorderSize == ChildBorderSize &&
				tar.PopupRounding == PopupRounding &&
				tar.PopupBorderSize == PopupBorderSize &&
				tar.FramePadding == FramePadding &&
				tar.FrameRounding == FrameRounding &&
				tar.FrameBorderSize == FrameBorderSize &&
				tar.ItemSpacing == ItemSpacing &&
				tar.ItemInnerSpacing == ItemInnerSpacing &&
				tar.CellPadding == CellPadding &&
				tar.TouchExtraPadding == TouchExtraPadding &&
				tar.IndentSpacing == IndentSpacing &&
				tar.ColumnsMinSpacing == ColumnsMinSpacing &&
				tar.ScrollbarSize == ScrollbarSize &&
				tar.ScrollbarRounding == ScrollbarRounding &&
				tar.GrabMinSize == GrabMinSize &&
				tar.GrabRounding == GrabRounding &&
				tar.LogSliderDeadzone == LogSliderDeadzone &&
				tar.TabRounding == TabRounding &&
				tar.TabBorderSize == TabBorderSize &&
				tar.TabMinWidthForCloseButton == TabMinWidthForCloseButton &&
				tar.ColorButtonPosition == ColorButtonPosition &&
				tar.ButtonTextAlign == ButtonTextAlign &&
				tar.SelectableTextAlign == SelectableTextAlign &&
				tar.DisplayWindowPadding == DisplayWindowPadding &&
				tar.DisplaySafeAreaPadding == DisplaySafeAreaPadding &&
				tar.MouseCursorScale == MouseCursorScale &&
				tar.AntiAliasedLines == AntiAliasedLines &&
				tar.AntiAliasedLinesUseTex == AntiAliasedLinesUseTex &&
				tar.AntiAliasedFill == AntiAliasedFill &&
				tar.CurveTessellationTol == CurveTessellationTol &&
				tar.CircleTessellationMaxError == CircleTessellationMaxError;
		}
		bool StyleVar::operator!=(const StyleVar& tar)
		{
			return tar.Alpha != Alpha ||
				tar.DisabledAlpha != DisabledAlpha ||
				tar.WindowPadding != WindowPadding ||
				tar.WindowRounding != WindowRounding ||
				tar.WindowBorderSize != WindowBorderSize ||
				tar.WindowMinSize != WindowMinSize ||
				tar.WindowTitleAlign != WindowTitleAlign ||
				tar.WindowMenuButtonPosition != WindowMenuButtonPosition ||
				tar.ChildRounding != ChildRounding ||
				tar.ChildBorderSize != ChildBorderSize ||
				tar.PopupRounding != PopupRounding ||
				tar.PopupBorderSize != PopupBorderSize ||
				tar.FramePadding != FramePadding ||
				tar.FrameRounding != FrameRounding ||
				tar.FrameBorderSize != FrameBorderSize ||
				tar.ItemSpacing != ItemSpacing ||
				tar.ItemInnerSpacing != ItemInnerSpacing ||
				tar.CellPadding != CellPadding ||
				tar.TouchExtraPadding != TouchExtraPadding ||
				tar.IndentSpacing != IndentSpacing ||
				tar.ColumnsMinSpacing != ColumnsMinSpacing ||
				tar.ScrollbarSize != ScrollbarSize ||
				tar.ScrollbarRounding != ScrollbarRounding ||
				tar.GrabMinSize != GrabMinSize ||
				tar.GrabRounding != GrabRounding ||
				tar.LogSliderDeadzone != LogSliderDeadzone ||
				tar.TabRounding != TabRounding ||
				tar.TabBorderSize != TabBorderSize ||
				tar.TabMinWidthForCloseButton != TabMinWidthForCloseButton ||
				tar.ColorButtonPosition != ColorButtonPosition ||
				tar.ButtonTextAlign != ButtonTextAlign ||
				tar.SelectableTextAlign != SelectableTextAlign ||
				tar.DisplayWindowPadding != DisplayWindowPadding ||
				tar.DisplaySafeAreaPadding != DisplaySafeAreaPadding ||
				tar.MouseCursorScale != MouseCursorScale ||
				tar.AntiAliasedLines != AntiAliasedLines ||
				tar.AntiAliasedLinesUseTex != AntiAliasedLinesUseTex ||
				tar.AntiAliasedFill != AntiAliasedFill ||
				tar.CurveTessellationTol != CurveTessellationTol ||
				tar.CircleTessellationMaxError != CircleTessellationMaxError;
		}

		EditorStyle& Tara::UI::EditorStyle::Singleton()
		{
			if (!m_Singleton) m_Singleton = new EditorStyle();
			return *m_Singleton;
		}
		bool EditorStyle::Load(const char* filename)
		{
			using namespace nlohmann;
			if (!Utility::File::Exist(filename)) {
				TARA_ERROR_LEVEL("Application style setting does not exist: %s", 4, filename);
				return false;
			}
			json root = Utility::Json::ReadBson(filename);
			if (!root.contains("colors") || !root.contains("vars")) {
				TARA_ERROR_LEVEL("Application style setting format error", 4);
				return false;
			}
			json color_element = root["colors"];
			json var_element = root["vars"];

			LoadColor(color_element);
			LoadVar(var_element);

			return true;
		}
		bool EditorStyle::Save(const char* dest)
		{
			using namespace nlohmann;
			if (Utility::File::Exist(dest)) {
				remove(dest);
			}
			json root;
			root["colors"] = SaveColor();
			root["vars"] = SaveVar();
			Utility::Json::SaveBson(dest, root);
			return true;
		}
		bool EditorStyle::Apply()
		{
			bool a1 = ApplyStyle();
			bool a2 = ApplyVar();
			return a1 && a2;
		}
		bool EditorStyle::ApplyStyle()
		{
			ImGuiStyle& style = ImGui::GetStyle();
			style.Colors[ImGuiCol_Text] = ToVec4(colors.m_TextColor);
			style.Colors[ImGuiCol_TextDisabled] = ToVec4(colors.m_TextDisabled);
			style.Colors[ImGuiCol_WindowBg] = ToVec4(colors.m_WindowBg);
			style.Colors[ImGuiCol_ChildBg] = ToVec4(colors.m_ChildBg);
			style.Colors[ImGuiCol_PopupBg] = ToVec4(colors.m_PopupBg);
			style.Colors[ImGuiCol_Border] = ToVec4(colors.m_Border);
			style.Colors[ImGuiCol_BorderShadow] = ToVec4(colors.m_BorderShadow);
			style.Colors[ImGuiCol_FrameBg] = ToVec4(colors.m_FrameBg);
			style.Colors[ImGuiCol_FrameBgHovered] = ToVec4(colors.m_FrameBgHovered);
			style.Colors[ImGuiCol_FrameBgActive] = ToVec4(colors.m_FrameBgActive);
			style.Colors[ImGuiCol_TitleBg] = ToVec4(colors.m_TitleBg);
			style.Colors[ImGuiCol_TitleBgActive] = ToVec4(colors.m_TitleBgActive);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ToVec4(colors.m_TitleBgCollapsed);
			style.Colors[ImGuiCol_MenuBarBg] = ToVec4(colors.m_MenuBarBg);
			style.Colors[ImGuiCol_ScrollbarBg] = ToVec4(colors.m_ScrollbarBg);
			style.Colors[ImGuiCol_ScrollbarGrab] = ToVec4(colors.m_ScrollbarGrab);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] = ToVec4(colors.m_ScrollbarGrabHovered);
			style.Colors[ImGuiCol_ScrollbarGrabActive] = ToVec4(colors.m_ScrollbarGrabActive);
			style.Colors[ImGuiCol_CheckMark] = ToVec4(colors.m_CheckMark);
			style.Colors[ImGuiCol_SliderGrab] = ToVec4(colors.m_SliderGrab);
			style.Colors[ImGuiCol_SliderGrabActive] = ToVec4(colors.m_SliderGrabActive);
			style.Colors[ImGuiCol_Button] = ToVec4(colors.m_Button);
			style.Colors[ImGuiCol_ButtonHovered] = ToVec4(colors.m_ButtonHovered);
			style.Colors[ImGuiCol_ButtonActive] = ToVec4(colors.m_ButtonActive);
			style.Colors[ImGuiCol_Header] = ToVec4(colors.m_Header);
			style.Colors[ImGuiCol_HeaderHovered] = ToVec4(colors.m_HeaderHovered);
			style.Colors[ImGuiCol_HeaderActive] = ToVec4(colors.m_HeaderActive);
			style.Colors[ImGuiCol_Separator] = ToVec4(colors.m_Separator);
			style.Colors[ImGuiCol_SeparatorHovered] = ToVec4(colors.m_SeparatorHovered);
			style.Colors[ImGuiCol_SeparatorActive] = ToVec4(colors.m_SeparatorActive);
			style.Colors[ImGuiCol_ResizeGrip] = ToVec4(colors.m_ResizeGrip);
			style.Colors[ImGuiCol_ResizeGripHovered] = ToVec4(colors.m_ResizeGripHovered);
			style.Colors[ImGuiCol_ResizeGripActive] = ToVec4(colors.m_ResizeGripActive);
			style.Colors[ImGuiCol_Tab] = ToVec4(colors.m_Tab);
			style.Colors[ImGuiCol_TabHovered] = ToVec4(colors.m_TabHovered);
			style.Colors[ImGuiCol_TabActive] = ToVec4(colors.m_TabActive);
			style.Colors[ImGuiCol_TabUnfocused] = ToVec4(colors.m_TabUnfocused);
			style.Colors[ImGuiCol_TabUnfocusedActive] = ToVec4(colors.m_TabUnfocusedActive);
			style.Colors[ImGuiCol_DockingPreview] = ToVec4(colors.m_DockingPreview);
			style.Colors[ImGuiCol_DockingEmptyBg] = ToVec4(colors.m_DockingEmptyBg);
			style.Colors[ImGuiCol_PlotLines] = ToVec4(colors.m_PlotLines);
			style.Colors[ImGuiCol_PlotLinesHovered] = ToVec4(colors.m_PlotLinesHovered);
			style.Colors[ImGuiCol_PlotHistogram] = ToVec4(colors.m_PlotHistogram);
			style.Colors[ImGuiCol_PlotHistogramHovered] = ToVec4(colors.m_PlotHistogramHovered);
			style.Colors[ImGuiCol_TableHeaderBg] = ToVec4(colors.m_TableHeaderBg);
			style.Colors[ImGuiCol_TableBorderStrong] = ToVec4(colors.m_TableBorderStrong);
			style.Colors[ImGuiCol_TableBorderLight] = ToVec4(colors.m_TableBorderLight);
			style.Colors[ImGuiCol_TableRowBg] = ToVec4(colors.m_TableRowBg);
			style.Colors[ImGuiCol_TableRowBgAlt] = ToVec4(colors.m_TableRowBgAlt);
			style.Colors[ImGuiCol_TextSelectedBg] = ToVec4(colors.m_TextSelectedBg);
			style.Colors[ImGuiCol_DragDropTarget] = ToVec4(colors.m_DragDropTarget);
			style.Colors[ImGuiCol_NavHighlight] = ToVec4(colors.m_NavHighlight);
			style.Colors[ImGuiCol_NavWindowingHighlight] = ToVec4(colors.m_NavWindowingHighlight);
			style.Colors[ImGuiCol_NavWindowingDimBg] = ToVec4(colors.m_NavWindowingDimBg);
			style.Colors[ImGuiCol_ModalWindowDimBg] = ToVec4(colors.m_ModalWindowDimBg);
			return true;
		}
		bool EditorStyle::SubmitStyle(StyleColor col)
		{
			colors.m_TextColor = col.m_TextColor;
			colors.m_TextDisabled = col.m_TextDisabled;
			colors.m_WindowBg = col.m_WindowBg;
			colors.m_ChildBg = col.m_ChildBg;
			colors.m_PopupBg = col.m_PopupBg;
			colors.m_Border = col.m_Border;
			colors.m_BorderShadow = col.m_BorderShadow;
			colors.m_FrameBg = col.m_FrameBg;
			colors.m_FrameBgHovered = col.m_FrameBgHovered;
			colors.m_FrameBgActive = col.m_FrameBgActive;
			colors.m_TitleBg = col.m_TitleBg;
			colors.m_TitleBgActive = col.m_TitleBgActive;
			colors.m_TitleBgCollapsed = col.m_TitleBgCollapsed;
			colors.m_MenuBarBg = col.m_MenuBarBg;
			colors.m_ScrollbarBg = col.m_ScrollbarBg;
			colors.m_ScrollbarGrab = col.m_ScrollbarGrab;
			colors.m_ScrollbarGrabHovered = col.m_ScrollbarGrabHovered;
			colors.m_ScrollbarGrabActive = col.m_ScrollbarGrabActive;
			colors.m_CheckMark = col.m_CheckMark;
			colors.m_SliderGrab = col.m_SliderGrab;
			colors.m_SliderGrabActive = col.m_SliderGrabActive;
			colors.m_Button = col.m_Button;
			colors.m_ButtonHovered = col.m_ButtonHovered;
			colors.m_ButtonActive = col.m_ButtonActive;
			colors.m_Header = col.m_Header;
			colors.m_HeaderHovered = col.m_HeaderHovered;
			colors.m_HeaderActive = col.m_HeaderActive;
			colors.m_Separator = col.m_Separator;
			colors.m_SeparatorHovered = col.m_SeparatorHovered;
			colors.m_SeparatorActive = col.m_SeparatorActive;
			colors.m_ResizeGrip = col.m_ResizeGrip;
			colors.m_ResizeGripHovered = col.m_ResizeGripHovered;
			colors.m_ResizeGripActive = col.m_ResizeGripActive;
			colors.m_Tab = col.m_Tab;
			colors.m_TabHovered = col.m_TabHovered;
			colors.m_TabActive = col.m_TabActive;
			colors.m_TabUnfocused = col.m_TabUnfocused;
			colors.m_TabUnfocusedActive = col.m_TabUnfocusedActive;
			colors.m_DockingPreview = col.m_DockingPreview;
			colors.m_DockingEmptyBg = col.m_DockingEmptyBg;
			colors.m_PlotLines = col.m_PlotLines;
			colors.m_PlotLinesHovered = col.m_PlotLinesHovered;
			colors.m_PlotHistogram = col.m_PlotHistogram;
			colors.m_PlotHistogramHovered = col.m_PlotHistogramHovered;
			colors.m_TableHeaderBg = col.m_TableHeaderBg;
			colors.m_TableBorderStrong = col.m_TableBorderStrong;
			colors.m_TableBorderLight = col.m_TableBorderLight;
			colors.m_TableRowBg = col.m_TableRowBg;
			colors.m_TableRowBgAlt = col.m_TableRowBgAlt;
			colors.m_TextSelectedBg = col.m_TextSelectedBg;
			colors.m_DragDropTarget = col.m_DragDropTarget;
			colors.m_NavHighlight = col.m_NavHighlight;
			colors.m_NavWindowingHighlight = col.m_NavWindowingHighlight;
			colors.m_NavWindowingDimBg = col.m_NavWindowingDimBg;
			colors.m_ModalWindowDimBg = col.m_ModalWindowDimBg;

			return true;
		}
		bool EditorStyle::ApplyVar()
		{
			ImGuiStyle& style = ImGui::GetStyle();
			style.Alpha = vars.Alpha;
			style.DisabledAlpha = vars.DisabledAlpha;
			style.WindowPadding = ToVec2(vars.WindowPadding);
			style.WindowRounding = vars.WindowRounding;
			style.WindowBorderSize = vars.WindowBorderSize;
			style.WindowMinSize = ToVec2(vars.WindowMinSize);
			style.WindowTitleAlign = ToVec2(vars.WindowTitleAlign);
			style.WindowMenuButtonPosition = (int32_t)vars.WindowMenuButtonPosition;
			style.ChildRounding = vars.ChildRounding;
			style.ChildBorderSize = vars.ChildBorderSize;
			style.PopupRounding = vars.PopupRounding;
			style.PopupBorderSize = vars.PopupBorderSize;
			style.FramePadding = ToVec2(vars.FramePadding);
			style.FrameRounding = vars.FrameRounding;
			style.FrameBorderSize = vars.FrameBorderSize;
			style.ItemSpacing = ToVec2(vars.ItemSpacing);
			style.ItemInnerSpacing = ToVec2(vars.ItemInnerSpacing);
			style.CellPadding = ToVec2(vars.CellPadding);
			style.TouchExtraPadding = ToVec2(vars.TouchExtraPadding);
			style.IndentSpacing = vars.IndentSpacing;
			style.ColumnsMinSpacing = vars.ColumnsMinSpacing;
			style.ScrollbarSize = vars.ScrollbarSize;
			style.ScrollbarRounding = vars.ScrollbarRounding;
			style.GrabMinSize = vars.GrabMinSize;
			style.GrabRounding = vars.GrabRounding;
			style.LogSliderDeadzone = vars.LogSliderDeadzone;
			style.TabRounding = vars.TabRounding;
			style.TabBorderSize = vars.TabBorderSize;
			style.TabMinWidthForCloseButton = vars.TabMinWidthForCloseButton;
			style.ColorButtonPosition = (int32_t)vars.ColorButtonPosition;
			style.ButtonTextAlign = ToVec2(vars.ButtonTextAlign);
			style.SelectableTextAlign = ToVec2(vars.SelectableTextAlign);
			style.DisplayWindowPadding = ToVec2(vars.DisplayWindowPadding);
			style.DisplaySafeAreaPadding = ToVec2(vars.DisplaySafeAreaPadding);
			style.MouseCursorScale = vars.MouseCursorScale;
			style.AntiAliasedLines = vars.AntiAliasedLines;
			style.AntiAliasedLinesUseTex = vars.AntiAliasedLinesUseTex;
			style.AntiAliasedFill = vars.AntiAliasedFill;
			style.CurveTessellationTol = vars.CurveTessellationTol;
			style.CircleTessellationMaxError = vars.CircleTessellationMaxError;
			return true;
		}
		bool EditorStyle::SubmitVar(StyleVar v)
		{
			return true;
		}
		void EditorStyle::LoadInstance()
		{
			ImGuiStyle& style = ImGui::GetStyle();
			vars.Alpha = style.Alpha;
			vars.Alpha = style.Alpha;
			vars.DisabledAlpha = style.DisabledAlpha;
			vars.WindowPadding = ToVec2(style.WindowPadding);
			vars.WindowRounding = style.WindowRounding;
			vars.WindowBorderSize = style.WindowBorderSize;
			vars.WindowMinSize = ToVec2(style.WindowMinSize);
			vars.WindowTitleAlign = ToVec2(style.WindowTitleAlign);
			vars.WindowMenuButtonPosition = (Direction)style.WindowMenuButtonPosition;
			vars.ChildRounding = style.ChildRounding;
			vars.ChildBorderSize = style.ChildBorderSize;
			vars.PopupRounding = style.PopupRounding;
			vars.PopupBorderSize = style.PopupBorderSize;
			vars.FramePadding = ToVec2(style.FramePadding);
			vars.FrameRounding = style.FrameRounding;
			vars.FrameBorderSize = style.FrameBorderSize;
			vars.ItemSpacing = ToVec2(style.ItemSpacing);
			vars.ItemInnerSpacing = ToVec2(style.ItemInnerSpacing);
			vars.CellPadding = ToVec2(style.CellPadding);
			vars.TouchExtraPadding = ToVec2(style.TouchExtraPadding);
			vars.IndentSpacing = style.IndentSpacing;
			vars.ColumnsMinSpacing = style.ColumnsMinSpacing;
			vars.ScrollbarSize = style.ScrollbarSize;
			vars.ScrollbarRounding = style.ScrollbarRounding;
			vars.GrabMinSize = style.GrabMinSize;
			vars.GrabRounding = style.GrabRounding;
			vars.LogSliderDeadzone = style.LogSliderDeadzone;
			vars.TabRounding = style.TabRounding;
			vars.TabBorderSize = style.TabBorderSize;
			vars.TabMinWidthForCloseButton = style.TabMinWidthForCloseButton;
			vars.ColorButtonPosition = (Direction)style.ColorButtonPosition;
			vars.ButtonTextAlign = ToVec2(style.ButtonTextAlign);
			vars.SelectableTextAlign = ToVec2(style.SelectableTextAlign);
			vars.DisplayWindowPadding = ToVec2(style.DisplayWindowPadding);
			vars.DisplaySafeAreaPadding = ToVec2(style.DisplaySafeAreaPadding);
			vars.MouseCursorScale = style.MouseCursorScale;
			vars.AntiAliasedLines = style.AntiAliasedLines;
			vars.AntiAliasedLinesUseTex = style.AntiAliasedLinesUseTex;
			vars.AntiAliasedFill = style.AntiAliasedFill;
			vars.CurveTessellationTol = style.CurveTessellationTol;
			vars.CircleTessellationMaxError = style.CircleTessellationMaxError;

			colors.m_TextColor = ToVec4(style.Colors[ImGuiCol_Text]);
			colors.m_TextDisabled = ToVec4(style.Colors[ImGuiCol_TextDisabled]);
			colors.m_WindowBg = ToVec4(style.Colors[ImGuiCol_WindowBg]);
			colors.m_ChildBg = ToVec4(style.Colors[ImGuiCol_ChildBg]);
			colors.m_PopupBg = ToVec4(style.Colors[ImGuiCol_PopupBg]);
			colors.m_Border = ToVec4(style.Colors[ImGuiCol_Border]);
			colors.m_BorderShadow = ToVec4(style.Colors[ImGuiCol_BorderShadow]);
			colors.m_FrameBg = ToVec4(style.Colors[ImGuiCol_FrameBg]);
			colors.m_FrameBgHovered = ToVec4(style.Colors[ImGuiCol_FrameBgHovered]);
			colors.m_FrameBgActive = ToVec4(style.Colors[ImGuiCol_FrameBgActive]);
			colors.m_TitleBg = ToVec4(style.Colors[ImGuiCol_TitleBg]);
			colors.m_TitleBgActive = ToVec4(style.Colors[ImGuiCol_TitleBgActive]);
			colors.m_TitleBgCollapsed = ToVec4(style.Colors[ImGuiCol_TitleBgCollapsed]);
			colors.m_MenuBarBg = ToVec4(style.Colors[ImGuiCol_MenuBarBg]);
			colors.m_ScrollbarBg = ToVec4(style.Colors[ImGuiCol_ScrollbarBg]);
			colors.m_ScrollbarGrab = ToVec4(style.Colors[ImGuiCol_ScrollbarGrab]);
			colors.m_ScrollbarGrabHovered = ToVec4(style.Colors[ImGuiCol_ScrollbarGrabHovered]);
			colors.m_ScrollbarGrabActive = ToVec4(style.Colors[ImGuiCol_ScrollbarGrabActive]);
			colors.m_CheckMark = ToVec4(style.Colors[ImGuiCol_CheckMark]);
			colors.m_SliderGrab = ToVec4(style.Colors[ImGuiCol_SliderGrab]);
			colors.m_SliderGrabActive = ToVec4(style.Colors[ImGuiCol_SliderGrabActive]);
			colors.m_Button = ToVec4(style.Colors[ImGuiCol_Button]);
			colors.m_ButtonHovered = ToVec4(style.Colors[ImGuiCol_ButtonHovered]);
			colors.m_ButtonActive = ToVec4(style.Colors[ImGuiCol_ButtonActive]);
			colors.m_Header = ToVec4(style.Colors[ImGuiCol_Header]);
			colors.m_HeaderHovered = ToVec4(style.Colors[ImGuiCol_HeaderHovered]);
			colors.m_HeaderActive = ToVec4(style.Colors[ImGuiCol_HeaderActive]);
			colors.m_Separator = ToVec4(style.Colors[ImGuiCol_Separator]);
			colors.m_SeparatorHovered = ToVec4(style.Colors[ImGuiCol_SeparatorHovered]);
			colors.m_SeparatorActive = ToVec4(style.Colors[ImGuiCol_SeparatorActive]);
			colors.m_ResizeGrip = ToVec4(style.Colors[ImGuiCol_ResizeGrip]);
			colors.m_ResizeGripHovered = ToVec4(style.Colors[ImGuiCol_ResizeGripHovered]);
			colors.m_ResizeGripActive = ToVec4(style.Colors[ImGuiCol_ResizeGripActive]);
			colors.m_Tab = ToVec4(style.Colors[ImGuiCol_Tab]);
			colors.m_TabHovered = ToVec4(style.Colors[ImGuiCol_TabHovered]);
			colors.m_TabActive = ToVec4(style.Colors[ImGuiCol_TabActive]);
			colors.m_TabUnfocused = ToVec4(style.Colors[ImGuiCol_TabUnfocused]);
			colors.m_TabUnfocusedActive = ToVec4(style.Colors[ImGuiCol_TabUnfocusedActive]);
			colors.m_DockingPreview = ToVec4(style.Colors[ImGuiCol_DockingPreview]);
			colors.m_DockingEmptyBg = ToVec4(style.Colors[ImGuiCol_DockingEmptyBg]);
			colors.m_PlotLines = ToVec4(style.Colors[ImGuiCol_PlotLines]);
			colors.m_PlotLinesHovered = ToVec4(style.Colors[ImGuiCol_PlotLinesHovered]);
			colors.m_PlotHistogram = ToVec4(style.Colors[ImGuiCol_PlotHistogram]);
			colors.m_PlotHistogramHovered = ToVec4(style.Colors[ImGuiCol_PlotHistogramHovered]);
			colors.m_TableHeaderBg = ToVec4(style.Colors[ImGuiCol_TableHeaderBg]);
			colors.m_TableBorderStrong = ToVec4(style.Colors[ImGuiCol_TableBorderStrong]);
			colors.m_TableBorderLight = ToVec4(style.Colors[ImGuiCol_TableBorderLight]);
			colors.m_TableRowBg = ToVec4(style.Colors[ImGuiCol_TableRowBg]);
			colors.m_TableRowBgAlt = ToVec4(style.Colors[ImGuiCol_TableRowBgAlt]);
			colors.m_TextSelectedBg = ToVec4(style.Colors[ImGuiCol_TextSelectedBg]);
			colors.m_DragDropTarget = ToVec4(style.Colors[ImGuiCol_DragDropTarget]);
			colors.m_NavHighlight = ToVec4(style.Colors[ImGuiCol_NavHighlight]);
			colors.m_NavWindowingHighlight = ToVec4(style.Colors[ImGuiCol_NavWindowingHighlight]);
			colors.m_NavWindowingDimBg = ToVec4(style.Colors[ImGuiCol_NavWindowingDimBg]);
			colors.m_ModalWindowDimBg = ToVec4(style.Colors[ImGuiCol_ModalWindowDimBg]);
		}

		nlohmann::json EditorStyle::SaveColor()
		{
			using namespace nlohmann;
			json root;
			root["TextColor"] = GetVec4List(colors.m_TextColor);
			root["TextDisabled"] = GetVec4List(colors.m_TextDisabled);
			root["WindowBg"] = GetVec4List(colors.m_WindowBg);
			root["ChildBg"] = GetVec4List(colors.m_ChildBg);
			root["PopupBg"] = GetVec4List(colors.m_PopupBg);
			root["Border"] = GetVec4List(colors.m_Border);
			root["BorderShadow"] = GetVec4List(colors.m_BorderShadow);
			root["FrameBg"] = GetVec4List(colors.m_FrameBg);
			root["FrameBgHovered"] = GetVec4List(colors.m_FrameBgHovered);
			root["FrameBgActive"] = GetVec4List(colors.m_FrameBgActive);
			root["TitleBg"] = GetVec4List(colors.m_TitleBg);
			root["TitleBgActive"] = GetVec4List(colors.m_TitleBgActive);
			root["TitleBgCollapsed"] = GetVec4List(colors.m_TitleBgCollapsed);
			root["MenuBarBg"] = GetVec4List(colors.m_MenuBarBg);
			root["ScrollbarBg"] = GetVec4List(colors.m_ScrollbarBg);
			root["ScrollbarGrab"] = GetVec4List(colors.m_ScrollbarGrab);
			root["ScrollbarGrabHovered"] = GetVec4List(colors.m_ScrollbarGrabHovered);
			root["ScrollbarGrabActive"] = GetVec4List(colors.m_ScrollbarGrabActive);
			root["CheckMark"] = GetVec4List(colors.m_CheckMark);
			root["SliderGrab"] = GetVec4List(colors.m_SliderGrab);
			root["SliderGrabActive"] = GetVec4List(colors.m_SliderGrabActive);
			root["Button"] = GetVec4List(colors.m_Button);
			root["ButtonHovered"] = GetVec4List(colors.m_ButtonHovered);
			root["ButtonActive"] = GetVec4List(colors.m_ButtonActive);
			root["Header"] = GetVec4List(colors.m_Header);
			root["HeaderHovered"] = GetVec4List(colors.m_HeaderHovered);
			root["HeaderActive"] = GetVec4List(colors.m_HeaderActive);
			root["Separator"] = GetVec4List(colors.m_Separator);
			root["SeparatorHovered"] = GetVec4List(colors.m_SeparatorHovered);
			root["SeparatorActive"] = GetVec4List(colors.m_SeparatorActive);
			root["ResizeGrip"] = GetVec4List(colors.m_ResizeGrip);
			root["ResizeGripHovered"] = GetVec4List(colors.m_ResizeGripHovered);
			root["ResizeGripActive"] = GetVec4List(colors.m_ResizeGripActive);
			root["Tab"] = GetVec4List(colors.m_Tab);
			root["TabHovered"] = GetVec4List(colors.m_TabHovered);
			root["TabActive"] = GetVec4List(colors.m_TabActive);
			root["TabUnfocused"] = GetVec4List(colors.m_TabUnfocused);
			root["TabUnfocusedActive"] = GetVec4List(colors.m_TabUnfocusedActive);
			root["DockingPreview"] = GetVec4List(colors.m_DockingPreview);
			root["DockingEmptyBg"] = GetVec4List(colors.m_DockingEmptyBg);
			root["PlotLines"] = GetVec4List(colors.m_PlotLines);
			root["PlotLinesHovered"] = GetVec4List(colors.m_PlotLinesHovered);
			root["PlotHistogram"] = GetVec4List(colors.m_PlotHistogram);
			root["PlotHistogramHovered"] = GetVec4List(colors.m_PlotHistogramHovered);
			root["TableHeaderBg"] = GetVec4List(colors.m_TableHeaderBg);
			root["TableBorderStrong"] = GetVec4List(colors.m_TableBorderStrong);
			root["TableBorderLight"] = GetVec4List(colors.m_TableBorderLight);
			root["TableRowBg"] = GetVec4List(colors.m_TableRowBg);
			root["TableRowBgAlt"] = GetVec4List(colors.m_TableRowBgAlt);
			root["TextSelectedBg"] = GetVec4List(colors.m_TextSelectedBg);
			root["DragDropTarget"] = GetVec4List(colors.m_DragDropTarget);
			root["NavHighlight"] = GetVec4List(colors.m_NavHighlight);
			root["NavWindowingHighlight"] = GetVec4List(colors.m_NavWindowingHighlight);
			root["NavWindowingDimBg"] = GetVec4List(colors.m_NavWindowingDimBg);
			root["ModalWindowDimBg"] = GetVec4List(colors.m_ModalWindowDimBg);
			return root;
		}
		nlohmann::json EditorStyle::SaveVar()
		{
			using namespace nlohmann;
			json root;
			root["Alpha"] = vars.Alpha;
			root["DisabledAlpha"] = vars.DisabledAlpha;
			root["WindowPadding"] = GetVec2List(vars.WindowPadding);
			root["WindowRounding"] = vars.WindowRounding;
			root["WindowBorderSize"] = vars.WindowBorderSize;
			root["WindowMinSize"] = GetVec2List(vars.WindowMinSize);
			root["WindowTitleAlign"] = GetVec2List(vars.WindowTitleAlign);
			root["WindowMenuButtonPosition"] = vars.WindowMenuButtonPosition;
			root["ChildRounding"] = vars.ChildRounding;
			root["ChildBorderSize"] = vars.ChildBorderSize;
			root["PopupRounding"] = vars.PopupRounding;
			root["PopupBorderSize"] = vars.PopupBorderSize;
			root["FramePadding"] = GetVec2List(vars.FramePadding);
			root["FrameRounding"] = vars.FrameRounding;
			root["FrameBorderSize"] = vars.FrameBorderSize;
			root["ItemSpacing"] = GetVec2List(vars.ItemSpacing);
			root["ItemInnerSpacing"] = GetVec2List(vars.ItemInnerSpacing);
			root["CellPadding"] = GetVec2List(vars.CellPadding);
			root["TouchExtraPadding"] = GetVec2List(vars.TouchExtraPadding);
			root["IndentSpacing"] = vars.IndentSpacing;
			root["ColumnsMinSpacing"] = vars.ColumnsMinSpacing;
			root["ScrollbarSize"] = vars.ScrollbarSize;
			root["ScrollbarRounding"] = vars.ScrollbarRounding;
			root["GrabMinSize"] = vars.GrabMinSize;
			root["GrabRounding"] = vars.GrabRounding;
			root["LogSliderDeadzone"] = vars.LogSliderDeadzone;
			root["TabRounding"] = vars.TabRounding;
			root["TabBorderSize"] = vars.TabBorderSize;
			root["TabMinWidthForCloseButton"] = vars.TabMinWidthForCloseButton;
			root["ColorButtonPosition"] = vars.ColorButtonPosition;
			root["ButtonTextAlign"] = GetVec2List(vars.ButtonTextAlign);
			root["SelectableTextAlign"] = GetVec2List(vars.SelectableTextAlign);
			root["DisplayWindowPadding"] = GetVec2List(vars.DisplayWindowPadding);
			root["DisplaySafeAreaPadding"] = GetVec2List(vars.DisplaySafeAreaPadding);
			root["MouseCursorScale"] = vars.MouseCursorScale;
			root["AntiAliasedLines"] = vars.AntiAliasedLines;
			root["AntiAliasedLinesUseTex"] = vars.AntiAliasedLinesUseTex;
			root["AntiAliasedFill"] = vars.AntiAliasedFill;
			root["CurveTessellationTol"] = vars.CurveTessellationTol;
			root["CircleTessellationMaxError"] = vars.CircleTessellationMaxError;
			return root;
		}
		bool EditorStyle::LoadColor(nlohmann::json j)
		{
			colors.m_TextColor = ListToVec4(j, "TextColor");
			colors.m_TextDisabled = ListToVec4(j, "TextDisabled");
			colors.m_WindowBg = ListToVec4(j, "WindowBg");
			colors.m_ChildBg = ListToVec4(j, "ChildBg");
			colors.m_PopupBg = ListToVec4(j, "PopupBg");
			colors.m_Border = ListToVec4(j, "Border");
			colors.m_BorderShadow = ListToVec4(j, "BorderShadow");
			colors.m_FrameBg = ListToVec4(j, "FrameBg");
			colors.m_FrameBgHovered = ListToVec4(j, "FrameBgHovered");
			colors.m_FrameBgActive = ListToVec4(j, "FrameBgActive");
			colors.m_TitleBg = ListToVec4(j, "TitleBg");
			colors.m_TitleBgActive = ListToVec4(j, "TitleBgActive");
			colors.m_TitleBgCollapsed = ListToVec4(j, "TitleBgCollapsed");
			colors.m_MenuBarBg = ListToVec4(j, "MenuBarBg");
			colors.m_ScrollbarBg = ListToVec4(j, "ScrollbarBg");
			colors.m_ScrollbarGrab = ListToVec4(j, "ScrollbarGrab");
			colors.m_ScrollbarGrabHovered = ListToVec4(j, "ScrollbarGrabHovered");
			colors.m_ScrollbarGrabActive = ListToVec4(j, "ScrollbarGrabActive");
			colors.m_CheckMark = ListToVec4(j, "CheckMark");
			colors.m_SliderGrab = ListToVec4(j, "SliderGrab");
			colors.m_SliderGrabActive = ListToVec4(j, "SliderGrabActive");
			colors.m_Button = ListToVec4(j, "Button");
			colors.m_ButtonHovered = ListToVec4(j, "ButtonHovered");
			colors.m_ButtonActive = ListToVec4(j, "ButtonActive");
			colors.m_Header = ListToVec4(j, "Header");
			colors.m_HeaderHovered = ListToVec4(j, "HeaderHovered");
			colors.m_HeaderActive = ListToVec4(j, "HeaderActive");
			colors.m_Separator = ListToVec4(j, "Separator");
			colors.m_SeparatorHovered = ListToVec4(j, "SeparatorHovered");
			colors.m_SeparatorActive = ListToVec4(j, "SeparatorActive");
			colors.m_ResizeGrip = ListToVec4(j, "ResizeGrip");
			colors.m_ResizeGripHovered = ListToVec4(j, "ResizeGripHovered");
			colors.m_ResizeGripActive = ListToVec4(j, "ResizeGripActive");
			colors.m_Tab = ListToVec4(j, "Tab");
			colors.m_TabHovered = ListToVec4(j, "TabHovered");
			colors.m_TabActive = ListToVec4(j, "TabActive");
			colors.m_TabUnfocused = ListToVec4(j, "TabUnfocused");
			colors.m_TabUnfocusedActive = ListToVec4(j, "TabUnfocusedActive");
			colors.m_DockingPreview = ListToVec4(j, "DockingPreview");
			colors.m_DockingEmptyBg = ListToVec4(j, "DockingEmptyBg");
			colors.m_PlotLines = ListToVec4(j, "PlotLines");
			colors.m_PlotLinesHovered = ListToVec4(j, "PlotLinesHovered");
			colors.m_PlotHistogram = ListToVec4(j, "PlotHistogram");
			colors.m_PlotHistogramHovered = ListToVec4(j, "PlotHistogramHovered");
			colors.m_TableHeaderBg = ListToVec4(j, "TableHeaderBg");
			colors.m_TableBorderStrong = ListToVec4(j, "TableBorderStrong");
			colors.m_TableBorderLight = ListToVec4(j, "TableBorderLight");
			colors.m_TableRowBg = ListToVec4(j, "TableRowBg");
			colors.m_TableRowBgAlt = ListToVec4(j, "TableRowBgAlt");
			colors.m_TextSelectedBg = ListToVec4(j, "TextSelectedBg");
			colors.m_DragDropTarget = ListToVec4(j, "DragDropTarget");
			colors.m_NavHighlight = ListToVec4(j, "NavHighlight");
			colors.m_NavWindowingHighlight = ListToVec4(j, "NavWindowingHighlight");
			colors.m_NavWindowingDimBg = ListToVec4(j, "NavWindowingDimBg");
			colors.m_ModalWindowDimBg = ListToVec4(j, "ModalWindowDimBg");
			return true;
		}
		bool EditorStyle::LoadVar(nlohmann::json j)
		{
			vars.Alpha = j["Alpha"];
			vars.DisabledAlpha= j["DisabledAlpha"];
			vars.WindowPadding = ListToVec2(j, "WindowPadding");
			vars.WindowRounding= j["WindowRounding"];
			vars.WindowBorderSize= j["WindowBorderSize"];
			vars.WindowMinSize = ListToVec2(j, "WindowMinSize");
			vars.WindowTitleAlign = ListToVec2(j, "WindowTitleAlign");
			vars.WindowMenuButtonPosition = (Direction)j["WindowMenuButtonPosition"];
			vars.ChildRounding = j["ChildRounding"];
			vars.ChildBorderSize = j["ChildBorderSize"];
			vars.PopupRounding = j["PopupRounding"];
			vars.PopupBorderSize = j["PopupBorderSize"];
			vars.FramePadding = ListToVec2(j, "FramePadding");
			vars.FrameRounding = j["FrameRounding"];
			vars.FrameBorderSize = j["FrameBorderSize"];
			vars.ItemSpacing = ListToVec2(j, "ItemSpacing");
			vars.ItemInnerSpacing = ListToVec2(j, "ItemInnerSpacing");
			vars.CellPadding = ListToVec2(j, "CellPadding");
			vars.TouchExtraPadding = ListToVec2(j, "TouchExtraPadding");
			vars.IndentSpacing= j["IndentSpacing"];
			vars.ColumnsMinSpacing= j["ColumnsMinSpacing"];
			vars.ScrollbarSize= j["ScrollbarSize"];
			vars.ScrollbarRounding= j["ScrollbarRounding"];
			vars.GrabMinSize = j["GrabMinSize"];
			vars.GrabRounding = j["GrabRounding"];
			vars.LogSliderDeadzone= j["LogSliderDeadzone"];
			vars.TabRounding = j["TabRounding"];
			vars.TabBorderSize= j["TabBorderSize"];
			vars.TabMinWidthForCloseButton= j["TabMinWidthForCloseButton"];
			vars.ColorButtonPosition= (Direction)j["ColorButtonPosition"];
			vars.ButtonTextAlign = ListToVec2(j, "ButtonTextAlign");
			vars.SelectableTextAlign = ListToVec2(j, "SelectableTextAlign");
			vars.DisplayWindowPadding = ListToVec2(j, "DisplayWindowPadding");
			vars.DisplaySafeAreaPadding = ListToVec2(j, "DisplaySafeAreaPadding");
			vars.MouseCursorScale= j["MouseCursorScale"];
			vars.AntiAliasedLines= j["AntiAliasedLines"];
			vars.AntiAliasedLinesUseTex= j["AntiAliasedLinesUseTex"];
			vars.AntiAliasedFill= j["AntiAliasedFill"];
			vars.CurveTessellationTol= j["CurveTessellationTol"];
			vars.CircleTessellationMaxError= j["CircleTessellationMaxError"];

			return true;
		}
}
}