#include "gui/gui_lowlevel.h"
#ifndef TARA_NO_IMGUI
#include <gui/gui_style.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <Windows.h>
#include <Shellapi.h>
#include <cstdarg>
#include <sstream>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <ewindow.h>
#include <imgui_markdown.h>
// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
#endif

namespace Tara {
#ifndef TARA_NO_IMGUI
	ImGui_ChangeViewport m_ImGui_ChangeViewport;

	bool markdownInit = false;
	ImGui::MarkdownConfig mdConfig = ImGui::MarkdownConfig();
	ImFont* H1 = NULL;
	ImFont* H2 = NULL;
	ImFont* H3 = NULL;

	void LinkCallback(ImGui::MarkdownLinkCallbackData data_) {
		std::string url(data_.link, data_.linkLength);
		if (!data_.isImage)
		{
			ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
		}
	}
	ImGui::MarkdownImageData ImageCallback(ImGui::MarkdownLinkCallbackData data_)
	{
		// In your application you would load an image based on data_ input. Here we just use the imgui font texture.
		ImTextureID image = ImGui::GetIO().Fonts->TexID;
		// > C++14 can use ImGui::MarkdownImageData imageData{ true, false, image, ImVec2( 40.0f, 20.0f ) };
		ImGui::MarkdownImageData imageData;
		imageData.isValid = true;
		imageData.useLinkCallback = false;
		imageData.user_texture_id = image;
		imageData.size = ImVec2(40.0f, 20.0f);

		// For image resize when available size.x > image width, add
		ImVec2 const contentSize = ImGui::GetContentRegionAvail();
		if (imageData.size.x > contentSize.x)
		{
			float const ratio = imageData.size.y / imageData.size.x;
			imageData.size.x = contentSize.x;
			imageData.size.y = contentSize.x * ratio;
		}

		return imageData;
	}
	void ExampleMarkdownFormatCallback(const ImGui::MarkdownFormatInfo& markdownFormatInfo_, bool start_)
	{
		// Call the default first so any settings can be overwritten by our implementation.
		// Alternatively could be called or not called in a switch statement on a case by case basis.
		// See defaultMarkdownFormatCallback definition for furhter examples of how to use it.
		ImGui::defaultMarkdownFormatCallback(markdownFormatInfo_, start_);

		switch (markdownFormatInfo_.type)
		{
			// example: change the colour of heading level 2
		case ImGui::MarkdownFormatType::HEADING:
		{
			if (markdownFormatInfo_.level == 2)
			{
				if (start_)
				{
					ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
				}
				else
				{
					ImGui::PopStyleColor();
				}
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	void MarkdownInitialization()
	{
		mdConfig.linkCallback = LinkCallback;
		mdConfig.tooltipCallback = NULL;
		mdConfig.imageCallback = ImageCallback;
		//mdConfig.linkIcon = ICON_FA_LINK;
		mdConfig.headingFormats[0] = { H1, true };
		mdConfig.headingFormats[1] = { H2, true };
		mdConfig.headingFormats[2] = { H3, false };
		mdConfig.userData = NULL;
		mdConfig.formatCallback = ExampleMarkdownFormatCallback;

		markdownInit = true;
	}

	namespace UI {
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
			//io.Fonts->AddFontDefault();
			io.Fonts->AddFontFromFileTTF(".\\Resources\\fonts\\OpenSans-Medium.ttf", 16.0f);
			H1 = io.Fonts->AddFontFromFileTTF(".\\Resources\\fonts\\OpenSans-Bold.ttf", 36.0f);
			H2 = io.Fonts->AddFontFromFileTTF(".\\Resources\\fonts\\OpenSans-Bold.ttf", 32.0f);
			H3 = io.Fonts->AddFontFromFileTTF(".\\Resources\\fonts\\OpenSans-SemiBold.ttf", 26.0f);
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
		bool ImGui_ButtonArrow(const char* title, ArrowDirection dir)
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
		bool ImGui_DragFloat(const char* title, float_t* value, float_t speed, float_t min, float_t max)
		{
			return ImGui::DragFloat(title, value, speed, min, max);
		}
		bool ImGui_DragVec2(const char* title, float_t value[2], float_t speed, float_t min, float_t max)
		{
			return ImGui::DragFloat2(title, &value[0], speed, min, max);
		}
		bool ImGui_DragVec2(const char* title, glm::vec2* value, float_t speed, float_t min, float_t max)
		{
			return ImGui::DragFloat2(title, &value->x, speed, min, max);
		}
		bool ImGui_DragVec3(const char* title, float_t value[3], float_t speed, float_t min, float_t max)
		{
			return ImGui::DragFloat3(title, &value[0], speed, min, max);
		}
		bool ImGui_DragVec3(const char* title, glm::vec3* value, float_t speed, float_t min, float_t max)
		{
			return ImGui::DragFloat3(title, &value->x, speed, min, max);
		}
		bool ImGui_DragVec4(const char* title, float_t value[4], float_t speed, float_t min, float_t max)
		{
			return ImGui::DragFloat4(title, &value[0], speed, min, max);
		}
		bool ImGui_DragVec4(const char* title, glm::vec4* value, float_t speed, float_t min, float_t max)
		{
			return ImGui::DragFloat4(title, &value->x, speed, min, max);
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
		bool ImGui_Selectable(const char* title, bool selected)
		{
			return ImGui::Selectable(title, selected);
		}
		bool ImGui_Tree(const char* title)
		{
			return ImGui::TreeNode(title);
		}
		bool ImGui_Tree(const char* id, const char* title, ...)
		{
			va_list vl;
			va_start(vl, title);
			bool v = ImGui::TreeNodeV(id, title, vl);
			va_end(vl);
			return v;
		}
		bool ImGui_Tree(const void* id, const char* title, ...)
		{
			va_list vl;
			va_start(vl, title);
			bool v = ImGui::TreeNodeV(id, title, vl);
			va_end(vl);
			return v;
		}
		void ImGui_TreePop() {
			ImGui::TreePop();
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
		void ImGui_Markdown(std::string& text) {
			if (!markdownInit) MarkdownInitialization();
			ImGui::Markdown(text.c_str(), text.length(), mdConfig);
		}
		void ImGui_MeshField(const char* title, Mesh* target)
		{
			std::string s = "";
			glm::vec2 wsize = ImGui_GetWindowSize();
			ImGui_Column(2, false);
			ImGui_Text(title);
			ImGui_SetColumnWidth(0, std::fmax(wsize.x / 7.0f, 80));
			ImGui_NextColumn();
			if (target == nullptr) {
				ImGui_Disabled("NULL");
			}
			else {
				s.append(target->Name());
				ImGui_Disabled(s.c_str());
			}
			ImGui_NextColumn();
		}
		void ImGui_TextureField(const char* title, Texture* target)
		{
			std::string s = "";
			glm::vec2 wsize = ImGui_GetWindowSize();
			ImGui_Column(2, false);
			ImGui_Text(title);
			ImGui_SetColumnWidth(0, std::fmax(wsize.x / 7.0f, 80));
			ImGui_NextColumn();
			if (target == nullptr) {
				ImGui_Disabled("NULL");
			}
			else {
				s.append(target->Name());
				ImGui_Disabled(s.c_str());
			}
			ImGui_NextColumn();
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
				columnCount = std::fmax(windowSize.x / size, 1);
			}
			else {
				columnCount = std::fmax(std::fmin(column, windowSize.x / size), 1);
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
			ImGui_BeginChild("Grid Image Field Frame", 0, 0, false, wf);
			ImGui_BeginChild("Grid Image Field", columnCount * size, height, false, wf);
			ImGui_Column(columnCount, false);
			for (int32_t i = 0; i < target.size(); i++) {
				Texture* tex = target.at(i);
				ImGui_TextureImageField(tex, size, events);
				ImGui_NextColumn();
			}
			ImGui_Column(1);
			ImGui_EndChild();
			ImGui_EndChild();
		}
		void ImGui_MaterialField(const char* title, Material* target)
		{
			std::string s = "";
			glm::vec2 wsize = ImGui_GetWindowSize();
			ImGui_Column(2, false);
			ImGui_Text(title);
			ImGui_SetColumnWidth(0, std::fmax(wsize.x / 7.0f, 80));
			ImGui_NextColumn();
			if (target == nullptr) {
				ImGui_Disabled("NULL");
			}
			else {
				s.append(target->Name());
				ImGui_Disabled(s.c_str());
				if (UI::ImGui_BeginDrop()) {
					UI::ImGui_EndDrop();
				}
			}
			ImGui_NextColumn();
		}
		void ImGui_MaterialImageField(Material* target, CommomMesh preview)
		{
		}
		void ImGui_MaterialVerticalImageField(Material* target, CommomMesh preview)
		{
		}
		void ImGui_MaterialGridImageField(Material* target, CommomMesh preview)
		{
		}
		void ImGui_ShaderField(Shader* target)
		{
		}
		EObject* ImGui_EObjectHierarchy(EObject* target, EObject* _focus) {
			size_t c = target->Count();
			EObject* focus = _focus;
			if (target == focus) {
				ImGui_TextColor(glm::vec3(1, 1, 0));
			}
			else {
				ImGui_TextColor(glm::vec3(1, 1, 1));
			}

			if (ImGui_Tree((void*)target, target->Name())) {
				if (ImGui_IsItemFocued()) {
					focus = target;
				}
				ImGui_TableNextColumn();
				if (c > 0) {
					ImGui_Indent();
					for (int32_t i = 0; i < c; i++) {
						focus = ImGui_EObjectHierarchy(target->GetChild(i), focus);
					}
					ImGui_UnIndent();
				}
				ImGui_TreePop();
			}
			ImGui_PopColor();
			return focus;
		}
		void ImGui_EObjectField(const char* title, EObject* target)
		{
			std::string s = "";
			glm::vec2 wsize = ImGui_GetWindowSize();
			ImGui_Column(2, false);
			ImGui_Text(title);
			ImGui_SetColumnWidth(0, std::fmax(wsize.x / 7.0f, 80));
			ImGui_NextColumn();
			if (target == nullptr) {
				ImGui_Disabled("NULL");
			}
			else {
				s.append(target->Name());
				ImGui_Disabled(s.c_str());
			}
			ImGui_NextColumn();
		}
		void ImGui_EObjectImageField(EObject* target)
		{
		}
		void ImGui_EObjectVerticalImageField(EObject* target)
		{
		}
		void ImGui_EObjectGridImageField(EObject* target)
		{
		}
		void ImGui_EComponentField(EObject* target)
		{
			
		}
	}
#endif
}