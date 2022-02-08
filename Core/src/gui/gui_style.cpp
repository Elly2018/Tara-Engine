#include "gui/gui_style.h"
#ifndef TARA_NO_IMGUI
#include <imgui.h>
#endif

namespace Tara {
#ifndef TARA_NO_IMGUI
	namespace UI {
		void ImGui_SetLightTheme() {
			ImGui::StyleColorsLight();
		}
		void ImGui_SetDarkTheme() {
			ImGui::StyleColorsDark();
		}
		void ImGui_SetClassicTheme() {
			ImGui::StyleColorsClassic();
		}
		void ImGui_SetTaraTheme()
		{
			ImGuiStyle& style = ImGui::GetStyle();

			// light style from Pacôme Danhiez (user itamago) https://github.com/ocornut/imgui/pull/511#issuecomment-175719267
			style.Alpha = 1.0f;
			style.FrameRounding = 3.0f;
			style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
			style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
			style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
			style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
			style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
			style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
			style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
			style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
			style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
			style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
			style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
			style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
			style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
			//style.Colors[ImGuiCol_ComboBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
			style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
			style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
			style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
			style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
			style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			//style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
			//style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
			//style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
			style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
			style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
			//style.Colors[ImGuiCol_CloseButton] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
			//style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
			//style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
			style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
			style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
			//style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

			for (int i = 0; i <= ImGuiCol_COUNT; i++)
			{
				ImVec4& col = style.Colors[i];
				float H, S, V;
				ImGui::ColorConvertRGBtoHSV(col.x, col.y, col.z, H, S, V);

				if (S < 0.1f)
				{
					V = 1.0f - V;
				}
				ImGui::ColorConvertHSVtoRGB(H, S, V, col.x, col.y, col.z);
				if (col.w < 1.00f)
				{
					col.w *= 0.9f;
				}
			}
		}
		void ImGui_TextColor(float r, float g, float b, float a) {
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(r, g, b, a));
		}
		void ImGui_TextColor(glm::vec4 v) {
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(v.r, v.g, v.b, v.a));
		}
		void ImGui_TextColor(glm::vec3 v) {
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(v.r, v.g, v.b, 1));
		}
		void ImGui_TextDisabledColor(float r, float g, float b, float a) {
			ImGui::PushStyleColor(ImGuiCol_TextDisabled, ImVec4(r, g, b, a));
		}
		void ImGui_TextDisabledColor(glm::vec4 v) {
			ImGui::PushStyleColor(ImGuiCol_TextDisabled, ImVec4(v.r, v.g, v.b, v.a));
		}
		void ImGui_TextDisabledColor(glm::vec3 v) {
			ImGui::PushStyleColor(ImGuiCol_TextDisabled, ImVec4(v.r, v.g, v.b, 1));
		}

		void ImGui_WindowBgColor(float r, float g, float b, float a) {
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(r, g, b, a));
		}
		void ImGui_ChildBgColor(float r, float g, float b, float a) {
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(r, g, b, a));
		}
		void ImGui_PopupBgColor(float r, float g, float b, float a) {
			ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(r, g, b, a));
		}
		void ImGui_BorderColor(float r, float g, float b, float a) {
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(r, g, b, a));
		}
		void ImGui_BorderShadowColor(float r, float g, float b, float a) {
			ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(r, g, b, a));
		}
		void ImGui_FrameBgColor(float r, float g, float b, float a) {
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(r, g, b, a));
		}
		void ImGui_FrameBgHoveredColor(float r, float g, float b, float a) {
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(r, g, b, a));
		}
		void ImGui_FrameBgActiveColor(float r, float g, float b, float a) {
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(r, g, b, a));
		}
		void ImGui_TitleBgColor(float r, float g, float b, float a) {
			ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = ImVec4(r, g, b, a);
		}
		void ImGui_TitleBgActiveColor(float r, float g, float b, float a) {
			ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = ImVec4(r, g, b, a);
		}
		void ImGui_TitleBgCollapsedColor(float r, float g, float b, float a) {
			ImGui::GetStyle().Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(r, g, b, a);
		}
		void ImGui_MenuBarBgColor(float r, float g, float b, float a) {
			ImGui::GetStyle().Colors[ImGuiCol_MenuBarBg] = ImVec4(r, g, b, a);
		}
		void ImGui_HeaderColor(float r, float g, float b, float a) {
			ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(r, g, b, a));
		}
		void ImGui_HeaderHoveredColor(float r, float g, float b, float a)
		{
			ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(r, g, b, a));
		}
		void ImGui_HeaderActiveColor(float r, float g, float b, float a)
		{
			ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(r, g, b, a));
		}
		void ImGui_NavHighlightColor(float r, float g, float b, float a)
		{
			ImGui::PushStyleColor(ImGuiCol_NavHighlight, ImVec4(r, g, b, a));
		}
		void ImGui_PopVar(int32_t c)
		{
			ImGui::PopStyleVar(c);
		}
		void ImGui_PopColor(int32_t c)
		{
			ImGui::PopStyleColor(c);
		}
	}
#endif
}