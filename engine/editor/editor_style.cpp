#include "editor_style.h"
#include <imgui.h>
#include "editor_setting.h"

namespace Tara {
	namespace UI {
		StyleColor* LightTheme() {
			StyleColor* result = new StyleColor();
			result->m_TextColor =			glm::vec4(0.00f, 0.00f, 0.00f, 1.00f);
			result->m_TextDisabled =			glm::vec4(0.60f, 0.60f, 0.60f, 1.00f);
			result->m_WindowBg =				glm::vec4(0.94f, 0.94f, 0.94f, 1.00f);
			result->m_ChildBg =				glm::vec4(0.00f, 0.00f, 0.00f, 0.00f);
			result->m_PopupBg =				glm::vec4(1.00f, 1.00f, 1.00f, 0.98f);
			result->m_Border =				glm::vec4(0.00f, 0.00f, 0.00f, 0.30f);
			result->m_BorderShadow =			glm::vec4(0.00f, 0.00f, 0.00f, 0.00f);
			result->m_FrameBg =				glm::vec4(1.00f, 1.00f, 1.00f, 1.00f);
			result->m_FrameBgHovered =		glm::vec4(0.26f, 0.59f, 0.98f, 0.40f);
			result->m_FrameBgActive =		glm::vec4(0.26f, 0.59f, 0.98f, 0.67f);
			result->m_TitleBg =				glm::vec4(0.96f, 0.96f, 0.96f, 1.00f);
			result->m_TitleBgActive =		glm::vec4(0.82f, 0.82f, 0.82f, 1.00f);
			result->m_TitleBgCollapsed =		glm::vec4(1.00f, 1.00f, 1.00f, 0.51f);
			result->m_MenuBarBg =			glm::vec4(0.86f, 0.86f, 0.86f, 1.00f);
			result->m_ScrollbarBg =			glm::vec4(0.98f, 0.98f, 0.98f, 0.53f);
			result->m_ScrollbarGrab =		glm::vec4(0.69f, 0.69f, 0.69f, 0.80f);
			result->m_ScrollbarGrabHovered = glm::vec4(0.49f, 0.49f, 0.49f, 0.80f);
			result->m_ScrollbarGrabActive =	glm::vec4(0.49f, 0.49f, 0.49f, 1.00f);
			result->m_CheckMark =			glm::vec4(0.26f, 0.59f, 0.98f, 1.00f);
			result->m_SliderGrab =			glm::vec4(0.26f, 0.59f, 0.98f, 0.78f);
			result->m_SliderGrabActive =		glm::vec4(0.46f, 0.54f, 0.80f, 0.60f);
			result->m_Button =				glm::vec4(0.26f, 0.59f, 0.98f, 0.40f);
			result->m_ButtonHovered =		glm::vec4(0.26f, 0.59f, 0.98f, 1.00f);
			result->m_ButtonActive =			glm::vec4(0.06f, 0.53f, 0.98f, 1.00f);
			result->m_Header =				glm::vec4(0.26f, 0.59f, 0.98f, 0.31f);
			result->m_HeaderHovered =		glm::vec4(0.26f, 0.59f, 0.98f, 0.80f);
			result->m_HeaderActive =			glm::vec4(0.26f, 0.59f, 0.98f, 1.00f);
			result->m_Separator =			glm::vec4(0.39f, 0.39f, 0.39f, 0.62f);
			result->m_SeparatorHovered =		glm::vec4(0.14f, 0.44f, 0.80f, 0.78f);
			result->m_SeparatorActive =		glm::vec4(0.14f, 0.44f, 0.80f, 1.00f);
			result->m_ResizeGrip =			glm::vec4(0.35f, 0.35f, 0.35f, 0.17f);
			result->m_ResizeGripHovered =	glm::vec4(0.26f, 0.59f, 0.98f, 0.67f);
			result->m_ResizeGripActive =		glm::vec4(0.26f, 0.59f, 0.98f, 0.95f);
			result->m_Tab =					result->m_Header + ((result->m_TitleBgActive - result->m_Header) / 0.90f);
			result->m_TabHovered =			result->m_HeaderHovered;
			result->m_TabActive =			result->m_HeaderActive + ((result->m_TitleBgActive - result->m_HeaderActive) / 0.60f);
			result->m_TabUnfocused =			result->m_Tab + ((result->m_TitleBg - result->m_HeaderActive) / 0.80f);
			result->m_TabUnfocusedActive =	result->m_TabActive + ((result->m_TitleBg - result->m_TabActive) / 0.40f);
			result->m_DockingPreview =		result->m_Header + glm::vec4(1.0f, 1.0f, 1.0f, 0.7f);
			result->m_DockingEmptyBg =		glm::vec4(0.20f, 0.20f, 0.20f, 1.00f);
			result->m_PlotLines =			glm::vec4(0.39f, 0.39f, 0.39f, 1.00f);
			result->m_PlotLinesHovered =		glm::vec4(1.00f, 0.43f, 0.35f, 1.00f);
			result->m_PlotHistogram =		glm::vec4(0.90f, 0.70f, 0.00f, 1.00f);
			result->m_PlotHistogramHovered = glm::vec4(1.00f, 0.45f, 0.00f, 1.00f);
			result->m_TableHeaderBg =		glm::vec4(0.78f, 0.87f, 0.98f, 1.00f);
			result->m_TableBorderStrong =	glm::vec4(0.57f, 0.57f, 0.64f, 1.00f);
			result->m_TableBorderLight =		glm::vec4(0.68f, 0.68f, 0.74f, 1.00f);
			result->m_TableRowBg =			glm::vec4(0.00f, 0.00f, 0.00f, 0.00f);
			result->m_TableRowBgAlt =		glm::vec4(0.30f, 0.30f, 0.30f, 0.09f);
			result->m_TextSelectedBg =		glm::vec4(0.26f, 0.59f, 0.98f, 0.35f);
			result->m_DragDropTarget =		glm::vec4(0.26f, 0.59f, 0.98f, 0.95f);
			result->m_NavHighlight =			result->m_HeaderHovered;
			result->m_NavWindowingHighlight =glm::vec4(0.70f, 0.70f, 0.70f, 0.70f);
			result->m_NavWindowingDimBg =	glm::vec4(0.20f, 0.20f, 0.20f, 0.20f);
			result->m_ModalWindowDimBg =		glm::vec4(0.20f, 0.20f, 0.20f, 0.35f);
			return result;
		}
		StyleColor* DarkTheme() {
			StyleColor* result = new StyleColor();
			result->m_TextColor =			glm::vec4(1.00f, 1.00f, 1.00f, 1.00f);
			result->m_TextDisabled =			glm::vec4(0.50f, 0.50f, 0.50f, 1.00f);
			result->m_WindowBg =				glm::vec4(0.06f, 0.06f, 0.06f, 0.94f);
			result->m_ChildBg =				glm::vec4(0.00f, 0.00f, 0.00f, 0.00f);
			result->m_PopupBg =				glm::vec4(0.08f, 0.08f, 0.08f, 0.94f);
			result->m_Border =				glm::vec4(0.43f, 0.43f, 0.50f, 0.50f);
			result->m_BorderShadow =			glm::vec4(0.00f, 0.00f, 0.00f, 0.00f);
			result->m_FrameBg =				glm::vec4(0.16f, 0.29f, 0.48f, 0.54f);
			result->m_FrameBgHovered =		glm::vec4(0.26f, 0.59f, 0.98f, 0.40f);
			result->m_FrameBgActive =		glm::vec4(0.26f, 0.59f, 0.98f, 0.67f);
			result->m_TitleBg =				glm::vec4(0.04f, 0.04f, 0.04f, 1.00f);
			result->m_TitleBgActive =		glm::vec4(0.16f, 0.29f, 0.48f, 1.00f);
			result->m_TitleBgCollapsed =		glm::vec4(0.00f, 0.00f, 0.00f, 0.51f);
			result->m_MenuBarBg =			glm::vec4(0.14f, 0.14f, 0.14f, 1.00f);
			result->m_ScrollbarBg =			glm::vec4(0.02f, 0.02f, 0.02f, 0.53f);
			result->m_ScrollbarGrab =		glm::vec4(0.31f, 0.31f, 0.31f, 1.00f);
			result->m_ScrollbarGrabHovered = glm::vec4(0.41f, 0.41f, 0.41f, 1.00f);
			result->m_ScrollbarGrabActive =	glm::vec4(0.51f, 0.51f, 0.51f, 1.00f);
			result->m_CheckMark =			glm::vec4(0.26f, 0.59f, 0.98f, 1.00f);
			result->m_SliderGrab =			glm::vec4(0.24f, 0.52f, 0.88f, 1.00f);
			result->m_SliderGrabActive =		glm::vec4(0.26f, 0.59f, 0.98f, 1.00f);
			result->m_Button =				glm::vec4(0.26f, 0.59f, 0.98f, 0.40f);
			result->m_ButtonHovered =		glm::vec4(0.26f, 0.59f, 0.98f, 1.00f);
			result->m_ButtonActive =			glm::vec4(0.06f, 0.53f, 0.98f, 1.00f);
			result->m_Header =				glm::vec4(0.26f, 0.59f, 0.98f, 0.31f);
			result->m_HeaderHovered =		glm::vec4(0.26f, 0.59f, 0.98f, 0.80f);
			result->m_HeaderActive =			glm::vec4(0.26f, 0.59f, 0.98f, 1.00f);
			result->m_Separator =			result->m_Border;
			result->m_SeparatorHovered =		glm::vec4(0.10f, 0.40f, 0.75f, 0.78f);
			result->m_SeparatorActive =		glm::vec4(0.10f, 0.40f, 0.75f, 1.00f);
			result->m_ResizeGrip =			glm::vec4(0.26f, 0.59f, 0.98f, 0.20f);
			result->m_ResizeGripHovered =	glm::vec4(0.26f, 0.59f, 0.98f, 0.67f);
			result->m_ResizeGripActive =		glm::vec4(0.26f, 0.59f, 0.98f, 0.95f);
			result->m_Tab =					result->m_Header + ((result->m_TitleBgActive - result->m_Header) / 0.90f);
			result->m_TabHovered =			result->m_HeaderHovered;
			result->m_TabActive =			result->m_HeaderActive + ((result->m_TitleBgActive - result->m_HeaderActive) / 0.60f);
			result->m_TabUnfocused =			result->m_Tab + ((result->m_TitleBg - result->m_HeaderActive) / 0.80f);
			result->m_TabUnfocusedActive =	result->m_TabActive + ((result->m_TitleBg - result->m_TabActive) / 0.40f);
			result->m_DockingPreview =		result->m_HeaderActive + glm::vec4(1.0f, 1.0f, 1.0f, 0.7f);
			result->m_DockingEmptyBg =		glm::vec4(0.20f, 0.20f, 0.20f, 1.00f);
			result->m_PlotLines =			glm::vec4(0.61f, 0.61f, 0.61f, 1.00f);
			result->m_PlotLinesHovered =		glm::vec4(1.00f, 0.43f, 0.35f, 1.00f);
			result->m_PlotHistogram =		glm::vec4(0.90f, 0.70f, 0.00f, 1.00f);
			result->m_PlotHistogramHovered = glm::vec4(1.00f, 0.60f, 0.00f, 1.00f);
			result->m_TableHeaderBg =		glm::vec4(0.19f, 0.19f, 0.20f, 1.00f);
			result->m_TableBorderStrong =	glm::vec4(0.31f, 0.31f, 0.35f, 1.00f);
			result->m_TableBorderLight =		glm::vec4(0.23f, 0.23f, 0.25f, 1.00f);
			result->m_TableRowBg =			glm::vec4(0.00f, 0.00f, 0.00f, 0.00f);
			result->m_TableRowBgAlt =		glm::vec4(1.00f, 1.00f, 1.00f, 0.06f);
			result->m_TextSelectedBg =		glm::vec4(0.26f, 0.59f, 0.98f, 0.35f);
			result->m_DragDropTarget =		glm::vec4(1.00f, 1.00f, 0.00f, 0.90f);
			result->m_NavHighlight =			glm::vec4(0.26f, 0.59f, 0.98f, 1.00f);
			result->m_NavWindowingHighlight =glm::vec4(1.00f, 1.00f, 1.00f, 0.70f);
			result->m_NavWindowingDimBg =	glm::vec4(0.80f, 0.80f, 0.80f, 0.20f);
			result->m_ModalWindowDimBg =		glm::vec4(0.80f, 0.80f, 0.80f, 0.35f);
			return result;
		}
		StyleColor* ClassicTheme() {
			StyleColor* result = new StyleColor();
			result->m_TextColor =			glm::vec4(0.90f, 0.90f, 0.90f, 1.00f);
			result->m_TextDisabled =			glm::vec4(0.60f, 0.60f, 0.60f, 1.00f);
			result->m_WindowBg =				glm::vec4(0.00f, 0.00f, 0.00f, 0.85f);
			result->m_ChildBg =				glm::vec4(0.00f, 0.00f, 0.00f, 0.00f);
			result->m_PopupBg =				glm::vec4(0.11f, 0.11f, 0.14f, 0.92f);
			result->m_Border =				glm::vec4(0.50f, 0.50f, 0.50f, 0.50f);
			result->m_BorderShadow =			glm::vec4(0.00f, 0.00f, 0.00f, 0.00f);
			result->m_FrameBg =				glm::vec4(0.43f, 0.43f, 0.43f, 0.39f);
			result->m_FrameBgHovered =		glm::vec4(0.47f, 0.47f, 0.69f, 0.40f);
			result->m_FrameBgActive =		glm::vec4(0.42f, 0.41f, 0.64f, 0.69f);
			result->m_TitleBg =				glm::vec4(0.27f, 0.27f, 0.54f, 0.83f);
			result->m_TitleBgActive =		glm::vec4(0.32f, 0.32f, 0.63f, 0.87f);
			result->m_TitleBgCollapsed =		glm::vec4(0.40f, 0.40f, 0.80f, 0.20f);
			result->m_MenuBarBg =			glm::vec4(0.40f, 0.40f, 0.55f, 0.80f);
			result->m_ScrollbarBg =			glm::vec4(0.20f, 0.25f, 0.30f, 0.60f);
			result->m_ScrollbarGrab =		glm::vec4(0.40f, 0.40f, 0.80f, 0.30f);
			result->m_ScrollbarGrabHovered = glm::vec4(0.40f, 0.40f, 0.80f, 0.40f);
			result->m_ScrollbarGrabActive =	glm::vec4(0.41f, 0.39f, 0.80f, 0.60f);
			result->m_CheckMark =			glm::vec4(0.90f, 0.90f, 0.90f, 0.50f);
			result->m_SliderGrab =			glm::vec4(1.00f, 1.00f, 1.00f, 0.30f);
			result->m_SliderGrabActive =		glm::vec4(0.41f, 0.39f, 0.80f, 0.60f);
			result->m_Button =				glm::vec4(0.35f, 0.40f, 0.61f, 0.62f);
			result->m_ButtonHovered =		glm::vec4(0.40f, 0.48f, 0.71f, 0.79f);
			result->m_ButtonActive =			glm::vec4(0.46f, 0.54f, 0.80f, 1.00f);
			result->m_Header =				glm::vec4(0.40f, 0.40f, 0.90f, 0.45f);
			result->m_HeaderHovered =		glm::vec4(0.45f, 0.45f, 0.90f, 0.80f);
			result->m_HeaderActive =			glm::vec4(0.53f, 0.53f, 0.87f, 0.80f);
			result->m_Separator =			glm::vec4(0.50f, 0.50f, 0.50f, 0.60f);
			result->m_SeparatorHovered =		glm::vec4(0.60f, 0.60f, 0.70f, 1.00f);
			result->m_SeparatorActive =		glm::vec4(0.70f, 0.70f, 0.90f, 1.00f);
			result->m_ResizeGrip =			glm::vec4(1.00f, 1.00f, 1.00f, 0.10f);
			result->m_ResizeGripHovered =	glm::vec4(0.78f, 0.82f, 1.00f, 0.60f);
			result->m_ResizeGripActive =		glm::vec4(0.78f, 0.82f, 1.00f, 0.90f);
			result->m_Tab =					result->m_Header + ((result->m_TitleBgActive - result->m_Header) / 0.90f);
			result->m_TabHovered =			result->m_HeaderHovered;
			result->m_TabActive =			result->m_HeaderActive + ((result->m_TitleBgActive - result->m_HeaderActive) / 0.60f);
			result->m_TabUnfocused =			result->m_Tab + ((result->m_TitleBg - result->m_HeaderActive) / 0.80f);
			result->m_TabUnfocusedActive =	result->m_TabActive + ((result->m_TitleBg - result->m_TabActive) / 0.40f);
			result->m_DockingPreview =		result->m_Header + glm::vec4(1.0f, 1.0f, 1.0f, 0.7f);
			result->m_DockingEmptyBg =		glm::vec4(0.20f, 0.20f, 0.20f, 1.00f);
			result->m_PlotLines =			glm::vec4(1.00f, 1.00f, 1.00f, 1.00f);
			result->m_PlotLinesHovered =		glm::vec4(0.90f, 0.70f, 0.00f, 1.00f);
			result->m_PlotHistogram =		glm::vec4(0.90f, 0.70f, 0.00f, 1.00f);
			result->m_PlotHistogramHovered = glm::vec4(1.00f, 0.60f, 0.00f, 1.00f);
			result->m_TableHeaderBg =		glm::vec4(0.27f, 0.27f, 0.38f, 1.00f);
			result->m_TableBorderStrong =	glm::vec4(0.31f, 0.31f, 0.45f, 1.00f);
			result->m_TableBorderLight =		glm::vec4(0.26f, 0.26f, 0.28f, 1.00f);
			result->m_TableRowBg =			glm::vec4(0.00f, 0.00f, 0.00f, 0.00f);
			result->m_TableRowBgAlt =		glm::vec4(1.00f, 1.00f, 1.00f, 0.07f);
			result->m_TextSelectedBg =		glm::vec4(0.00f, 0.00f, 1.00f, 0.35f);
			result->m_DragDropTarget =		glm::vec4(1.00f, 1.00f, 0.00f, 0.90f);
			result->m_NavHighlight =			result->m_HeaderHovered;
			result->m_NavWindowingHighlight =glm::vec4(1.00f, 1.00f, 1.00f, 0.70f);
			result->m_NavWindowingDimBg =	glm::vec4(0.80f, 0.80f, 0.80f, 0.20f);
			result->m_ModalWindowDimBg =		glm::vec4(0.20f, 0.20f, 0.20f, 0.35f);
			return result;
		}
		StyleColor* TaraTheme() {
			StyleColor* result = DarkTheme();

			result->m_TextColor = glm::vec4(1.000f, 1.000f, 1.000f, 1.000f);
			result->m_TextDisabled = glm::vec4(0.500f, 0.500f, 0.500f, 1.000f);
			result->m_WindowBg = glm::vec4(0.180f, 0.180f, 0.180f, 1.000f);
			result->m_ChildBg = glm::vec4(0.280f, 0.280f, 0.280f, 0.000f);
			result->m_PopupBg = glm::vec4(0.313f, 0.313f, 0.313f, 1.000f);
			result->m_Border = glm::vec4(0.266f, 0.266f, 0.266f, 1.000f);
			result->m_BorderShadow = glm::vec4(0.000f, 0.000f, 0.000f, 0.000f);
			result->m_FrameBg = glm::vec4(0.160f, 0.160f, 0.160f, 1.000f);
			result->m_FrameBgHovered = glm::vec4(0.200f, 0.200f, 0.200f, 1.000f);
			result->m_FrameBgActive = glm::vec4(0.280f, 0.280f, 0.280f, 1.000f);
			result->m_TitleBg = glm::vec4(0.148f, 0.148f, 0.148f, 1.000f);
			result->m_TitleBgActive = glm::vec4(0.148f, 0.148f, 0.148f, 1.000f);
			result->m_TitleBgCollapsed = glm::vec4(0.148f, 0.148f, 0.148f, 1.000f);
			result->m_MenuBarBg = glm::vec4(0.195f, 0.195f, 0.195f, 1.000f);
			result->m_ScrollbarBg = glm::vec4(0.160f, 0.160f, 0.160f, 1.000f);
			result->m_ScrollbarGrab = glm::vec4(0.277f, 0.277f, 0.277f, 1.000f);
			result->m_ScrollbarGrabHovered = glm::vec4(0.300f, 0.300f, 0.300f, 1.000f);
			result->m_ScrollbarGrabActive = glm::vec4(1.000f, 0.391f, 0.000f, 1.000f);
			result->m_CheckMark = glm::vec4(1.000f, 1.000f, 1.000f, 1.000f);
			result->m_SliderGrab = glm::vec4(0.391f, 0.391f, 0.391f, 1.000f);
			result->m_SliderGrabActive = glm::vec4(1.000f, 0.391f, 0.000f, 1.000f);
			result->m_Button = glm::vec4(1.000f, 1.000f, 1.000f, 0.000f);
			result->m_ButtonHovered = glm::vec4(1.000f, 1.000f, 1.000f, 0.156f);
			result->m_ButtonActive = glm::vec4(1.000f, 1.000f, 1.000f, 0.391f);
			result->m_Header = glm::vec4(0.313f, 0.313f, 0.313f, 1.000f);
			result->m_HeaderHovered = glm::vec4(0.469f, 0.469f, 0.469f, 1.000f);
			result->m_HeaderActive = glm::vec4(0.469f, 0.469f, 0.469f, 1.000f);
			result->m_Separator = result->m_Border;
			result->m_SeparatorHovered = glm::vec4(0.391f, 0.391f, 0.391f, 1.000f);
			result->m_SeparatorActive = glm::vec4(1.000f, 0.391f, 0.000f, 1.000f);
			result->m_ResizeGrip = glm::vec4(1.000f, 1.000f, 1.000f, 0.250f);
			result->m_ResizeGripHovered = glm::vec4(1.000f, 1.000f, 1.000f, 0.670f);
			result->m_ResizeGripActive = glm::vec4(1.000f, 0.391f, 0.000f, 1.000f);
			result->m_Tab = glm::vec4(0.098f, 0.098f, 0.098f, 1.000f);
			result->m_TabHovered = glm::vec4(0.352f, 0.352f, 0.352f, 1.000f);
			result->m_TabActive = glm::vec4(0.195f, 0.195f, 0.195f, 1.000f);
			result->m_TabUnfocused = glm::vec4(0.098f, 0.098f, 0.098f, 1.000f);
			result->m_TabUnfocusedActive = glm::vec4(0.195f, 0.195f, 0.195f, 1.000f);
			result->m_DockingPreview = glm::vec4(1.000f, 0.391f, 0.000f, 0.781f);
			result->m_DockingEmptyBg = glm::vec4(0.180f, 0.180f, 0.180f, 1.000f);
			result->m_PlotLines = glm::vec4(0.469f, 0.469f, 0.469f, 1.000f);
			result->m_PlotLinesHovered = glm::vec4(1.000f, 0.391f, 0.000f, 1.000f);
			result->m_PlotHistogram = glm::vec4(0.586f, 0.586f, 0.586f, 1.000f);
			result->m_PlotHistogramHovered = glm::vec4(1.000f, 0.391f, 0.000f, 1.000f);
			result->m_TextSelectedBg = glm::vec4(1.000f, 1.000f, 1.000f, 0.156f);
			result->m_DragDropTarget = glm::vec4(1.000f, 0.391f, 0.000f, 1.000f);
			result->m_NavHighlight = glm::vec4(1.000f, 0.391f, 0.000f, 1.000f);
			result->m_NavWindowingHighlight = glm::vec4(1.000f, 0.391f, 0.000f, 1.000f);
			result->m_NavWindowingDimBg = glm::vec4(0.000f, 0.000f, 0.000f, 0.586f);
			result->m_ModalWindowDimBg = glm::vec4(0.000f, 0.000f, 0.000f, 0.586f);

			return result;
		}
		std::map<std::string, StyleColor*> m_Themes = {
			{"Light", LightTheme()},
			{"Dark", DarkTheme()},
			{"Classic", ClassicTheme()},
			{"Tara", TaraTheme()},
		};
		bool ImGui_RegisterTheme(const char* name, StyleColor* theme)
		{
			if (!m_Themes.count(name)) {
				m_Themes[name] = theme;
				return true;
			}
			return false;
		}
		std::vector<std::pair<std::string, StyleColor*>> ImGui_RegisteredTheme()
		{
			std::vector<std::pair<std::string, StyleColor*>> result = std::vector<std::pair<std::string, StyleColor*>>();
			for (auto& i : m_Themes) {
				result.push_back(i);
			}
			return result;
		}
		StyleColor* ImGui_GetRegisteredTheme(const char* name)
		{
			if (!m_Themes.count( name)) {
				return nullptr;
			}
			return m_Themes.at(name);
		}
		void ImGui_SetLightTheme(bool save) {
			EditorStyle& es = EditorStyle::Singleton();
			StyleColor* c = ImGui_GetRegisteredTheme("Light");
			es.SubmitStyle(*c);
			if (save) es.Save(EDITOR_STYLE_FILE);
		}
		void ImGui_SetDarkTheme(bool save) {
			EditorStyle& es = EditorStyle::Singleton();
			StyleColor* c = ImGui_GetRegisteredTheme("Dark");
			es.SubmitStyle(*c);
			if (save) es.Save(EDITOR_STYLE_FILE);
		}
		void ImGui_SetClassicTheme(bool save) {
			EditorStyle& es = EditorStyle::Singleton();
			StyleColor* c = ImGui_GetRegisteredTheme("Classic");
			es.SubmitStyle(*c);
			if(save) es.Save(EDITOR_STYLE_FILE);
		}
		void ImGui_SetTaraTheme(bool save)
		{
			EditorStyle& es = EditorStyle::Singleton();
			StyleColor* c = ImGui_GetRegisteredTheme("Tara");
			es.SubmitStyle(*c);
			if(save) es.Save(EDITOR_STYLE_FILE);
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
		void ImGui_BorderColor(glm::vec4 color) {
			ImGui_BorderColor(color.r, color.g, color.b, color.a);
		}
		void ImGui_BorderColor(glm::vec3 color) {
			ImGui_BorderColor(color.r, color.g, color.b, 1);
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
		void ImGui_TitleBgColor(glm::vec4 color) {
			ImGui_TitleBgColor(color.r, color.g, color.b, color.a);
		}
		void ImGui_TitleBgColor(glm::vec3 color) {
			ImGui_TitleBgColor(color.r, color.g, color.b, 1);
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
		void ImGui_HeaderColor(glm::vec4 color) {
			ImGui_HeaderColor(color.r, color.g, color.b, color.a);
		}
		void ImGui_HeaderColor(glm::vec3 color) {
			ImGui_HeaderColor(color.r, color.g, color.b, 1);
		}

		void ImGui_HeaderHoveredColor(float r, float g, float b, float a)
		{
			ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(r, g, b, a));
		}
		void ImGui_HeaderHoveredColor(glm::vec4 color) {
			ImGui_HeaderHoveredColor(color.r, color.g, color.b, color.a);
		}
		void ImGui_HeaderHoveredColor(glm::vec3 color) {
			ImGui_HeaderHoveredColor(color.r, color.g, color.b, 1);
		}

		void ImGui_HeaderActiveColor(float r, float g, float b, float a)
		{
			ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(r, g, b, a));
		}
		void ImGui_HeaderActiveColor(glm::vec4 color) {
			ImGui_HeaderActiveColor(color.r, color.g, color.b, color.a);
		}
		void ImGui_HeaderActiveColor(glm::vec3 color) {
			ImGui_HeaderActiveColor(color.r, color.g, color.b, 1);
		}

		void ImGui_NavHighlightColor(float r, float g, float b, float a)
		{
			ImGui::PushStyleColor(ImGuiCol_NavHighlight, ImVec4(r, g, b, a));
		}
		void ImGui_TableRowBg(float r, float g, float b, float a)
		{
			ImGui::PushStyleColor(ImGuiCol_TableRowBg, ImVec4(r, g, b, a));
		}
		void ImGui_TableRowBg(glm::vec4 color) {
			ImGui_TableRowBg(color.r, color.g, color.b, color.a);
		}
		void ImGui_TableRowBg(glm::vec3 color) {
			ImGui_TableRowBg(color.r, color.g, color.b, 1);
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
}