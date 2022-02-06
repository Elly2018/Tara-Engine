#pragma once
#ifndef TARA_NO_IMGUI
// Include std library
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <memory>

// Include tara library
#include <config.h>
#include <glm/glm.hpp>
#include <texture.h>
#include <Framebuffer.h>
#include <ecomponent.h>
#endif

namespace Tara {
/*
	Summary:
		[ GUI Elements ]
		What this file does is organize the gui functions and variables to object oriented programming style,
		And adding additional utility methods to it make it easy to use.
*/
	typedef void (*ImGui_ChangeViewport)(int32_t x, int32_t y, int32_t w, int32_t h);

	namespace UI {
	#ifndef TARA_NO_IMGUI
		/*

			Structs, classes declaration

		*/
		template<typename T> struct	DllExport ImGui_EventPack;
		struct	DllExport ImGui_FlagBase;
		struct	DllExport ImGui_ConditionFlags;
		struct	DllExport ImGui_WindiwFlags;
		struct	DllExport ImGui_TableFlags;
		struct	DllExport ImGui_TabFlags;
		struct	DllExport ImGui_TabFlagsFitting;
		struct	DllExport ImGui_TabitemsFlags;
		struct  DllExport ImGui_PopupFlags;
		class	DllExport ImGui_UIBase;
		class	DllExport ImGui_ElementBase;
		class	DllExport ImGui_WindowBase;
		class	DllExport ImGui_DebugWindow;
		class	DllExport ImGui_MaterialField;
		class	DllExport ImGui_MaterialView;
		class	DllExport ImGui_ShaderView;
		class	DllExport ImGui_TextureField;
		class	DllExport ImGui_TextureImageField;
		class	DllExport ImGui_TextureView;
		class	DllExport ImGui_EObjectField;
		class	DllExport ImGui_EObjectHeaderView;
		class	DllExport ImGui_EObjectContentView;

		template<typename T>
		struct ImGui_EventPack {
		public:
			typedef void (*BaseEvent)(T* target);
			BaseEvent OnClick = nullptr;
			BaseEvent Tooltop = nullptr;
			BaseEvent Hovered = nullptr;
		};
		/*
			Flags is a way to tell widget to behave,
			Different widget have different flags type
		*/
		#pragma region Flag Struct
		enum class DllExport MouseButton {
			Left = 0,
			Right = 1,
			Middle = 2,
			COUNT = 5,
		};
		/*
			Summary:
				The flag struct base
		*/
		struct ImGui_FlagBase
		{
		public:
			virtual int32_t	GetFlags();
		};
		struct ImGui_ConditionFlags : public ImGui_FlagBase {
		public:
			bool Always = false;
			bool Once = false;
			bool FirstUseEver = false;
			bool Appearing = false;
			int32_t GetFlags() override;
		};
		/*
			Summary:
				UI window flags.
		*/
		struct ImGui_WindiwFlags : public ImGui_FlagBase
		{
		public:
			bool		NoTitleBar = false;
			bool		NoResize = false;
			bool		NoMove = false;
			bool		NoScrollbar = false;
			bool		NoScrollWithMouse = false;
			bool		NoCollapse = false;
			bool		AlwaysAutoResize = false;
			bool		NoBackground = false;
			bool		UnSave = false;
			bool		NoMouseInput = false;
			bool		MenuBar = false;
			bool		HorizontalScrollbar = false;
			bool		NoFocusOnAppearing = false;
			bool		NoBringToFrontOnFocus = false;
			bool		AlwaysVerticalScrollbar = false;
			bool		AlwaysHorizontalScrollbar = false;
			bool		AlwaysUseWindowPadding = false;
			bool		NoNavInputs = false;
			bool		NoNavFocus = false;
			bool		UnsaveDocumentDot = false;
			bool		NoDocking = false;

			bool		NoNav = false;
			bool		NoDecoration = false;
			bool		NoInputs = false;
			int32_t GetFlags() override;
		};
		struct ImGui_ComboFlags : public ImGui_FlagBase {
		public:
			bool PopupAlignLeft = false;
			bool HeightSmall = false;
			bool HeightHeightRegular = false;
			bool HeightHeightLarge = false;
			bool HeightHeightLargest = false;
			bool NoArrowButton = false;
			bool NoPreview = false;
			int32_t GetFlags() override;
		};
		struct ImGui_TableFlags : public ImGui_FlagBase {
		public:
			// Feature
			bool ReSizeble = false;
			bool ReOrderable = false;
			bool Hideable = false;
			bool Sortable = false;
			bool NoSave = false;
			bool ContextMenuInBody = false;
			// Decoration
			bool RowBG = false;
			bool BordersInnerH = false;
			bool BordersOuterH = false;
			bool BordersInnerV = false;
			bool BordersOuterV = false;
			bool NoBordersInBody = false;
			bool NoBordersInBodyUntilResize = false;
			// Sizing
			bool SizingFixedFit = false;
			bool SizingFixedSame = false;
			bool SizingStretchProp = false;
			bool SizingStretchSame = false;
			// Sizing Extra
			bool NoHostExtendX = false;
			bool NoHostExtendY = false;
			bool NoKeepColumnVisible = false;
			bool PreciseWidths = false;
			// Clip
			bool NoClip = false;
			// Padding
			bool PadOuterX = false;
			bool NoPadOuterX = false;
			bool NoPadInnerX = false;
			// Scrolling
			bool ScrollX = false;
			bool ScrollY = false;
			// Sorting
			bool SortMulti = false;
			bool SortTristate = false;
			int32_t GetFlags() override;
		};
		struct ImGui_TabFlagsFitting : public ImGui_FlagBase
		{
		public:
			bool	Resizedown = false;
			bool	Scroll = false;
			int32_t GetFlags() override;
		};
		struct ImGui_TabFlags : public ImGui_FlagBase
		{
		public:
			bool		ReOrderable = false;
			bool		AutoSelectTab = false;
			bool		TabListPopupButton = false;
			bool		NoCloseMiddleMouse = false;
			bool		NoTabListScrolling = false;
			bool		NoTooltop = false;
			ImGui_TabFlagsFitting	fittingpolicy = ImGui_TabFlagsFitting();
			int32_t GetFlags() override;
		};
		struct ImGui_TabitemsFlags : public ImGui_FlagBase
		{
			bool		UnSave = false;
			bool		SetSelect = false;
			bool		NoCloseMiddleMouse = false;
			bool		NoPushID = false;
			bool		NoTooltip = false;
			bool		NoReOrder = false;
			bool		Leading = false;
			bool		Trailing = false;
			int32_t GetFlags() override;
		};
		struct ImGui_PopupFlags : public ImGui_FlagBase {
		public:
			int32_t GetFlags() override;
		};
		#pragma endregion

		/*
			Summary:
				Use for arrow button functional call
		*/
		enum class arrowdirection
		{
			None = -1,
			Left = 0,
			Right = 1,
			Up = 2,
			Down = 3,
			COUNT
		};

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

		#pragma region Gui Func
		/*
			Basic func call from imgui library or third party imgui library
		*/

		DllExport void ImGui_Initialization(const char* version, void* window);
		DllExport void ImGui_ViewportCallback(ImGui_ChangeViewport callback);
		DllExport void ImGui_NewFrame();
		DllExport void ImGui_Render(void* window);
		DllExport void ImGui_Destroy();
	
		DllExport bool ImGui_Begin(const char* title, bool* open = (bool*)0, ImGui_WindiwFlags flags = ImGui_WindiwFlags());
		DllExport bool ImGui_BeginChild(const char* title, float_t w, float_t h, bool border = false, ImGui_WindiwFlags flags = ImGui_WindiwFlags());
		DllExport bool ImGui_BeginCombo(const char* title, const char* preview = "", ImGui_ComboFlags flags = ImGui_ComboFlags());
		DllExport void ImGui_BeginDisabled(bool disabled);
		DllExport bool ImGui_BeginFrame();
		DllExport void ImGui_BeginGroup();
		DllExport bool ImGui_BeginMainmenuBar();
		DllExport bool ImGui_BeginMenu(const char* label, bool enable = true);
		DllExport bool ImGui_BeginMenubar();
		DllExport bool ImGui_BeginTabBar(const char* title, ImGui_TabFlags flags = ImGui_TabFlags());
		DllExport bool ImGui_BeginTabitems(const char* title, bool* open = (bool*)0, ImGui_TabitemsFlags flags = ImGui_TabitemsFlags());
		DllExport bool ImGui_BeginTable(const char* title, int column, ImGui_TableFlags flags = ImGui_TableFlags(), glm::vec2 outterSize = glm::vec2(0), float innerWidth = 0);
		// TODO
		DllExport bool ImGui_BeginListbox();
		DllExport void ImGui_BeginTooltip();
		DllExport bool ImGui_BeginPopup(const char* title, ImGui_WindiwFlags flags = ImGui_WindiwFlags());
		DllExport bool ImGui_BeginPopupContextItem();
		DllExport bool ImGui_BeginPopupContextVoid();
		DllExport bool ImGui_BeginPopupContextWindow();
		DllExport bool ImGui_BeginPopupModal(const char* title, bool* open = (bool*)0, ImGui_WindiwFlags flags = ImGui_WindiwFlags());
		DllExport bool ImGui_BeginDrag();
		DllExport bool ImGui_BeginDrop();
	
		DllExport void ImGui_End();
		DllExport void ImGui_EndChild();
		DllExport void ImGui_EndCombo();
		DllExport void ImGui_EndDisabled();
		DllExport void ImGui_EndFrame();
		DllExport void ImGui_EndGroup();
		DllExport void ImGui_EndMainmenuBar();
		DllExport void ImGui_EndMenu();
		DllExport void ImGui_EndMenubar();
		DllExport void ImGui_EndTabBar();
		DllExport void ImGui_EndTabitems();
		DllExport void ImGui_EndTable();
		DllExport void ImGui_EndListbox();
		DllExport void ImGui_EndTooltip();
		DllExport void ImGui_EndPopup();
		DllExport void ImGui_EndDrag();
		DllExport void ImGui_EndDrop();

		DllExport void ImGui_SetNextWindowSize(float_t x, float_t y, ImGui_ConditionFlags cond = ImGui_ConditionFlags());
		DllExport void ImGui_SetNextWindowSize(glm::vec2 size, ImGui_ConditionFlags cond = ImGui_ConditionFlags());
		DllExport void ImGui_SetNextWindowPos(glm::vec2 pos, ImGui_ConditionFlags cond = ImGui_ConditionFlags(), glm::vec2 pivot = glm::vec2(0));
		DllExport void ImGui_SetNextWindowPos(float_t x, float_t y, ImGui_ConditionFlags cond = ImGui_ConditionFlags(), float_t p_x = 0, float_t p_y = 0);
		DllExport void ImGui_SetCursor(float_t x, float_t y);
		DllExport void ImGui_SetCursor(glm::vec2 pos);
		DllExport void ImGui_SetClipboard(const char* text);
		DllExport void ImGui_SetItemOpen(bool open, ImGui_ConditionFlags cond = ImGui_ConditionFlags());
		DllExport void ImGui_SetItemWidth(float_t width);
		DllExport void ImGui_SetColumnOffset(int32_t index, float_t offset);
		DllExport void ImGui_SetColumnWidth(int32_t index, float_t width);
		DllExport void ImGui_SetScrollHereX(float_t v);
		DllExport void ImGui_SetScrollHereY(float_t v);
		DllExport void ImGui_SetTreeNodeOpen(bool open, ImGui_ConditionFlags cond = ImGui_ConditionFlags());

		DllExport glm::vec2 ImGui_GetWindowSize();
		DllExport glm::vec2 ImGui_GetWindowPos();
		DllExport glm::vec2 ImGui_GetItemSize();
		DllExport glm::vec2 ImGui_GetItemMin();
		DllExport glm::vec2 ImGui_GetItemMax();
		DllExport const char* ImGui_GetVersion();
		DllExport glm::vec2 ImGui_GetCursor();
		DllExport const char* ImGui_GetClipboard();
		DllExport glm::vec2 ImGui_GetDragDelta(MouseButton button = MouseButton::Left, float_t lock_threshold = -1);
		DllExport float_t ImGui_GetColumnOffset(int32_t index = -1);
		DllExport float_t ImGui_GetColumnWidth(int32_t index = -1);
		DllExport int32_t ImGui_GetColumnsCount();
		DllExport float_t ImGui_GetScrollX();
		DllExport float_t ImGui_GetScrollY();
		DllExport float_t ImGui_GetScrollMaxX();
		DllExport float_t ImGui_GetScrollMaxY();
	
		DllExport uint32_t ImGui_DockspaceOverviewport();
		DllExport uint32_t ImGui_GetDockID();
		DllExport void ImGui_SetNextDockID(uint32_t id, ImGui_ConditionFlags cond = ImGui_ConditionFlags());
	
		DllExport void ImGui_RenderImage(void* rendertexture);
		DllExport bool ImGui_MenuItem(const char* label, const char* shortcut, bool* select, bool enable = false);
		DllExport bool ImGui_MenuItem(const char* label, const char* shortcut = 0, bool enable = false);
		DllExport bool ImGui_TextField(const char* text, char* buf, size_t buf_size);
		DllExport bool ImGui_TextFieldWithHint(const char* text, const char* hint, char* buf, size_t buf_size);
		DllExport bool ImGui_TextFieldMutiline(const char* text, char* buf, size_t buf_size, glm::vec2 size);
		DllExport void ImGui_Text(const char* text, ...);
		DllExport void ImGui_LabelText(const char* title, const char* text, ...);
		DllExport void ImGui_TextUnformatted(const char* text, const char* end = 0);
		DllExport void ImGui_Bullet();
		DllExport void ImGui_BulletText(const char* text, ...);
		DllExport void ImGui_Image(void* image, float_t w, float_t h, float_t uv_x = 0, float_t uv_y = 0, float_t uv2_x = 1, float_t uv2_y = 1);
		DllExport void ImGui_Image(void* image, glm::vec2 size = glm::vec2(100), glm::vec2 uv = glm::vec2(0), glm::vec2 uv2 = glm::vec2(1));
		DllExport void ImGui_Image(CCamera* image, float_t w, float_t h, float_t uv_x = 0, float_t uv_y = 0, float_t uv2_x = 1, float_t uv2_y = 1);
		DllExport void ImGui_Image(CCamera* image, glm::vec2 size = glm::vec2(100), glm::vec2 uv = glm::vec2(0), glm::vec2 uv2 = glm::vec2(1));
		DllExport void ImGui_Image(Texture* image, float_t w, float_t h, float_t uv_x = 0, float_t uv_y = 0, float_t uv2_x = 1, float_t uv2_y = 1);
		DllExport void ImGui_Image(Texture* image, glm::vec2 size = glm::vec2(100), glm::vec2 uv = glm::vec2(0), glm::vec2 uv2 = glm::vec2(1));
		DllExport void ImGui_Image(FrameBuffer* image, float_t w, float_t h, float_t uv_x = 0, float_t uv_y = 0, float_t uv2_x = 1, float_t uv2_y = 1);
		DllExport void ImGui_Image(FrameBuffer* image, glm::vec2 size = glm::vec2(100), glm::vec2 uv = glm::vec2(0), glm::vec2 uv2 = glm::vec2(1));
		DllExport bool ImGui_ImageButton(void* image, glm::vec2 size = glm::vec2(100), glm::vec2 uv = glm::vec2(0), glm::vec2 uv2 = glm::vec2(1));
		DllExport bool ImGui_ImageButton(void* image, float_t w = 100, float_t h = 100, float_t uv_x = 0, float_t uv_y = 0, float_t uv2_x = 1, float_t uv2_y = 1);
		DllExport bool ImGui_Checkbox(const char* title, bool* v);
		DllExport bool ImGui_CheckboxFlags(const char* title, int32_t* flags, int32_t v_flag);
		DllExport bool ImGui_Button(const char* title);
		DllExport bool ImGui_ButtonArrow(const char* title, arrowdirection dir);
		DllExport bool ImGui_ButtonSmall(const char* title);
		DllExport bool ImGui_ButtonRadio(const char* title, bool active);
		DllExport bool ImGui_ButtonRadio(const char* title, int32_t* current, int32_t button_id);
		DllExport void ImGui_Dummy(glm::vec2 size);
		DllExport void ImGui_Dummy(float_t w, float_t h);
		DllExport void ImGui_Space();
		DllExport bool ImGui_Combo(const char* title, int32_t* current, const char* const items, size_t size);
		DllExport void ImGui_Plot();
		DllExport void ImGui_Table();
		DllExport bool ImGui_CollapsingHeader(const char* title, bool* visible = (bool*)0);
		DllExport void ImGui_Indent(int32_t w = 10);
		DllExport void ImGui_UnIndent(int32_t w = 10);
		DllExport void ImGui_Separator();
		DllExport bool ImGui_InputFloat(const char* title, float_t* value);
		DllExport bool ImGui_InputVec2(const char* title, float_t value[2]);
		DllExport bool ImGui_InputVec2(const char* title, glm::vec2* value);
		DllExport bool ImGui_InputVec3(const char* title, float_t value[3]);
		DllExport bool ImGui_InputVec3(const char* title, glm::vec3* value);
		DllExport bool ImGui_InputVec4(const char* title, float_t value[4]);
		DllExport bool ImGui_InputVec4(const char* title, glm::vec4* value);
		DllExport bool ImGui_SliderAngle(const char* title, float_t* value, float_t min, float_t max);
		DllExport bool ImGui_SliderFloat(const char* title, float_t* value, float_t min, float_t max);
		DllExport bool ImGui_SliderVec2(const char* title, float_t value[2], float_t min, float_t max);
		DllExport bool ImGui_SliderVec2(const char* title, glm::vec2* value, float_t min, float_t max);
		DllExport bool ImGui_SliderVec3(const char* title, float_t value[3], float_t min, float_t max);
		DllExport bool ImGui_SliderVec3(const char* title, glm::vec3* value, float_t min, float_t max);
		DllExport bool ImGui_SliderVec4(const char* title, float_t value[4], float_t min, float_t max);
		DllExport bool ImGui_SliderVec4(const char* title, glm::vec4* value, float_t min, float_t max);
		DllExport bool ImGui_SliderInt(const char* title, int32_t* value, int32_t min, int32_t max);
		DllExport bool ImGui_SliderIVec2(const char* title, int32_t value[2], int32_t min, int32_t max);
		DllExport bool ImGui_SliderIVec2(const char* title, glm::ivec2* value, int32_t min, int32_t max);
		DllExport bool ImGui_SliderIVec3(const char* title, int32_t value[3], int32_t min, int32_t max);
		DllExport bool ImGui_SliderIVec3(const char* title, glm::ivec3* value, int32_t min, int32_t max);
		DllExport bool ImGui_SliderIVec4(const char* title, int32_t value[4], int32_t min, int32_t max);
		DllExport bool ImGui_SliderIVec4(const char* title, glm::ivec4* value, int32_t min, int32_t max);
		DllExport bool ImGui_ColorPicker3(const char* title, float_t value[3]);
		DllExport bool ImGui_ColorPicker3(const char* title, glm::vec3 value);
		DllExport bool ImGui_ColorPicker4(const char* title, float_t value[4]);
		DllExport bool ImGui_ColorPicker4(const char* title, glm::vec4 value);
		DllExport bool ImGui_ColorEditor3(const char* title, float_t value[3]);
		DllExport bool ImGui_ColorEditor3(const char* title, glm::vec3 value);
		DllExport bool ImGui_ColorEditor4(const char* title, float_t value[4]);
		DllExport bool ImGui_ColorEditor4(const char* title, glm::vec4 value);
		DllExport void ImGui_OpenPopup(const char* title, ImGui_PopupFlags flags = ImGui_PopupFlags());
		DllExport void ImGui_ClosePopup();
		DllExport void ImGui_TableNextRow();
		DllExport bool ImGui_TableNextColumn();
		DllExport void ImGui_NextColumn();
		DllExport void ImGui_Column(int32_t count, bool border = true);
		DllExport void ImGui_Sameline(float_t offset, float_t spacing);
		DllExport bool ImGui_Selectable(const char* title, bool* selected);
		DllExport void ImGui_Tree(const char* title);
		DllExport void ImGui_Tree(const char* id, const char* title, ...);
		DllExport void ImGui_Disabled(const char* title, ...);
		DllExport void ImGui_Progress(float_t fraction, float_t xsize, float_t ysize, const char* overlay);
		DllExport void ImGui_Progress(float_t fraction, glm::vec2 size, const char* overlay);
		// TODO
		DllExport void ImGui_Listbox();
		DllExport void ImGui_ListboxHeader();
		DllExport void ImGui_ListboxFooter();

		DllExport bool ImGui_IsAnyItemActive();
		DllExport bool ImGui_IsAnyItemFocued();
		DllExport bool ImGui_IsAnyItemHoverd();
		DllExport bool ImGui_IsAnyMouseDown();
		DllExport bool ImGui_IsWindowFocued();
		DllExport bool ImGui_IsItemActivated();
		DllExport bool ImGui_IsItemDeactivated();
		DllExport bool ImGui_IsItemActive();
		DllExport bool ImGui_IsItemClicked();
		DllExport bool ImGui_IsItemFocued();
		DllExport bool ImGui_IsItemHovered();
		DllExport bool ImGui_IsItemVisible();
		DllExport bool ImGui_IsItemEdited();
		DllExport bool ImGui_IsMouseDragging(MouseButton button = MouseButton::Left, float_t threshold = -1);
		DllExport bool ImGui_IsMouseDown(MouseButton button = MouseButton::Left);
		DllExport bool ImGui_IsMouseUp(MouseButton button = MouseButton::Left);
		DllExport bool ImGui_IsMouseDoubleClicked(MouseButton button = MouseButton::Left);
		DllExport bool ImGui_IsMouseHoverdRect(glm::vec2 min, glm::vec2 max, bool clip = true);
		DllExport bool ImGui_IsMouseHoverdItem(bool clip = true);

		/*
			Additional func to increase gui utility of tara engine
		*/
		DllExport void ImGui_PieMenu();
		DllExport void ImGui_TextureField(Texture* target);
		DllExport void ImGui_TextureImageField(Texture* target, int32_t size = 100, ImGui_EventPack<Texture> events = ImGui_EventPack<Texture>());
		DllExport void ImGui_TextureVerticalImageField(Texture* target, int32_t size = 100, ImGui_EventPack<Texture> events = ImGui_EventPack<Texture>());
		DllExport void ImGui_TextureGridImageField(const char* title, std::vector<Texture*> target, int32_t size = 100, int32_t height = 0, int32_t column = 0, ImGui_EventPack<Texture> events = ImGui_EventPack<Texture>());
	#pragma endregion

		/*
			Gui classes are just organize the gui functional call to object oriented style,
			Where you can adding element to the parent window and remove it etc...
		*/
		#pragma region Gui Objects
		/*
			Summary:
				The gui object base class
		*/
		class ImGui_UIBase {
		public:
			virtual void Render() {}
		};

		/*
			Summary:
				The gui element base class
		*/
		class ImGui_ElementBase : public ImGui_UIBase {
		public:
			ImGui_ElementBase(const char* _label = "Empty");
			~ImGui_ElementBase();
		protected:
			std::string label;
		};

		/*
			Summary:
				The gui element base class.
		*/
		class ImGui_WindowBase : public ImGui_UIBase {
		public:
			ImGui_WindowBase();
			ImGui_WindowBase(const char* _title);
			~ImGui_WindowBase();
			virtual void Start() {}
			void Render() override;
			virtual void Content();
			void DefaultContent();
		
			ImGui_ElementBase* AddChild(ImGui_ElementBase* element);
			std::vector<ImGui_ElementBase*> AddChildren(std::vector<ImGui_ElementBase*> elements);
			bool RemoveChild(ImGui_ElementBase* element);
			bool RemoveChildren(std::vector<ImGui_ElementBase*> elements);
			bool RemoveAll();
		
			void Swap(int32_t index1, int32_t index2);
			ImGui_ElementBase* GetChild(int32_t index);
			std::vector<ImGui_ElementBase*> GetChildren(int32_t index, int32_t count);
			size_t Count();
			void SetVisible(bool v);
			bool Visible();
		
			template<typename T> T* Getchild()
			{
				static_assert(std::is_base_of<ImGui_ElementBase, T>::value, L"T must inherit from uielementbase");
				for (auto i = elementlist.begin(); i != elementlist.end(); i++) {
					if (dynamic_cast<T>(*i) != nullptr) {
						return *i;
					}
				}
				return nullptr;
			}
			template<typename T> std::vector<T*> GetChildren()
			{
				static_assert(std::is_base_of<ImGui_ElementBase, T>::value, L"T must inherit from uielementbase");
				std::vector<T*> result = std::vector<T*>();
				for (auto i = elementlist.begin(); i != elementlist.end(); i++) {
					if (dynamic_cast<T>(*i) != nullptr) {
						result.push_back(*i);
					}
				}
				return result;
			}

		protected:
			bool show = true;
			std::string title = "Default Window";

		private:
			std::vector<ImGui_ElementBase*> elementlist = std::vector<ImGui_ElementBase*>();
		};

		/*
			Summary:
				A simple window show all the application states.
		*/
		class ImGui_DebugWindow : public ImGui_WindowBase {
		public:
			ImGui_DebugWindow();
			~ImGui_DebugWindow();
			void Content() override;

		protected:
			void DebugInfo();
		};

		class ImGui_MaterialField : public ImGui_ElementBase {

		};

		class ImGui_MaterialView : public ImGui_ElementBase {

		};

		class ImGui_ShaderView : public ImGui_ElementBase {

		};

		/*
			Summary:
				Render a texture viewer that can use apply different effect on it.
				RGBA filter, information at bottom, brightness.
		*/
		class ImGui_TextureView : public ImGui_ElementBase {
		public:
			ImGui_TextureView(Texture* tex);
			~ImGui_TextureView();
			void Render() override;
		private:
			Texture* target;
		};

		/*
			Summary:
				Render a object field without the viewing object info.
				Only show the object icon and name.
		*/
		class ImGui_EObjectField : public ImGui_ElementBase {

		};

		class ImGui_EObjectHeaderView : public ImGui_ElementBase {

		};

		class ImGui_EObjectContentView : public ImGui_ElementBase {

		};

		#pragma endregion
	};
	#endif // TARA_NO_IMGUI
};