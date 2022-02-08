#pragma once
#include <config.h>

namespace Tara {
	#ifndef TARA_NO_IMGUI
	namespace UI {
		/*
			Summary:
				Set imgui style.
		*/
		#pragma region Style
		DllExport void ImGui_SetLightTheme();
		DllExport void ImGui_SetDarkTheme();
		DllExport void ImGui_SetClassicTheme();
		DllExport void ImGui_SetTaraTheme();
		DllExport void ImGui_TextColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_TextColor(glm::vec4 v);
		DllExport void ImGui_TextColor(glm::vec3 v);
		DllExport void ImGui_TextDisabledColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_TextDisabledColor(glm::vec4 v);
		DllExport void ImGui_TextDisabledColor(glm::vec3 v);
		DllExport void ImGui_WindowBgColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_ChildBgColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_PopupBgColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_BorderColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_BorderShadowColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_FrameBgColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_FrameBgHoveredColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_FrameBgActiveColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_TitleBgColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_TitleBgActiveColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_TitleBgCollapsedColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_MenuBarBgColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_HeaderColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_HeaderHoveredColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_HeaderActiveColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_NavHighlightColor(float r, float g, float b, float a = 1);
		DllExport void ImGui_PopVar(int32_t c = 1);
		DllExport void ImGui_PopColor(int32_t c = 1);
		#pragma endregion
	}
	#endif
}