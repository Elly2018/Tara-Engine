#pragma once
#include "editor_config.h"
#include "editor_setting.h"

namespace Tara {
	namespace UI {
		/*
			Summary:
				Set imgui style.
		*/
		#pragma region Style
		TARA_EDITOR_API bool ImGui_RegisterTheme(const char* name, StyleColor* theme);
		TARA_EDITOR_API std::vector<std::pair<std::string, StyleColor*>> ImGui_RegisteredTheme();
		/*
			Summary:
				If failed to get the theme, it will return dark theme instead.
		*/
		TARA_EDITOR_API StyleColor* ImGui_GetRegisteredTheme(const char* name);
		TARA_EDITOR_API void ImGui_SetLightTheme(bool save = false);
		TARA_EDITOR_API void ImGui_SetDarkTheme(bool save = false);
		TARA_EDITOR_API void ImGui_SetClassicTheme(bool save = false);
		TARA_EDITOR_API void ImGui_SetTaraTheme(bool save = false);
		TARA_EDITOR_API void ImGui_TextColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_TextColor(glm::vec4 v);
		TARA_EDITOR_API void ImGui_TextColor(glm::vec3 v);
		TARA_EDITOR_API void ImGui_TextDisabledColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_TextDisabledColor(glm::vec4 v);
		TARA_EDITOR_API void ImGui_TextDisabledColor(glm::vec3 v);
		TARA_EDITOR_API void ImGui_WindowBgColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_ChildBgColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_PopupBgColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_BorderColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_BorderColor(glm::vec4 color);
		TARA_EDITOR_API void ImGui_BorderColor(glm::vec3 color);
		TARA_EDITOR_API void ImGui_BorderShadowColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_FrameBgColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_FrameBgHoveredColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_FrameBgActiveColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_TitleBgColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_TitleBgColor(glm::vec4 v);
		TARA_EDITOR_API void ImGui_TitleBgColor(glm::vec3 v);
		TARA_EDITOR_API void ImGui_TitleBgActiveColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_TitleBgCollapsedColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_MenuBarBgColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_HeaderColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_HeaderColor(glm::vec4 v);
		TARA_EDITOR_API void ImGui_HeaderColor(glm::vec3 v);
		TARA_EDITOR_API void ImGui_HeaderHoveredColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_HeaderHoveredColor(glm::vec4 v);
		TARA_EDITOR_API void ImGui_HeaderHoveredColor(glm::vec3 v);
		TARA_EDITOR_API void ImGui_HeaderActiveColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_HeaderActiveColor(glm::vec4 v);
		TARA_EDITOR_API void ImGui_HeaderActiveColor(glm::vec3 v);
		TARA_EDITOR_API void ImGui_NavHighlightColor(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_TableRowBg(float r, float g, float b, float a = 1);
		TARA_EDITOR_API void ImGui_TableRowBg(glm::vec4 v);
		TARA_EDITOR_API void ImGui_TableRowBg(glm::vec3 v);
		TARA_EDITOR_API void ImGui_PopVar(int32_t c = 1);
		TARA_EDITOR_API void ImGui_PopColor(int32_t c = 1);
		#pragma endregion
	}
}