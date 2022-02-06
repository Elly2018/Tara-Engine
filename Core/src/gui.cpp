#include <gui.h>
#include <string>
#include <stdarg.h>
#ifndef TARA_NO_IMGUI
//#define GLFW_INCLUDE_NONE
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <cstdarg>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <einput.h>
#undef GLFW_INCLUDE_NONE

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace Tara {
	ImGui_ChangeViewport m_ImGui_ChangeViewport;
	namespace UI {
	
		#pragma region Struct implementation
		int32_t ImGui_FlagBase::GetFlags()
		{
			return int32_t();
		}
		int32_t ImGui_WindiwFlags::GetFlags()
		{
			int32_t buffer = 0;
			if (NoTitleBar) buffer |= ImGuiWindowFlags_NoTitleBar;
			if (NoResize) buffer |= ImGuiWindowFlags_NoResize;
			if (NoMove) buffer |= ImGuiWindowFlags_NoMove;
			if (NoScrollbar) buffer |= ImGuiWindowFlags_NoScrollbar;
			if (NoScrollWithMouse) buffer |= ImGuiWindowFlags_NoScrollWithMouse;
			if (NoCollapse) buffer |= ImGuiWindowFlags_NoCollapse;
			if (AlwaysAutoResize) buffer |= ImGuiWindowFlags_NoCollapse;
			if (NoBackground) buffer |= ImGuiWindowFlags_NoBackground;
			if (UnSave) buffer |= ImGuiWindowFlags_UnsavedDocument;
			if (NoMouseInput) buffer |= ImGuiWindowFlags_NoMouseInputs;
			if (MenuBar) buffer |= ImGuiWindowFlags_MenuBar;
			if (HorizontalScrollbar) buffer |= ImGuiWindowFlags_HorizontalScrollbar;
			if (NoFocusOnAppearing) buffer |= ImGuiWindowFlags_NoFocusOnAppearing;
			if (NoBringToFrontOnFocus) buffer |= ImGuiWindowFlags_NoBringToFrontOnFocus;
			if (AlwaysVerticalScrollbar) buffer |= ImGuiWindowFlags_AlwaysVerticalScrollbar;
			if (AlwaysHorizontalScrollbar) buffer |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;
			if (AlwaysUseWindowPadding) buffer |= ImGuiWindowFlags_AlwaysUseWindowPadding;
			if (NoNavInputs) buffer |= ImGuiWindowFlags_NoNavInputs;
			if (NoNavFocus) buffer |= ImGuiWindowFlags_NoNavFocus;
			if (UnsaveDocumentDot) buffer |= ImGuiWindowFlags_UnsavedDocument;

			if (NoDocking) buffer |= ImGuiWindowFlags_NoDocking;

			if (NoNav) buffer |= ImGuiWindowFlags_NoNav;
			if (NoDecoration) buffer |= ImGuiWindowFlags_NoDecoration;
			if (NoInputs) buffer |= ImGuiWindowFlags_NoInputs;
			return buffer;
		}
		int32_t ImGui_ConditionFlags::GetFlags()
		{
			int32_t buffer = 0;
			if (Always) buffer |= ImGuiCond_Always;
			if (Once) buffer |= ImGuiCond_Once;
			if (FirstUseEver) buffer |= ImGuiCond_FirstUseEver;
			if (Appearing) buffer |= ImGuiCond_Appearing;
			return buffer;
		}
		int32_t ImGui_TableFlags::GetFlags()
		{
			int32_t buffer = 0;
			if (ReSizeble) buffer |= ImGuiTableFlags_Resizable;
			if (ReOrderable) buffer |= ImGuiTableFlags_Reorderable;
			if (Hideable) buffer |= ImGuiTableFlags_Hideable;
			if (Sortable) buffer |= ImGuiTableFlags_Sortable;
			if (NoSave) buffer |= ImGuiTableFlags_NoSavedSettings;
			if (ContextMenuInBody) buffer |= ImGuiTableFlags_ContextMenuInBody;

			if (RowBG) buffer |= ImGuiTableFlags_RowBg;
			if (BordersInnerH) buffer |= ImGuiTableFlags_BordersInnerH;
			if (BordersOuterH) buffer |= ImGuiTableFlags_BordersOuterH;
			if (BordersInnerV) buffer |= ImGuiTableFlags_BordersInnerV;
			if (BordersOuterV) buffer |= ImGuiTableFlags_BordersOuterV;
			if (NoBordersInBody) buffer |= ImGuiTableFlags_NoBordersInBody;
			if (NoBordersInBodyUntilResize) buffer |= ImGuiTableFlags_NoBordersInBodyUntilResize;

			if (SizingFixedFit) buffer |= ImGuiTableFlags_SizingFixedFit;
			if (SizingFixedSame) buffer |= ImGuiTableFlags_SizingFixedSame;
			if (SizingStretchProp) buffer |= ImGuiTableFlags_SizingStretchProp;
			if (SizingStretchSame) buffer |= ImGuiTableFlags_SizingStretchSame;

			if (NoHostExtendX) buffer |= ImGuiTableFlags_NoHostExtendX;
			if (NoHostExtendY) buffer |= ImGuiTableFlags_NoHostExtendY;
			if (NoKeepColumnVisible) buffer |= ImGuiTableFlags_NoKeepColumnsVisible;
			if (PreciseWidths) buffer |= ImGuiTableFlags_PreciseWidths;

			if (NoClip) buffer |= ImGuiTableFlags_NoClip;

			if (PadOuterX) buffer |= ImGuiTableFlags_PadOuterX;
			if (NoPadOuterX) buffer |= ImGuiTableFlags_NoPadOuterX;
			if (NoPadInnerX) buffer |= ImGuiTableFlags_NoPadInnerX;

			if (ScrollX) buffer |= ImGuiTableFlags_ScrollX;
			if (ScrollY) buffer |= ImGuiTableFlags_ScrollY;

			if (SortMulti) buffer |= ImGuiTableFlags_SortMulti;
			if (SortTristate) buffer |= ImGuiTableFlags_SortTristate;
			return buffer;
		}
		int32_t ImGui_TabFlagsFitting::GetFlags()
		{
			int32_t buffer = 0;
			if (Resizedown) buffer |= ImGuiTabBarFlags_FittingPolicyResizeDown;
			if (Scroll) buffer |= ImGuiTabBarFlags_FittingPolicyScroll;
			return buffer;
		}
		int32_t ImGui_ComboFlags::GetFlags()
		{
			int32_t buffer = 0;
			if (PopupAlignLeft) buffer |= ImGuiComboFlags_PopupAlignLeft;
			if (HeightSmall) buffer |= ImGuiComboFlags_HeightSmall;
			if (HeightHeightRegular) buffer |= ImGuiComboFlags_HeightRegular;
			if (HeightHeightLarge) buffer |= ImGuiComboFlags_HeightLarge;
			if (HeightHeightLargest) buffer |= ImGuiComboFlags_HeightLargest;
			if (NoArrowButton) buffer |= ImGuiComboFlags_NoArrowButton;
			if (NoPreview) buffer |= ImGuiComboFlags_NoPreview;
			return buffer;
		}
		int32_t ImGui_TabFlags::GetFlags()
		{
			int32_t buffer = 0;
			if (ReOrderable) buffer |= ImGuiTabBarFlags_Reorderable;
			if (AutoSelectTab) buffer |= ImGuiTabBarFlags_AutoSelectNewTabs;
			if (TabListPopupButton) buffer |= ImGuiTabBarFlags_TabListPopupButton;
			if (NoCloseMiddleMouse) buffer |= ImGuiTabBarFlags_NoCloseWithMiddleMouseButton;
			if (NoTabListScrolling) buffer |= ImGuiTabBarFlags_NoTabListScrollingButtons;
			if (NoTooltop) buffer |= ImGuiTabBarFlags_NoTooltip;
			buffer |= fittingpolicy.GetFlags();
			return buffer;
		}
		int32_t ImGui_TabitemsFlags::GetFlags()
		{
			int32_t buffer = 0;
			if (UnSave) buffer != ImGuiTabItemFlags_UnsavedDocument;
			if (SetSelect) buffer != ImGuiTabItemFlags_SetSelected;
			if (NoCloseMiddleMouse) buffer != ImGuiTabItemFlags_NoCloseWithMiddleMouseButton;
			if (NoPushID) buffer != ImGuiTabItemFlags_NoPushId;
			if (NoTooltip) buffer != ImGuiTabItemFlags_NoTooltip;
			if (NoReOrder) buffer != ImGuiTabItemFlags_NoReorder;
			if (Leading) buffer != ImGuiTabItemFlags_Leading;
			if (Trailing) buffer != ImGuiTabItemFlags_Trailing;
			return buffer;
		}
		int32_t ImGui_PopupFlags::GetFlags()
		{
			return int32_t();
		}
		#pragma endregion

		#pragma region Style
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
		#pragma endregion

		#pragma region Gui Func
		void ImGui_Initialization(const char* version, void* window)
		{
			GLFWwindow* w = (GLFWwindow*)window;
			if (!w) {
				TARA_RUNTIME_ERROR("ImGui failed to initialization.");
				return;
			}
			TARA_DEBUG("%s: %s", "Imgui gui version", ImGui::GetVersion());
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Gamepad Controls
			//io.ConfigViewportsNoAutoMerge = true;
			//io.ConfigViewportsNoTaskBarIcon = true;

			// Setup Dear ImGui style
			ImGui_SetTaraTheme();
			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}


			// Setup Platform/Renderer backends
			ImGui_ImplGlfw_InitForOpenGL(w, true);
			ImGui_ImplOpenGL3_Init(version);

			// Load Fonts
			// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
			// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
			// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
			// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
			// - Read 'docs/FONTS.md' for more instructions and details.
			// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
			io.Fonts->AddFontDefault();
			//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
			//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
			//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
			//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
			//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
			//IM_ASSERT(font != NULL);
		}
		void ImGui_ViewportCallback(ImGui_ChangeViewport callback)
		{
			m_ImGui_ChangeViewport = callback;
		}
		void ImGui_NewFrame()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
		void ImGui_Render(void* window)
		{
			GLFWwindow* w = (GLFWwindow*)window;
			if (!w) {
				TARA_RUNTIME_ERROR("ImGui window casting error.");
				return;
			}

			ImGui::Render();
			if (m_ImGui_ChangeViewport != nullptr) {
				int display_w, display_h;
				glfwGetFramebufferSize(w, &display_w, &display_h);
				m_ImGui_ChangeViewport(0, 0, display_w, display_h);
			}
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
		}
		void ImGui_Destroy()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		bool ImGui_Begin(const char* title, bool* open, ImGui_WindiwFlags flags)
		{
			return ImGui::Begin(title, open, flags.GetFlags());
		}
		bool ImGui_BeginChild(const char* title, float_t w, float_t h, bool border, ImGui_WindiwFlags flags)
		{
			return ImGui::BeginChild(title, ImVec2(w, h), border, flags.GetFlags());
		}
		bool ImGui_BeginCombo(const char* title, const char* preview, ImGui_ComboFlags flags)
		{
			return ImGui::BeginCombo(title, preview, flags.GetFlags());
		}
		void ImGui_BeginDisabled(bool disabled)
		{
			return ImGui::BeginDisabled(disabled);
		}
		bool ImGui_BeginFrame()
		{
			return false;
		}
		void ImGui_BeginGroup()
		{
			return ImGui::BeginGroup();
		}
		bool ImGui_BeginMainmenuBar()
		{
			return ImGui::BeginMainMenuBar();
		}
		bool ImGui_BeginMenu(const char* label, bool enable)
		{
			return ImGui::BeginMenu(label, enable);
		}
		bool ImGui_BeginMenubar()
		{
			return ImGui::BeginMenuBar();
		}
		bool ImGui_BeginTabBar(const char* title, ImGui_TabFlags flags)
		{
			return ImGui::BeginTabBar(title, flags.GetFlags());
		}
		bool ImGui_BeginTabitems(const char* title, bool* open, ImGui_TabitemsFlags flags)
		{
			return ImGui::BeginTabItem(title, open, flags.GetFlags());
		}

		bool ImGui_BeginTable(const char* title, int column, ImGui_TableFlags flags, glm::vec2 outterSize, float innerWidth)
		{
			return ImGui::BeginTable(title, column, flags.GetFlags(), ImVec2(outterSize.x, outterSize.y), innerWidth);
		}

		bool ImGui_BeginListbox()
		{
			return false;
		}

		void ImGui_BeginTooltip()
		{
			ImGui::BeginTooltip();
		}

		bool ImGui_BeginPopup(const char* title, ImGui_WindiwFlags flags)
		{
			return ImGui::BeginPopup(title, flags.GetFlags());
		}

		bool ImGui_BeginPopupContextItem()
		{
			return false;
		}

		bool ImGui_BeginPopupContextVoid()
		{
			return false;
		}

		bool ImGui_BeginPopupContextWindow()
		{
			return false;
		}

		bool ImGui_BeginPopupModal(const char* title, bool* open, ImGui_WindiwFlags flags)
		{
			return ImGui::BeginPopupModal(title, open, flags.GetFlags());
		}

		bool ImGui_BeginDrag()
		{
			return false;
		}

		bool ImGui_BeginDrop()
		{
			return false;
		}

		void ImGui_End()
		{
			ImGui::End();
		}
		void ImGui_EndChild()
		{
			ImGui::EndChild();
		}
		void ImGui_EndCombo()
		{
			ImGui::EndCombo();
		}
		void ImGui_EndDisabled()
		{
			ImGui::EndDisabled();
		}
		void ImGui_EndFrame()
		{
			ImGui::EndChildFrame();
		}
		void ImGui_EndGroup()
		{
			ImGui::EndGroup();
		}
		void ImGui_EndMainmenuBar()
		{
			ImGui::EndMainMenuBar();
		}
		void ImGui_EndMenu()
		{
			ImGui::EndMenu();
		}
		void ImGui_EndMenubar()
		{
			ImGui::EndMenuBar();
		}
		void ImGui_EndTabBar()
		{
			ImGui::EndTabBar();
		}
		void ImGui_EndTabitems()
		{
			ImGui::EndTabItem();
		}
		void ImGui_EndTable()
		{
			ImGui::EndTable();
		}
		void ImGui_EndListbox()
		{
			ImGui::EndListBox();
		}
		void ImGui_EndTooltip()
		{
			ImGui::EndTooltip();
		}
		void ImGui_EndPopup()
		{
			ImGui::EndPopup();
		}
		void ImGui_EndDrag()
		{
			ImGui::EndDragDropSource();
		}
		void ImGui_EndDrop()
		{
			ImGui::EndDragDropTarget();
		}

		void ImGui_SetNextWindowSize(float_t x, float_t y, ImGui_ConditionFlags cond)
		{
			ImGui::SetNextWindowSize(ImVec2(x, y), cond.GetFlags());
		}
		void ImGui_SetNextWindowSize(glm::vec2 size, ImGui_ConditionFlags cond)
		{
			ImGui::SetNextWindowSize(ImVec2(size.x, size.y), cond.GetFlags());
		}
		void ImGui_SetNextWindowPos(glm::vec2 pos, ImGui_ConditionFlags cond, glm::vec2 pivot)
		{
			ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y), cond.GetFlags(), ImVec2(pivot.x, pivot.y));
		}
		void ImGui_SetNextWindowPos(float_t x, float_t y, ImGui_ConditionFlags cond, float_t p_x, float_t p_y)
		{
			ImGui::SetNextWindowPos(ImVec2(x, y), cond.GetFlags(), ImVec2(p_x, p_y));
		}
		void ImGui_SetCursor(float_t x, float_t y)
		{
			ImGui::SetCursorPos(ImVec2(x, y));
		}
		void ImGui_SetCursor(glm::vec2 pos)
		{
			ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
		}
		void ImGui_SetClipboard(const char* text)
		{
			ImGui::SetClipboardText(text);
		}
		void ImGui_SetItemOpen(bool open, ImGui_ConditionFlags cond)
		{
			ImGui::SetNextItemOpen(open, cond.GetFlags());
		}
		void ImGui_SetItemWidth(float_t width)
		{
			ImGui::SetNextItemWidth(width);
		}
		void ImGui_SetColumnOffset(int32_t index, float_t offset)
		{
			ImGui::SetColumnOffset(index, offset);
		}
		void ImGui_SetColumnWidth(int32_t index, float_t width)
		{
			ImGui::SetColumnWidth(index, width);
		}
		void ImGui_SetScrollHereX(float_t v)
		{
			ImGui::SetScrollHereX(v);
		}
		void ImGui_SetScrollHereY(float_t v)
		{
			ImGui::SetScrollHereY(v);
		}
		void ImGui_SetTreeNodeOpen(bool open, ImGui_ConditionFlags cond)
		{
			ImGui::SetNextTreeNodeOpen(open, cond.GetFlags());
		}

		glm::vec2 ImGui_GetWindowSize()
		{
			ImVec2 v = ImGui::GetWindowSize();
			return glm::vec2(v.x, v.y);
		}
		glm::vec2 ImGui_GetWindowPos()
		{
			ImVec2 v = ImGui::GetWindowPos();
			return glm::vec2(v.x, v.y);
		}
		glm::vec2 ImGui_GetItemSize()
		{
			ImVec2 n = ImGui::GetItemRectSize();
			return glm::vec2(n.x, n.y);
		}
		glm::vec2 ImGui_GetItemMin()
		{
			ImVec2 n = ImGui::GetItemRectMin();
			return glm::vec2(n.x, n.y);
		}
		glm::vec2 ImGui_GetItemMax()
		{
			ImVec2 n = ImGui::GetItemRectMax();
			return glm::vec2(n.x, n.y);
		}
		const char* ImGui_GetVersion()
		{
			return ImGui::GetVersion();
		}
		glm::vec2 ImGui_GetCursor()
		{
			ImVec2 n = ImGui::GetCursorPos();
			return glm::vec2(n.x, n.y);
		}
		const char* ImGui_GetClipboard()
		{
			return ImGui::GetClipboardText();
		}
		glm::vec2 ImGui_GetDragDelta(MouseButton button, float_t lock_threshold)
		{
			ImVec2 n = ImGui::GetMouseDragDelta((int32_t)button, lock_threshold);
			return glm::vec2(n.x, n.y);
		}
		float_t ImGui_GetColumnOffset(int32_t index)
		{
			return ImGui::GetColumnOffset(index);
		}
		float_t ImGui_GetColumnWidth(int32_t index)
		{
			return ImGui::GetColumnWidth(index);
		}
		int32_t ImGui_GetColumnsCount()
		{
			return ImGui::GetColumnsCount();
		}
		float_t ImGui_GetScrollX()
		{
			return ImGui::GetScrollX();
		}
		float_t ImGui_GetScrollY()
		{
			return ImGui::GetScrollY();
		}
		float_t ImGui_GetScrollMaxX()
		{
			return ImGui::GetScrollMaxX();
		}
		float_t ImGui_GetScrollMaxY()
		{
			return ImGui::GetScrollMaxY();
		}

		uint32_t ImGui_DockspaceOverviewport()
		{
			return ImGui::DockSpaceOverViewport(0, 8);
		}
		uint32_t ImGui_GetDockID()
		{
			return ImGui::GetWindowDockID();
		}
		void ImGui_SetNextDockID(uint32_t id, ImGui_ConditionFlags cond)
		{
			ImGui::SetNextWindowDockID(id, cond.GetFlags());
		}

		void ImGui_RenderImage(void* rendertexture)
		{
			ImGui::GetWindowDrawList()->AddImage(
				rendertexture, ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowHeight() / 2, ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight() / 2),
				ImVec2(0, 1), ImVec2(1, 0));
		}
		bool ImGui_MenuItem(const char* label, const char* shortcut, bool* select, bool enable)
		{
			return ImGui::MenuItem(label, shortcut, select, enable);
		}
		bool ImGui_MenuItem(const char* label, const char* shortcut, bool enable)
		{
			return ImGui::MenuItem(label, shortcut, enable);
		}
		bool ImGui_TextField(const char* text, char* buf, size_t size)
		{
			return ImGui::InputText(text, buf, 1, size);
		}
		bool ImGui_TextFieldWithHint(const char* text, const char* hint, char* buf, size_t buf_size)
		{
			return ImGui::InputTextWithHint(text, hint, buf, buf_size);
		}
		bool ImGui_TextFieldMutiline(const char* text, char* buf, size_t buf_size, glm::vec2 size)
		{
			return ImGui::InputTextMultiline(text, buf, buf_size);
		}
		void ImGui_Text(const char* text, ...)
		{
			va_list args;
			va_start(args, text);
			ImGui::TextV(text, args);
			va_end(args);
		}
		void ImGui_LabelText(const char* title, const char* text, ...)
		{
			va_list args;
			va_start(args, text);
			ImGui::LabelTextV(title, text, args);
			va_end(args);
		}
		void ImGui_TextUnformatted(const char* text, const char* end)
		{
			ImGui::TextUnformatted(text, end);
		}
		void ImGui_Bullet()
		{
			ImGui::Bullet();
		}
		void ImGui_BulletText(const char* text, ...)
		{
			va_list args;
			va_start(args, text);
			ImGui::BulletTextV(text, args);
			va_end(args);
		}
		void ImGui_Image(void* image, float_t w, float_t h, float_t uv_x, float_t uv_y, float_t uv2_x, float_t uv2_y)
		{
			ImGui::Image(image, ImVec2(w, h), ImVec2(uv_x, uv_y), ImVec2(uv2_x, uv2_y));
		}
		void ImGui_Image(void* image, glm::vec2 size, glm::vec2 uv, glm::vec2 uv2)
		{
			ImGui_Image(image, size.x, size.y, uv.x, uv.y, uv2.x, uv2.y);
		}
		void ImGui_Image(CCamera* image, float_t w, float_t h, float_t uv_x, float_t uv_y, float_t uv2_x, float_t uv2_y)
		{
			glm::ivec2 size = CurrentWindow()->GetEWindowSize();
			ImGui_Image((void*)image->TextureID(), w, h, uv_x, uv_y, uv2_x, uv2_y);
		}
		void ImGui_Image(CCamera* image, glm::vec2 size, glm::vec2 uv, glm::vec2 uv2)
		{
			ImGui_Image((void*)image->TextureID(), size.x, size.y, uv.x, uv.y, uv2.x, uv2.y);
		}
		void ImGui_Image(Texture* image, float_t w, float_t h, float_t uv_x, float_t uv_y, float_t uv2_x, float_t uv2_y)
		{
			ImGui_Image((void*)image->ID(), w, h, uv_x, uv_y, uv2_x, uv2_y);
		}
		void ImGui_Image(Texture* image, glm::vec2 size, glm::vec2 uv, glm::vec2 uv2)
		{
			ImGui_Image((void*)image->ID(), size.x, size.y, uv.x, uv.y, uv2.x, uv2.y);
		}
		void ImGui_Image(FrameBuffer* image, float_t w, float_t h, float_t uv_x, float_t uv_y, float_t uv2_x, float_t uv2_y)
		{
			ImGui_Image((void*)image->GetTextureID(), w, h, uv_x, uv_y, uv2_x, uv2_y);
		}
		void ImGui_Image(FrameBuffer* image, glm::vec2 size, glm::vec2 uv, glm::vec2 uv2)
		{
			ImGui_Image((void*)image->GetTextureID(), size.x, size.y, uv.x, uv.y, uv2.x, uv2.y);
		}
		bool ImGui_ImageButton(void* image, glm::vec2 size, glm::vec2 uv, glm::vec2 uv2)
		{
			return ImGui::ImageButton(image, ImVec2(size.x, size.y), ImVec2(uv.x, uv.y), ImVec2(uv2.x, uv2.y));
		}
		bool ImGui_ImageButton(void* image, float_t w, float_t h, float_t uv_x, float_t uv_y, float_t uv2_x, float_t uv2_y)
		{
			return ImGui::ImageButton(image, ImVec2(w, h), ImVec2(uv_x, uv_y), ImVec2(uv2_x, uv2_y));
		}
		bool ImGui_Button(const char* title)
		{
			return ImGui::Button(title);
		}
		bool ImGui_ButtonArrow(const char* title, arrowdirection dir)
		{
			return ImGui::ArrowButton(title, (int)dir);
		}
		bool ImGui_ButtonSmall(const char* title)
		{
			return ImGui::SmallButton(title);
		}
		bool ImGui_ButtonRadio(const char* title, bool active)
		{
			return ImGui::RadioButton(title, active);
		}
		bool ImGui_ButtonRadio(const char* title, int32_t* current, int32_t button_id)
		{
			return ImGui::RadioButton(title, current, button_id);
		}
		void ImGui_Dummy(glm::vec2 size)
		{
			ImGui::Dummy(ImVec2(size.x, size.y));
		}
		void ImGui_Dummy(float_t w, float_t h)
		{
			ImGui::Dummy(ImVec2(w, h));
		}
		bool ImGui_Checkbox(const char* title, bool* v)
		{
			return ImGui::Checkbox(title, v);
		}
		bool ImGui_CheckboxFlags(const char* title, int32_t* flags, int32_t v_flag)
		{
			return ImGui::CheckboxFlags(title, flags, v_flag);
		}
		void ImGui_Space()
		{
			ImGui::Spacing();
		}
		bool ImGui_Combo(const char* title, int32_t* current, const char* const items, size_t size)
		{
			return ImGui::Combo(title, current, items, size);
		}
		void ImGui_Plot()
		{

		}
		void ImGui_Table()
		{

		}
		bool ImGui_CollapsingHeader(const char* title, bool* visible)
		{
			return ImGui::CollapsingHeader(title, visible);
		}
		void ImGui_Indent(int32_t w)
		{
			ImGui::Indent(w);
		}
		void ImGui_UnIndent(int32_t w)
		{
			ImGui::Unindent(w);
		}
		void ImGui_Separator()
		{
			ImGui::Separator();
		}
		bool ImGui_InputFloat(const char* title, float_t* value)
		{
			return ImGui::InputFloat(title, value);
		}
		bool ImGui_InputVec2(const char* title, float_t value[2])
		{
			return ImGui::InputFloat2(title, &value[0]);
		}
		bool ImGui_InputVec2(const char* title, glm::vec2* value)
		{
			return ImGui::InputFloat2(title, &value->x);
		}
		bool ImGui_InputVec3(const char* title, float_t value[3])
		{
			return ImGui::InputFloat3(title, &value[0]);
		}
		bool ImGui_InputVec3(const char* title, glm::vec3* value)
		{
			return ImGui::InputFloat3(title, &value->x);
		}
		bool ImGui_InputVec4(const char* title, float_t value[4])
		{
			return ImGui::InputFloat4(title, &value[0]);
		}
		bool ImGui_InputVec4(const char* title, glm::vec4* value)
		{
			return ImGui::InputFloat4(title, &value->x);
		}
		bool ImGui_SliderAngle(const char* title, float_t* value, float_t min, float_t max)
		{
			return ImGui::SliderAngle(title, value, min, max);
		}
		bool ImGui_SliderFloat(const char* title, float_t* value, float_t min, float_t max)
		{
			return ImGui::SliderFloat(title, value, min, max);
		}
		bool ImGui_SliderVec2(const char* title, float_t value[2], float_t min, float_t max)
		{
			return ImGui::SliderFloat2(title, value, min, max);
		}
		bool ImGui_SliderVec2(const char* title, glm::vec2* value, float_t min, float_t max)
		{
			return ImGui::SliderFloat2(title, &value->x, min, max);
		}
		bool ImGui_SliderVec3(const char* title, float_t value[3], float_t min, float_t max)
		{
			return ImGui::SliderFloat3(title, value, min, max);
		}
		bool ImGui_SliderVec3(const char* title, glm::vec3* value, float_t min, float_t max)
		{
			return ImGui::SliderFloat3(title, &value->x, min, max);
		}
		bool ImGui_SliderVec4(const char* title, float_t value[4], float_t min, float_t max)
		{
			return ImGui::SliderFloat4(title, value, min, max);
		}
		bool ImGui_SliderVec4(const char* title, glm::vec4* value, float_t min, float_t max)
		{
			return ImGui::SliderFloat4(title, &value->x, min, max);
		}
		bool ImGui_SliderInt(const char* title, int32_t* value, int32_t min, int32_t max)
		{
			return ImGui::SliderInt(title, value, min, max);
		}
		bool ImGui_SliderIVec2(const char* title, int32_t value[2], int32_t min, int32_t max)
		{
			return ImGui::SliderInt2(title, value, min, max);
		}
		bool ImGui_SliderIVec2(const char* title, glm::ivec2* value, int32_t min, int32_t max)
		{
			return ImGui::SliderInt2(title, &value->x, min, max);
		}
		bool ImGui_SliderIVec3(const char* title, int32_t value[3], int32_t min, int32_t max)
		{
			return ImGui::SliderInt3(title, value, min, max);
		}
		bool ImGui_SliderIVec3(const char* title, glm::ivec3* value, int32_t min, int32_t max)
		{
			return ImGui::SliderInt3(title, &value->x, min, max);
		}
		bool ImGui_SliderIVec4(const char* title, int32_t value[4], int32_t min, int32_t max)
		{
			return ImGui::SliderInt4(title, value, min, max);
		}
		bool ImGui_SliderIVec4(const char* title, glm::ivec4* value, int32_t min, int32_t max)
		{
			return ImGui::SliderInt4(title, &value->x, min, max);
		}
		bool ImGui_ColorPicker3(const char* title, float_t value[3])
		{
			return ImGui::ColorPicker3(title, value);
		}
		bool ImGui_ColorPicker3(const char* title, glm::vec3 value)
		{
			return ImGui::ColorPicker3(title, &value.x);
		}
		bool ImGui_ColorPicker4(const char* title, float_t value[4])
		{
			return ImGui::ColorPicker4(title, value);
		}
		bool ImGui_ColorPicker4(const char* title, glm::vec4 value)
		{
			return ImGui::ColorPicker4(title, &value.x);
		}
		bool ImGui_ColorEditor3(const char* title, float_t value[3])
		{
			return ImGui::ColorEdit3(title, value);
		}
		bool ImGui_ColorEditor3(const char* title, glm::vec3 value)
		{
			return ImGui::ColorEdit3(title, &value.x);
		}
		bool ImGui_ColorEditor4(const char* title, float_t value[4])
		{
			return ImGui::ColorEdit4(title, value);
		}
		bool ImGui_ColorEditor4(const char* title, glm::vec4 value)
		{
			return ImGui::ColorEdit4(title, &value.x);
		}
		void ImGui_OpenPopup(const char* title, ImGui_PopupFlags flags)
		{
			ImGui::OpenPopup(title, flags.GetFlags());
		}
		void ImGui_ClosePopup()
		{
			ImGui::CloseCurrentPopup();
		}
		void ImGui_TableNextRow()
		{
			ImGui::TableNextRow();
		}
		bool ImGui_TableNextColumn()
		{
			return ImGui::TableNextColumn();
		}
		void ImGui_NextColumn()
		{
			ImGui::NextColumn();
		}
		void ImGui_Column(int32_t count, bool border)
		{
			ImGui::Columns(count, 0, border);
		}
		void ImGui_Sameline(float_t offset, float_t spacing)
		{
			ImGui::SameLine(offset, spacing);
		}
		bool ImGui_Selectable(const char* title, bool* selected)
		{
			return ImGui::Selectable(title, selected);
		}
		void ImGui_Tree(const char* title)
		{
			ImGui::TreeNode(title);
		}
		void ImGui_Tree(const char* id, const char* title, ...)
		{
			va_list vl;
			va_start(vl, title);
			ImGui::TreeNodeV(id, title, vl);
			va_end(vl);
		}
		void ImGui_Tree()
		{

		}
		void ImGui_Disabled(const char* title, ...)
		{
			ImGui::TextDisabled(title);
		}
		void ImGui_Progress(float_t fraction, float_t xsize, float_t ysize, const char* overlay)
		{
			ImGui::ProgressBar(fraction, ImVec2(xsize, ysize), overlay);
		}
		void ImGui_Progress(float_t fraction, glm::vec2 size, const char* overlay)
		{
			ImGui::ProgressBar(fraction, ImVec2(size.x, size.y), overlay);
		}
		void ImGui_Listbox()
		{
		}
		void ImGui_ListboxHeader()
		{
		}
		void ImGui_ListboxFooter()
		{
		}

		bool ImGui_IsAnyItemActive()
		{
			return ImGui::IsAnyItemActive();
		}
		bool ImGui_IsAnyItemFocued()
		{
			return ImGui::IsAnyItemFocused();
		}
		bool ImGui_IsAnyItemHoverd()
		{
			return ImGui::IsAnyItemHovered();
		}
		bool ImGui_IsAnyMouseDown()
		{
			return ImGui::IsAnyMouseDown();
		}
		bool ImGui_IsWindowFocued()
		{
			return ImGui::IsWindowFocused();
		}
		bool ImGui_IsItemActivated()
		{
			return ImGui::IsItemActivated();
		}
		bool ImGui_IsItemDeactivated()
		{
			return ImGui::IsItemDeactivated();
		}
		bool ImGui_IsItemActive()
		{
			return ImGui::IsItemActive();
		}
		bool ImGui_IsItemClicked()
		{
			return ImGui::IsItemClicked();
		}
		bool ImGui_IsItemFocued()
		{
			return ImGui::IsItemFocused();
		}
		bool ImGui_IsItemHovered()
		{
			return ImGui::IsItemHovered();
		}
		bool ImGui_IsItemVisible()
		{
			return ImGui::IsItemVisible();
		}
		bool ImGui_IsItemEdited()
		{
			return ImGui::IsItemEdited();
		}
		bool ImGui_IsMouseDragging(MouseButton button, float_t threshold)
		{
			return ImGui::IsMouseDragging((int32_t)button, threshold);
		}
		bool ImGui_IsMouseDown(MouseButton button)
		{
			return ImGui::IsMouseDown((int32_t)button);
		}
		bool ImGui_IsMouseUp(MouseButton button)
		{
			return ImGui::IsMouseReleased((int32_t)button);
		}
		bool ImGui_IsMouseDoubleClicked(MouseButton button)
		{
			return ImGui::IsMouseDoubleClicked((int32_t)button);
		}
		bool ImGui_IsMouseHoverdRect(glm::vec2 min, glm::vec2 max, bool clip)
		{
			return ImGui::IsMouseHoveringRect(ImVec2(min.x, min.y), ImVec2(max.x, max.y), clip);
		}
		bool ImGui_IsMouseHoverdItem(bool clip)
		{
			glm::vec2 min = ImGui_GetItemMin();
			glm::vec2 max = ImGui_GetItemMax();
			return ImGui_IsMouseHoverdRect(min, max, clip);
		}

		void ImGui_PieMenu()
		{
		}
		void ImGui_TextureField(Texture* target)
		{
			std::string s = "";
			ImGui_Text(target->Name());
			glm::vec2 wsize = ImGui_GetWindowSize();
			ImGui_Sameline(wsize.x / 2.f, 2);
			if (target == nullptr) {
				ImGui_Disabled("NULL");
			}
			else {
				glm::ivec2 size = target->Size();
				s.append(std::to_string(size.x));
				s.append("x");
				s.append(std::to_string(size.y));
				ImGui_Disabled(s.c_str());
			}
		}
		void ImGui_TextureImageField(Texture* target, int32_t size, ImGui_EventPack<Texture> events)
		{
			ImGui_ImageButton((void*)target->ID(), glm::vec2(size, size));
			if (events.Tooltop != nullptr) {
				if (ImGui_IsItemHovered()) {
					ImGui_BeginTooltip();
					events.Tooltop(target);
					ImGui_EndTooltip();
				}
			}
			return;
			if (events.Hovered != nullptr) {
				if (ImGui_IsItemHovered()) {
					events.Hovered(target);
				}
			}
			if (events.OnClick != nullptr) {
				if (ImGui_IsItemClicked()) {
					events.OnClick(target);
				}
			}
		}
		void ImGui_TextureVerticalImageField(Texture* target, int32_t size, ImGui_EventPack<Texture> events)
		{
			// Override tooltip.
			if (events.Tooltop == nullptr) {
				events.Tooltop = [](Texture* tex) -> void {
					glm::ivec2 tsize = tex->Size();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted(tex->Name());
					ImGui::Text("%ix%i", tsize.x, tsize.y);
					ImGui::PopTextWrapPos();
				};
			}
			ImGui_TextureImageField(target, size, events);
			ImGui_Sameline(size + 20, 3);
			ImGui_Text(target->Name());
		}
		void ImGui_TextureGridImageField(const char* title, std::vector<Texture*> target, int32_t size, int32_t height, int32_t column, ImGui_EventPack<Texture> events)
		{
			glm::ivec2 windowSize = ImGui_GetWindowSize();
			int32_t columnCount = -1;
			if (column == 0) {
				columnCount = std::max(windowSize.x / size, 1);
			}
			else {
				columnCount = std::max(std::min(column, windowSize.x / size), 1);
			}
			// Override tooltip.
			if (events.Tooltop == nullptr) {
				events.Tooltop = [](Texture* tex) -> void {
					glm::ivec2 tsize = tex->Size();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted(tex->Name());
					ImGui::Text("%ix%i", tsize.x, tsize.y);
					ImGui::PopTextWrapPos();
				};
			}
			ImGui_WindiwFlags wf = ImGui_WindiwFlags();
			wf.AlwaysAutoResize = true;
			ImGui_TextColor(0, 1, 1);
			ImGui_Text("Textures: %s", title);
			ImGui::PopStyleColor();
			ImGui_BeginChild("Grid Image Field", columnCount * size, height, true, wf);
			ImGui_Column(columnCount, false);
			for (int32_t i = 0; i < target.size(); i++) {
				Texture* tex = target.at(i);
				ImGui_TextureImageField(tex, size, events);
				ImGui_NextColumn();
			}
			ImGui_Column(1);
			ImGui_EndChild();
		}
		#pragma endregion

		#pragma region Gui Base Objects
		ImGui_ElementBase::ImGui_ElementBase(const char* _label)
		{
			label = label;
		}
		ImGui_ElementBase::~ImGui_ElementBase()
		{
		}
		ImGui_WindowBase::ImGui_WindowBase()
		{
		}
		ImGui_WindowBase::ImGui_WindowBase(const char* _title)
		{
			title = _title;
		}
		ImGui_WindowBase::~ImGui_WindowBase()
		{
			for (auto i = elementlist.begin(); i != elementlist.end(); i++) {
				delete *i;
			}
		}
		void ImGui_WindowBase::Render()
		{
			if (show) {
				ImGui::Begin(title.c_str(), &show);
				Content();
				ImGui::End();
			}
		}
		void ImGui_WindowBase::Content()
		{
			DefaultContent();
		}
		void ImGui_WindowBase::DefaultContent()
		{
			for (auto i = elementlist.begin(); i != elementlist.end(); i++) {
				ImGui_ElementBase* buffer = *i;
				buffer->Render();
			}
		}

		ImGui_ElementBase* ImGui_WindowBase::AddChild(ImGui_ElementBase* element)
		{
			if (element)
				elementlist.push_back(element);
			return element;
		}
		std::vector<ImGui_ElementBase*> ImGui_WindowBase::AddChildren(std::vector<ImGui_ElementBase*> elements)
		{
			for (auto i = elements.begin(); i != elements.end(); i++) {
				ImGui_ElementBase* buffer = (*i);
				if (buffer)
					elementlist.push_back(buffer);
			}
			return elements;
		}
		bool ImGui_WindowBase::RemoveChild(ImGui_ElementBase* element)
		{
			for (auto i = elementlist.begin(); i != elementlist.end(); i++) {
				ImGui_ElementBase* buffer = (*i);
				if (buffer == element) {
					elementlist.erase(i);
					return true;
				}
			}
			return false;
		}
		bool ImGui_WindowBase::RemoveChildren(std::vector<ImGui_ElementBase*> elements)
		{
			for (auto i = elements.begin(); i != elements.end(); i++) {
				ImGui_ElementBase* buffer = (*i);
				RemoveChild(buffer);
			}
			return true;
		}
		bool ImGui_WindowBase::RemoveAll()
		{
			elementlist.clear();
			return true;
		}

		void ImGui_WindowBase::Swap(int32_t index1, int32_t index2)
		{
			ImGui_ElementBase* buffer = elementlist.at(index1);
			elementlist[index1] = elementlist[index2];
			elementlist[index2] = buffer;
		}
		ImGui_ElementBase* ImGui_WindowBase::GetChild(int32_t index)
		{
			return elementlist[index];
		}
		std::vector<ImGui_ElementBase*> ImGui_WindowBase::GetChildren(int32_t index, int32_t count)
		{
			std::vector<ImGui_ElementBase*> result = std::vector<ImGui_ElementBase*>();
			for (int i = index; i < index + count; i++) {
				if (i > elementlist.size()) break;
				ImGui_ElementBase* buffer = elementlist[i];
				result.push_back(buffer);
			}
			return result;
		}
		size_t ImGui_WindowBase::Count()
		{
			return elementlist.size();
		}
		void ImGui_WindowBase::SetVisible(bool v) {
			show = v;
		}
		bool ImGui_WindowBase::Visible() {
			return show;
		}
		#pragma endregion

		#pragma region Gui Window Subclasses
		ImGui_DebugWindow::ImGui_DebugWindow() : ImGui_WindowBase("Tara Debug Info")
		{
		}
		ImGui_DebugWindow::~ImGui_DebugWindow()
		{
		}
		void ImGui_DebugWindow::Content()
		{
			DebugInfo();
		}
		void ImGui_DebugWindow::DebugInfo()
		{
			std::string t = "";
			if (ImGui_BeginTabBar("Debug Info")) {
				if (ImGui_BeginTabitems("Application", 0)) {
					t = "Tara version: 1.0";
					ImGui_Text(t.c_str());
					ImGui_EndTabitems();
				}
				if (ImGui_BeginTabitems("Input", 0)) {
					t = "time: ";
					t.append(std::to_string(EInput::Time()));
					ImGui_Text(t.c_str());

					t = "time delta: ";
					t.append(std::to_string(EInput::Delta()));
					ImGui_Text(t.c_str());

					glm::ivec2 m = EInput::GetMousePosition();
					t = "mouse: ";
					t.append(std::to_string((int)m.x));
					t.append(", " + std::to_string((int)m.y));
					ImGui_Text(t.c_str());

					m = EInput::GetMouseDelta();
					t = "mouse delta: ";
					t.append(std::to_string((int)m.x));
					t.append(", " + std::to_string((int)m.y));
					ImGui_Text(t.c_str());

					char c = EInput::GetLastChar();
					t = "last char: ";
					t += c;
					ImGui_Text(t.c_str());

					t = "log level: ";
					t.append(std::to_string(DEBUG_LEVEL));
					ImGui_Text(t.c_str());

					t = "log filename: ";
					t.append(DEBUG_FILENAME);
					ImGui_Text(t.c_str());
					ImGui_EndTabitems();
				}
				ImGui_EndTabBar();
			}
		}
		#pragma endregion

		#pragma region Gui Element Subclasses
		ImGui_TextureView::ImGui_TextureView(Texture* tex)
		{
			target = tex;
		}
		ImGui_TextureView::~ImGui_TextureView()
		{
		}
		void ImGui_TextureView::Render()
		{
			ImGui_Image((void*)target->ID(), glm::vec2(512, 512), glm::vec2(0));
		}
		#pragma endregion
};
};
#endif