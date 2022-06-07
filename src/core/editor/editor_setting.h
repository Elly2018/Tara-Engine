#pragma once
#include <map>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
#include "editor_config.h"

namespace Tara {
	namespace UI {
		enum class TARA_EDITOR_API Direction {
			None = -1,
			Left = 0,
			Right = 1,
			Up = 2,
			Down = 3,
		};

		struct TARA_EDITOR_API StyleColor {
		public:
			const size_t COUNT = 55;
			glm::vec4 m_TextColor = glm::vec4();
			glm::vec4 m_TextDisabled = glm::vec4();
			glm::vec4 m_WindowBg = glm::vec4();
			glm::vec4 m_ChildBg = glm::vec4();
			glm::vec4 m_PopupBg = glm::vec4();
			glm::vec4 m_Border = glm::vec4();
			glm::vec4 m_BorderShadow = glm::vec4();
			glm::vec4 m_FrameBg = glm::vec4();
			glm::vec4 m_FrameBgHovered = glm::vec4();
			glm::vec4 m_FrameBgActive = glm::vec4();
			glm::vec4 m_TitleBg = glm::vec4();
			glm::vec4 m_TitleBgActive = glm::vec4();
			glm::vec4 m_TitleBgCollapsed = glm::vec4();
			glm::vec4 m_MenuBarBg = glm::vec4();
			glm::vec4 m_ScrollbarBg = glm::vec4();
			glm::vec4 m_ScrollbarGrab = glm::vec4();
			glm::vec4 m_ScrollbarGrabHovered = glm::vec4();
			glm::vec4 m_ScrollbarGrabActive = glm::vec4();
			glm::vec4 m_CheckMark = glm::vec4();
			glm::vec4 m_SliderGrab = glm::vec4();
			glm::vec4 m_SliderGrabActive = glm::vec4();
			glm::vec4 m_Button = glm::vec4();
			glm::vec4 m_ButtonHovered = glm::vec4();
			glm::vec4 m_ButtonActive = glm::vec4();
			glm::vec4 m_Header = glm::vec4();
			glm::vec4 m_HeaderHovered = glm::vec4();
			glm::vec4 m_HeaderActive = glm::vec4();
			glm::vec4 m_Separator = glm::vec4();
			glm::vec4 m_SeparatorHovered = glm::vec4();
			glm::vec4 m_SeparatorActive = glm::vec4();
			glm::vec4 m_ResizeGrip = glm::vec4();
			glm::vec4 m_ResizeGripHovered = glm::vec4();
			glm::vec4 m_ResizeGripActive = glm::vec4();
			glm::vec4 m_Tab = glm::vec4();
			glm::vec4 m_TabHovered = glm::vec4();
			glm::vec4 m_TabActive = glm::vec4();
			glm::vec4 m_TabUnfocused = glm::vec4();
			glm::vec4 m_TabUnfocusedActive = glm::vec4();
			glm::vec4 m_DockingPreview = glm::vec4();
			glm::vec4 m_DockingEmptyBg = glm::vec4();
			glm::vec4 m_PlotLines = glm::vec4();
			glm::vec4 m_PlotLinesHovered = glm::vec4();
			glm::vec4 m_PlotHistogram = glm::vec4();
			glm::vec4 m_PlotHistogramHovered = glm::vec4();
			glm::vec4 m_TableHeaderBg = glm::vec4();
			glm::vec4 m_TableBorderStrong = glm::vec4();
			glm::vec4 m_TableBorderLight = glm::vec4();
			glm::vec4 m_TableRowBg = glm::vec4();
			glm::vec4 m_TableRowBgAlt = glm::vec4();
			glm::vec4 m_TextSelectedBg = glm::vec4();
			glm::vec4 m_DragDropTarget = glm::vec4();
			glm::vec4 m_NavHighlight = glm::vec4();
			glm::vec4 m_NavWindowingHighlight = glm::vec4();
			glm::vec4 m_NavWindowingDimBg = glm::vec4();
			glm::vec4 m_ModalWindowDimBg = glm::vec4();

			void Set(int32_t index, glm::vec4 v);
			glm::vec4 Get(int32_t index);

			bool operator==(const StyleColor& tar);
			bool operator!=(const StyleColor& tar);
		};

		struct TARA_EDITOR_API StyleVar {
		public:
			float_t			Alpha;
			float_t			DisabledAlpha;
			glm::vec2		WindowPadding;
			float_t			WindowRounding;
			float_t			WindowBorderSize;
			glm::vec2		WindowMinSize;
			glm::vec2		WindowTitleAlign;
			Direction		WindowMenuButtonPosition;
			float_t			ChildRounding;
			float_t			ChildBorderSize;
			float_t			PopupRounding;
			float_t			PopupBorderSize;
			glm::vec2		FramePadding;
			float			FrameRounding;
			float			FrameBorderSize;
			glm::vec2		ItemSpacing;
			glm::vec2		ItemInnerSpacing;
			glm::vec2		CellPadding;
			glm::vec2		TouchExtraPadding;
			float_t			IndentSpacing;
			float_t			ColumnsMinSpacing;
			float_t			ScrollbarSize;
			float_t			ScrollbarRounding;
			float_t			GrabMinSize;
			float_t			GrabRounding;
			float_t			LogSliderDeadzone;
			float_t			TabRounding;
			float_t			TabBorderSize;
			float_t			TabMinWidthForCloseButton;
			Direction		ColorButtonPosition;
			glm::vec2		ButtonTextAlign;
			glm::vec2		SelectableTextAlign;
			glm::vec2		DisplayWindowPadding;
			glm::vec2		DisplaySafeAreaPadding;
			float_t			MouseCursorScale;
			bool			AntiAliasedLines;
			bool			AntiAliasedLinesUseTex;
			bool			AntiAliasedFill;
			float			CurveTessellationTol;
			float			CircleTessellationMaxError;

			bool operator==(const StyleVar& tar);
			bool operator!=(const StyleVar& tar);
		};

		class TARA_EDITOR_API EditorStyle {
		public:
			static EditorStyle& Singleton();
			bool Load(const char* filename);
			bool Save(const char* dest);
			bool Apply();
			bool ApplyStyle();
			bool SubmitStyle(StyleColor col);
			bool ApplyVar();
			bool SubmitVar(StyleVar v);
			void LoadInstance();

			StyleColor colors = StyleColor();
			StyleVar vars = StyleVar();

		private:
			static EditorStyle* m_Singleton;
			nlohmann::json SaveColor();
			nlohmann::json SaveVar();
			bool LoadColor(nlohmann::json json);
			bool LoadVar(nlohmann::json json);
		};
	}
}

