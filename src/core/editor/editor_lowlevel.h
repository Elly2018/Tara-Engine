#pragma once
// Import Third party library
#include <glm/glm.hpp>

// Import Tara engine library
#include "editor_config.h"
#include "../engine/core/data/tree.h"
#include "editor_base.h"
#include "editor_flags.h"

namespace Tara {
	class TARA_API CameraComponent;
	class TARA_API SceneObject;
	class TARA_API Texture2D;
	class TARA_API Mesh;
	class TARA_API Shader;
	class TARA_API Material;
	class TARA_API FrameBuffer;

	namespace UI {
		// ! Basic func call from imgui library or third party imgui library
		/*
			@brief Imgui lowlevel element initialization.
		*/
		TARA_EDITOR_API void ImGui_InitFont();

		TARA_EDITOR_API bool ImGui_Begin(const char* title, bool* open = (bool*)0, ImGui_WindiwFlags flags = ImGui_WindiwFlags());
		TARA_EDITOR_API bool ImGui_BeginChild(const char* title, float_t w, float_t h, bool border = false, ImGui_WindiwFlags flags = ImGui_WindiwFlags());
		TARA_EDITOR_API bool ImGui_BeginCombo(const char* title, const char* preview = "", ImGui_ComboFlags flags = ImGui_ComboFlags());
		TARA_EDITOR_API void ImGui_BeginDisabled(bool disabled);
		TARA_EDITOR_API bool ImGui_BeginFrame();
		TARA_EDITOR_API void ImGui_BeginGroup();
		TARA_EDITOR_API bool ImGui_BeginMainmenuBar();
		TARA_EDITOR_API bool ImGui_BeginMenu(const char* label, bool enable = true);
		TARA_EDITOR_API bool ImGui_BeginMenubar();
		TARA_EDITOR_API bool ImGui_BeginTabBar(const char* title, ImGui_TabFlags flags = ImGui_TabFlags());
		TARA_EDITOR_API bool ImGui_BeginTabitems(const char* title, bool* open = (bool*)0, ImGui_TabitemsFlags flags = ImGui_TabitemsFlags());
		TARA_EDITOR_API bool ImGui_BeginTable(const char* title, int column, ImGui_TableFlags flags = ImGui_TableFlags(), glm::vec2 outterSize = glm::vec2(0), float innerWidth = 0);
		// TODO
		TARA_EDITOR_API bool ImGui_BeginListbox();
		TARA_EDITOR_API void ImGui_BeginTooltip();
		TARA_EDITOR_API bool ImGui_BeginPopup(const char* title, ImGui_WindiwFlags flags = ImGui_WindiwFlags());
		TARA_EDITOR_API bool ImGui_BeginPopupContextItem();
		TARA_EDITOR_API bool ImGui_BeginPopupContextVoid();
		TARA_EDITOR_API bool ImGui_BeginPopupContextWindow(const char* title, ImGui_PopupFlags flags = ImGui_PopupFlags());
		TARA_EDITOR_API bool ImGui_BeginPopupModal(const char* title, bool* open = (bool*)0, ImGui_WindiwFlags flags = ImGui_WindiwFlags());
		TARA_EDITOR_API bool ImGui_BeginDrag();
		TARA_EDITOR_API bool ImGui_BeginDrop();

		TARA_EDITOR_API void ImGui_End();
		TARA_EDITOR_API void ImGui_EndChild();
		TARA_EDITOR_API void ImGui_EndCombo();
		TARA_EDITOR_API void ImGui_EndDisabled();
		TARA_EDITOR_API void ImGui_EndFrame();
		TARA_EDITOR_API void ImGui_EndGroup();
		TARA_EDITOR_API void ImGui_EndMainmenuBar();
		TARA_EDITOR_API void ImGui_EndMenu();
		TARA_EDITOR_API void ImGui_EndMenubar();
		TARA_EDITOR_API void ImGui_EndTabBar();
		TARA_EDITOR_API void ImGui_EndTabitems();
		TARA_EDITOR_API void ImGui_EndTable();
		TARA_EDITOR_API void ImGui_EndListbox();
		TARA_EDITOR_API void ImGui_EndTooltip();
		TARA_EDITOR_API void ImGui_EndPopup();
		TARA_EDITOR_API void ImGui_EndDrag();
		TARA_EDITOR_API void ImGui_EndDrop();
		TARA_EDITOR_API void ImGui_EndNodeEditor();
		TARA_EDITOR_API void ImGui_EndNode();

		TARA_EDITOR_API void ImGui_SetNextWindowSize(float_t x, float_t y, ImGui_ConditionFlags cond = ImGui_ConditionFlags());
		TARA_EDITOR_API void ImGui_SetNextWindowSize(glm::vec2 size, ImGui_ConditionFlags cond = ImGui_ConditionFlags());
		TARA_EDITOR_API void ImGui_SetNextWindowPos(glm::vec2 pos, glm::vec2 pivot = glm::vec2(0), ImGui_ConditionFlags cond = ImGui_ConditionFlags());
		TARA_EDITOR_API void ImGui_SetNextWindowPos(float_t x, float_t y, ImGui_ConditionFlags cond = ImGui_ConditionFlags(), float_t p_x = 0, float_t p_y = 0);
		TARA_EDITOR_API void ImGui_SetCursor(float_t x, float_t y);
		TARA_EDITOR_API void ImGui_SetCursor(glm::vec2 pos);
		TARA_EDITOR_API void ImGui_SetClipboard(const char* text);
		TARA_EDITOR_API void ImGui_SetItemDefaultFocus();
		TARA_EDITOR_API void ImGui_SetItemOpen(bool open, ImGui_ConditionFlags cond = ImGui_ConditionFlags());
		TARA_EDITOR_API void ImGui_SetItemWidth(float_t width);
		TARA_EDITOR_API void ImGui_SetColumnOffset(int32_t index, float_t offset);
		TARA_EDITOR_API void ImGui_SetColumnWidth(int32_t index, float_t width);
		TARA_EDITOR_API void ImGui_SetScrollHereX(float_t v);
		TARA_EDITOR_API void ImGui_SetScrollHereY(float_t v);
		TARA_EDITOR_API void ImGui_SetTreeNodeOpen(bool open, ImGui_ConditionFlags cond = ImGui_ConditionFlags());

		TARA_EDITOR_API glm::vec2 ImGui_GetWindowSize();
		TARA_EDITOR_API glm::vec2 ImGui_GetViewportSize();
		TARA_EDITOR_API glm::vec2 ImGui_GetWindowPos();
		TARA_EDITOR_API glm::vec2 ImGui_GetItemSize();
		TARA_EDITOR_API glm::vec2 ImGui_GetItemMin();
		TARA_EDITOR_API glm::vec2 ImGui_GetItemMax();
		TARA_EDITOR_API const char* ImGui_GetVersion();
		TARA_EDITOR_API glm::vec2 ImGui_GetCursor();
		TARA_EDITOR_API const char* ImGui_GetClipboard();
		TARA_EDITOR_API glm::vec2 ImGui_GetDragDelta(MouseButton button = MouseButton::Left, float_t lock_threshold = -1);
		TARA_EDITOR_API float_t ImGui_GetColumnOffset(int32_t index = -1);
		TARA_EDITOR_API float_t ImGui_GetColumnWidth(int32_t index = -1);
		TARA_EDITOR_API int32_t ImGui_GetColumnIndex();
		TARA_EDITOR_API int32_t ImGui_GetColumnsCount();
		TARA_EDITOR_API float_t ImGui_GetScrollX();
		TARA_EDITOR_API float_t ImGui_GetScrollY();
		TARA_EDITOR_API float_t ImGui_GetScrollMaxX();
		TARA_EDITOR_API float_t ImGui_GetScrollMaxY();

		TARA_EDITOR_API uint32_t ImGui_DockspaceOverviewport();
		TARA_EDITOR_API uint32_t ImGui_GetDockID();
		TARA_EDITOR_API void ImGui_SetNextDockID(uint32_t id, ImGui_ConditionFlags cond = ImGui_ConditionFlags());

		TARA_EDITOR_API void ImGui_RenderImage(void* rendertexture);
		TARA_EDITOR_API bool ImGui_MenuItem(const char* label, const char* shortcut, bool* select, bool enable = false);
		TARA_EDITOR_API bool ImGui_MenuItem(const char* label, const char* shortcut = 0, bool enable = false);
		TARA_EDITOR_API bool ImGui_TextField(const char* text, char* buf, size_t buf_size);
		TARA_EDITOR_API bool ImGui_TextField(const char* text, std::string* buf);
		TARA_EDITOR_API bool ImGui_TextFieldWithHint(const char* text, const char* hint, char* buf, size_t buf_size);
		TARA_EDITOR_API bool ImGui_TextFieldWithHint(const char* text, const char* hint, std::string* buf);
		TARA_EDITOR_API bool ImGui_TextFieldMutiline(const char* text, char* buf, size_t buf_size, glm::vec2 size);
		TARA_EDITOR_API bool ImGui_TextFieldMutiline(const char* text, std::string* buf, glm::vec2 size);
		TARA_EDITOR_API void ImGui_Text(const char* text, ...);
		TARA_EDITOR_API void ImGui_CenterText(const char* text, ...);
		TARA_EDITOR_API void ImGui_LabelText(const char* title, const char* text, ...);
		TARA_EDITOR_API void ImGui_TextUnformatted(const char* text, const char* end = 0);
		TARA_EDITOR_API void ImGui_Bullet();
		TARA_EDITOR_API void ImGui_BulletText(const char* text, ...);
		TARA_EDITOR_API void ImGui_Image(void* image, float_t w, float_t h, float_t uv_x = 0, float_t uv_y = 0, float_t uv2_x = 1, float_t uv2_y = 1);
		TARA_EDITOR_API void ImGui_Image(void* image, glm::vec2 size = glm::vec2(100), glm::vec2 uv = glm::vec2(0), glm::vec2 uv2 = glm::vec2(1));
		TARA_EDITOR_API void ImGui_Image(CameraComponent* image, float_t w, float_t h, float_t uv_x = 0, float_t uv_y = 0, float_t uv2_x = 1, float_t uv2_y = 1);
		TARA_EDITOR_API void ImGui_Image(CameraComponent* image, glm::vec2 size = glm::vec2(100), glm::vec2 uv = glm::vec2(0), glm::vec2 uv2 = glm::vec2(1));
		TARA_EDITOR_API void ImGui_Image(Texture2D* image, float_t w, float_t h, float_t uv_x = 0, float_t uv_y = 0, float_t uv2_x = 1, float_t uv2_y = 1);
		TARA_EDITOR_API void ImGui_Image(Texture2D* image, glm::vec2 size = glm::vec2(100), glm::vec2 uv = glm::vec2(0), glm::vec2 uv2 = glm::vec2(1));
		TARA_EDITOR_API void ImGui_Image(FrameBuffer* image, float_t w, float_t h, float_t uv_x = 0, float_t uv_y = 0, float_t uv2_x = 1, float_t uv2_y = 1);
		TARA_EDITOR_API void ImGui_Image(FrameBuffer* image, glm::vec2 size = glm::vec2(100), glm::vec2 uv = glm::vec2(0), glm::vec2 uv2 = glm::vec2(1));
		TARA_EDITOR_API bool ImGui_ImageButton(void* image, glm::vec2 size = glm::vec2(100), glm::vec2 uv = glm::vec2(0), glm::vec2 uv2 = glm::vec2(1));
		TARA_EDITOR_API bool ImGui_ImageButton(void* image, float_t w = 100, float_t h = 100, float_t uv_x = 0, float_t uv_y = 0, float_t uv2_x = 1, float_t uv2_y = 1);
		TARA_EDITOR_API bool ImGui_Checkbox(const char* title, bool* v);
		TARA_EDITOR_API bool ImGui_CheckboxFlags(const char* title, int32_t* flags, int32_t v_flag);
		TARA_EDITOR_API bool ImGui_Button(const char* title, glm::vec2 size = glm::vec2(0));
		TARA_EDITOR_API bool ImGui_ColumnButton(const char* title, float_t height = 24, float_t padding = 0);
		TARA_EDITOR_API bool ImGui_ButtonArrow(const char* title, ArrowDirection dir);
		TARA_EDITOR_API bool ImGui_ButtonSmall(const char* title);
		TARA_EDITOR_API bool ImGui_ButtonRadio(const char* title, bool active);
		TARA_EDITOR_API bool ImGui_ButtonRadio(const char* title, int32_t* current, int32_t button_id);
		TARA_EDITOR_API void ImGui_Dummy(glm::vec2 size);
		TARA_EDITOR_API void ImGui_Dummy(float_t w, float_t h);
		TARA_EDITOR_API void ImGui_Space();
		TARA_EDITOR_API bool ImGui_Combo(const char* title, int32_t* current, const char* const items, size_t size);
		TARA_EDITOR_API void ImGui_Plot();
		TARA_EDITOR_API void ImGui_Table();
		TARA_EDITOR_API bool ImGui_CollapsingHeader(std::string title, bool* visible = (bool*)0);
		TARA_EDITOR_API bool ImGui_CollapsingHeader(const char* title, bool* visible = (bool*)0);
		TARA_EDITOR_API void ImGui_Indent(int32_t w = 10);
		TARA_EDITOR_API void ImGui_UnIndent(int32_t w = 10);
		TARA_EDITOR_API void ImGui_Separator();
		TARA_EDITOR_API bool ImGui_InputFloat(const char* title, float_t* value);
		TARA_EDITOR_API bool ImGui_InputVec2(const char* title, float_t value[2]);
		TARA_EDITOR_API bool ImGui_InputVec2(const char* title, glm::vec2* value);
		TARA_EDITOR_API bool ImGui_InputVec3(const char* title, float_t value[3]);
		TARA_EDITOR_API bool ImGui_InputVec3(const char* title, glm::vec3* value);
		TARA_EDITOR_API bool ImGui_InputVec4(const char* title, float_t value[4]);
		TARA_EDITOR_API bool ImGui_InputVec4(const char* title, glm::vec4* value);
		TARA_EDITOR_API bool ImGui_DragFloat(const char* title, float_t* value, float_t speed = 1, float_t min = 0, float_t max = 0);
		TARA_EDITOR_API bool ImGui_DragVec2(const char* title, float_t value[2], float_t speed = 1, float_t min = 0, float_t max = 0);
		TARA_EDITOR_API bool ImGui_DragVec2(const char* title, glm::vec2* value, float_t speed = 1, float_t min = 0, float_t max = 0);
		TARA_EDITOR_API bool ImGui_DragVec3(const char* title, float_t value[3], float_t speed = 1, float_t min = 0, float_t max = 0);
		TARA_EDITOR_API bool ImGui_DragVec3(const char* title, glm::vec3* value, float_t speed = 1, float_t min = 0, float_t max = 0);
		TARA_EDITOR_API bool ImGui_DragVec4(const char* title, float_t value[4], float_t speed = 1, float_t min = 0, float_t max = 0);
		TARA_EDITOR_API bool ImGui_DragVec4(const char* title, glm::vec4* value, float_t speed = 1, float_t min = 0, float_t max = 0);
		TARA_EDITOR_API bool ImGui_SliderAngle(const char* title, float_t* value, float_t min, float_t max);
		TARA_EDITOR_API bool ImGui_SliderFloat(const char* title, float_t* value, float_t min, float_t max);
		TARA_EDITOR_API bool ImGui_SliderVec2(const char* title, float_t value[2], float_t min, float_t max);
		TARA_EDITOR_API bool ImGui_SliderVec2(const char* title, glm::vec2* value, float_t min, float_t max);
		TARA_EDITOR_API bool ImGui_SliderVec3(const char* title, float_t value[3], float_t min, float_t max);
		TARA_EDITOR_API bool ImGui_SliderVec3(const char* title, glm::vec3* value, float_t min, float_t max);
		TARA_EDITOR_API bool ImGui_SliderVec4(const char* title, float_t value[4], float_t min, float_t max);
		TARA_EDITOR_API bool ImGui_SliderVec4(const char* title, glm::vec4* value, float_t min, float_t max);
		TARA_EDITOR_API bool ImGui_SliderInt(const char* title, int32_t* value, int32_t min, int32_t max);
		TARA_EDITOR_API bool ImGui_SliderIVec2(const char* title, int32_t value[2], int32_t min, int32_t max);
		TARA_EDITOR_API bool ImGui_SliderIVec2(const char* title, glm::ivec2* value, int32_t min, int32_t max);
		TARA_EDITOR_API bool ImGui_SliderIVec3(const char* title, int32_t value[3], int32_t min, int32_t max);
		TARA_EDITOR_API bool ImGui_SliderIVec3(const char* title, glm::ivec3* value, int32_t min, int32_t max);
		TARA_EDITOR_API bool ImGui_SliderIVec4(const char* title, int32_t value[4], int32_t min, int32_t max);
		TARA_EDITOR_API bool ImGui_SliderIVec4(const char* title, glm::ivec4* value, int32_t min, int32_t max);
		TARA_EDITOR_API bool ImGui_ColorPicker3(const char* title, float_t value[3]);
		TARA_EDITOR_API bool ImGui_ColorPicker3(const char* title, glm::vec3* value);
		TARA_EDITOR_API bool ImGui_ColorPicker4(const char* title, float_t value[4]);
		TARA_EDITOR_API bool ImGui_ColorPicker4(const char* title, glm::vec4* value);
		TARA_EDITOR_API bool ImGui_ColorEditor3(const char* title, float_t value[3]);
		TARA_EDITOR_API bool ImGui_ColorEditor3(const char* title, glm::vec3* value);
		TARA_EDITOR_API bool ImGui_ColorEditor4(const char* title, float_t value[4]);
		TARA_EDITOR_API bool ImGui_ColorEditor4(const char* title, glm::vec4* value);
		TARA_EDITOR_API void ImGui_OpenPopup(const char* title, ImGui_PopupFlags flags = ImGui_PopupFlags());
		TARA_EDITOR_API void ImGui_ClosePopup();
		TARA_EDITOR_API void ImGui_TableNextRow();
		TARA_EDITOR_API bool ImGui_TableNextColumn();
		TARA_EDITOR_API void ImGui_NextColumn();
		TARA_EDITOR_API void ImGui_Column(int32_t count, bool border = true);
		TARA_EDITOR_API void ImGui_Sameline(float_t offset, float_t spacing);
		TARA_EDITOR_API bool ImGui_Selectable(const char* title, bool* selected, glm::vec2 size, ImGui_SelectableFlags flag = ImGui_SelectableFlags());
		TARA_EDITOR_API bool ImGui_Selectable(const char* title, bool selected, glm::vec2 size, ImGui_SelectableFlags flag = ImGui_SelectableFlags());
		TARA_EDITOR_API bool ImGui_Selectable(const char* title, bool* selected, ImGui_SelectableFlags flag = ImGui_SelectableFlags());
		TARA_EDITOR_API bool ImGui_Selectable(const char* title, bool selected, ImGui_SelectableFlags flag = ImGui_SelectableFlags());
		TARA_EDITOR_API bool ImGui_Selectable(const char* title, ImGui_SelectableFlags flag = ImGui_SelectableFlags());
		TARA_EDITOR_API bool ImGui_Tree(const char* title);
		TARA_EDITOR_API bool ImGui_Tree(const char* id, const char* title, ...);
		TARA_EDITOR_API bool ImGui_Tree(std::string id, std::string title, ...);
		TARA_EDITOR_API bool ImGui_Tree(const void* id, const char* title, ...);
		TARA_EDITOR_API bool ImGui_TreeStyle(const char* title, glm::vec4 bgcolor, glm::vec3 textcolor);
		TARA_EDITOR_API bool ImGui_TreeStyle(const char* id, const char* title, glm::vec4 bgcolor, glm::vec3 textcolor, ...);
		TARA_EDITOR_API bool ImGui_TreeStyle(std::string id, std::string title, glm::vec4 bgcolor, glm::vec3 textcolor, ...);
		TARA_EDITOR_API bool ImGui_TreeStyle(const void* id, const char* title, glm::vec4 bgcolor, glm::vec3 textcolor, ...);
		TARA_EDITOR_API void ImGui_TreePop();
		TARA_EDITOR_API void ImGui_Disabled(const char* title, ...);
		TARA_EDITOR_API void ImGui_Progress(float_t fraction, float_t xsize, float_t ysize, const char* overlay);
		TARA_EDITOR_API void ImGui_Progress(float_t fraction, glm::vec2 size, const char* overlay);
		// TODO
		TARA_EDITOR_API void ImGui_Listbox();
		TARA_EDITOR_API void ImGui_ListboxHeader();
		TARA_EDITOR_API void ImGui_ListboxFooter();

		TARA_EDITOR_API bool ImGui_IsAnyItemActive();
		TARA_EDITOR_API bool ImGui_IsAnyItemFocued();
		TARA_EDITOR_API bool ImGui_IsAnyItemHoverd();
		TARA_EDITOR_API bool ImGui_IsAnyMouseDown();
		TARA_EDITOR_API bool ImGui_IsWindowFocued();
		TARA_EDITOR_API bool ImGui_IsItemActivated();
		TARA_EDITOR_API bool ImGui_IsItemDeactivated();
		TARA_EDITOR_API bool ImGui_IsItemActive();
		TARA_EDITOR_API bool ImGui_IsItemClicked(MouseButton button = MouseButton::Left);
		TARA_EDITOR_API bool ImGui_IsItemFocued();
		TARA_EDITOR_API bool ImGui_IsItemHovered();
		TARA_EDITOR_API bool ImGui_IsItemVisible();
		TARA_EDITOR_API bool ImGui_IsItemEdited();
		TARA_EDITOR_API bool ImGui_IsMouseDragging(MouseButton button = MouseButton::Left, float_t threshold = -1);
		TARA_EDITOR_API bool ImGui_IsMouseDown(MouseButton button = MouseButton::Left);
		TARA_EDITOR_API bool ImGui_IsMouseUp(MouseButton button = MouseButton::Left);
		TARA_EDITOR_API bool ImGui_IsMouseDoubleClicked(MouseButton button = MouseButton::Left);
		TARA_EDITOR_API bool ImGui_IsMouseHoverdRect(glm::vec2 min, glm::vec2 max, bool clip = true);
		TARA_EDITOR_API bool ImGui_IsMouseHoverdItem(bool clip = true);
		TARA_EDITOR_API bool ImGui_IsModifieKeyDown(EditorModifieKey key);
		TARA_EDITOR_API bool ImGui_IsKeyDown(EditorKey key);
		TARA_EDITOR_API bool ImGui_IsPopupOpen(const char* id);

		// ! Additional func to increase gui utility of tara engine
		/*
			@brief Render custom tree node.
			@param id: Node id.
			@param title: Node title text.
			@param select: This will decide that the background color will draw or not.
			@param has children: this will decide that left side arrow is render or not.
		*/
		TARA_EDITOR_API bool ImGui_CustomTreeNode(const void* id, const char* title, bool* select, bool hasChildren);
		/*
			@brief Render custom tree node.
			@param id: Node id.
			@param title: Node title text.
			@param select: This will decide that the background color will draw or not.
			@param has children: this will decide that left side arrow is render or not.
			@param textcolor: text display color.
		*/
		TARA_EDITOR_API bool ImGui_CustomTreeNode(const void* id, const char* title, bool* select, bool hasChildren, glm::vec3 textcolor);
		/*
			@brief Render custom tree node.
			@param id: Node id.
			@param title: Node title text.
			@param select: This will decide that the background color will draw or not.
			@param has children: this will decide that left side arrow is render or not.
			@param bgcolor: background color, notice that only select is true will draw the background.
		*/
		TARA_EDITOR_API bool ImGui_CustomTreeNode(const void* id, const char* title, bool* select, bool hasChildren, glm::vec4 bgcolor);
		/*
			@brief Render custom tree node.
			@param id: Node id.
			@param title: Node title text.
			@param select: This will decide that the background color will draw or not.
			@param has children: this will decide that left side arrow is render or not.
			@param bgcolor: background color, notice that only select is true will draw the background.
			@param textcolor: text display color.
		*/
		TARA_EDITOR_API bool ImGui_CustomTreeNode(const void* id, const char* title, bool* select, bool hasChildren, glm::vec4 bgcolor, glm::vec3 textcolor);
		/*
			@brief Render custom tree node.
			@param id: Node id.
			@param title: Node title text.
			@param select: This will decide that the background color will draw or not.
			@param has children: this will decide that left side arrow is render or not.
		*/
		TARA_EDITOR_API bool ImGui_CustomTreeNode(const char* id, const char* title, bool* select, bool hasChildren);
		/*
			@brief Render custom tree node.
			@param id: Node id.
			@param title: Node title text.
			@param select: This will decide that the background color will draw or not.
			@param has children: this will decide that left side arrow is render or not.
			@param textcolor: text display color.
		*/
		TARA_EDITOR_API bool ImGui_CustomTreeNode(const char* id, const char* title, bool* select, bool hasChildren, glm::vec3 textcolor);
		/*
			@brief Render custom tree node.
			@param id: Node id.
			@param title: Node title text.
			@param select: This will decide that the background color will draw or not.
			@param has children: this will decide that left side arrow is render or not.
			@param bgcolor: background color, notice that only select is true will draw the background.
		*/
		TARA_EDITOR_API bool ImGui_CustomTreeNode(const char* id, const char* title, bool* select, bool hasChildren, glm::vec4 bgcolor);
		/*
			@brief Render custom tree node.
			@param id: Node id.
			@param title: Node title text.
			@param select: This will decide that the background color will draw or not.
			@param has children: this will decide that left side arrow is render or not.
			@param bgcolor: background color, notice that only select is true will draw the background.
			@param textcolor: text display color.
		*/
		TARA_EDITOR_API bool ImGui_CustomTreeNode(const char* id, const char* title, bool* select, bool hasChildren, glm::vec4 bgcolor, glm::vec3 textcolor);
		TARA_EDITOR_API void ImGui_PieMenu();
		TARA_EDITOR_API void ImGui_Markdown(std::string& text);
		TARA_EDITOR_API void ImGui_BeginGrid(int32_t column = 0, int32_t size = 100, int32_t height = 0);
		TARA_EDITOR_API void ImGui_EndGrid();
		TARA_EDITOR_API bool ImGui_MeshField(const char* title, Mesh* target);
		TARA_EDITOR_API void ImGui_MeshGridImageView(const char* title, std::vector<Mesh*> target, int32_t size = 100, int32_t height = 0, int32_t column = 0, ImGui_EventPack<Mesh>& events = ImGui_EventPack<Mesh>());
		TARA_EDITOR_API bool ImGui_TextureField(const char* title, Texture2D* target);
		TARA_EDITOR_API void ImGui_TextureImageField(Texture2D* target, int32_t size = 100, ImGui_EventPack<Texture2D>& events = ImGui_EventPack<Texture2D>());
		TARA_EDITOR_API void ImGui_TextureVerticalImageField(Texture2D* target, int32_t size = 100, ImGui_EventPack<Texture2D>& events = ImGui_EventPack<Texture2D>());
		TARA_EDITOR_API void ImGui_TextureGridImageView(const char* title, std::vector<Texture2D*> target, int32_t size = 100, int32_t height = 0, int32_t column = 0, ImGui_EventPack<Texture2D>& events = ImGui_EventPack<Texture2D>());
		TARA_EDITOR_API bool ImGui_MaterialField(const char* title, Material* target);
		TARA_EDITOR_API void ImGui_MaterialImageField(Material* target, std::vector<Mesh*> preview);
		TARA_EDITOR_API void ImGui_MaterialVerticalImageField(Material* target, std::vector<Mesh*> preview);
		TARA_EDITOR_API void ImGui_MaterialGridImageView(const char* title, std::vector<Material*> target, int32_t size = 100, int32_t height = 0, int32_t column = 0, ImGui_EventPack<Material>& events = ImGui_EventPack<Material>());
		TARA_EDITOR_API void ImGui_MaterialUniformPropertiesView(Material* target);
		TARA_EDITOR_API void ImGui_ShaderField(Shader* target);
		TARA_EDITOR_API void ImGui_ShaderGridImageView(const char* title, std::vector<Shader*> target, int32_t size = 100, int32_t height = 0, int32_t column = 0, ImGui_EventPack<Shader>& events = ImGui_EventPack<Shader>());
		TARA_EDITOR_API void ImGui_NotifyInit();
		TARA_EDITOR_API void ImGui_SetNotifyType(int32_t type = 4);
		TARA_EDITOR_API void ImGui_SetNotifyDismissTime(int32_t time = 3000);
		TARA_EDITOR_API void ImGui_Notify(const char* title, const char* content);
		TARA_EDITOR_API void ImGui_Notify(std::string title, std::string content);
		TARA_EDITOR_API void ImGui_RenderNotifycation();
		/*
			@brief Render eobject hierachy.
			@param target: Render target.
			@param hightlight: Secondary multiple select array, this will getting secondary highlight.
			@param focus: Primary select target, this will getting highlight.
			@param filter: Filter object to draw.
			@param events: Event trigger pack.
			@result Select result.
		*/
		TARA_EDITOR_API SceneObject* ImGui_SceneObjectHierarchy(SceneObject* target, std::vector<SceneObject*> hightlight = std::vector<SceneObject*>(), SceneObject* focus = nullptr, ImGui_EventPack<SceneObject>& events = ImGui_EventPack<SceneObject>());
		TARA_EDITOR_API SceneObject* ImGui_SceneObjectHierarchy(tree<SceneObject*>& target, std::vector<SceneObject*>& hightlight = std::vector<SceneObject*>(), SceneObject* focus = nullptr, ImGui_EventPack<SceneObject>& events = ImGui_EventPack<SceneObject>());
		TARA_EDITOR_API void ImGui_SceneObjectField(const char* title, SceneObject* target);
		TARA_EDITOR_API void ImGui_SceneObjectImageField(SceneObject* target);
		TARA_EDITOR_API void ImGui_SceneObjectVerticalImageField(SceneObject* target);
		TARA_EDITOR_API void ImGui_SceneObjectGridImageField(SceneObject* target);
		TARA_EDITOR_API void ImGui_EComponentField(SceneObject* target);

		template<typename T>
		TARA_EDITOR_API void FireEventPack(ImGui_EventPack<T>& events, T* target);

		template<typename T>
		inline void FireEventPack(ImGui_EventPack<T>& events, T* target) {
			if (events.Tooltop) {
				if (ImGui_IsItemHovered()) {
					ImGui_BeginTooltip();
					events.Tooltop(target);
					ImGui_EndTooltip();
				}
			}
			if (events.Hovered) {
				if (ImGui_IsItemHovered()) {
					events.Hovered(target);
				}
			}
			if (events.OnClick) {
				if (ImGui_IsItemClicked(MouseButton::Left)) {
					events.OnClick(target, MouseButton::Left);
					if (events.DoubleClick) {
						if (ImGui_IsMouseDoubleClicked(MouseButton::Left)) {
							events.DoubleClick(target, MouseButton::Left);
						}
					}
				}
				else if (ImGui_IsItemClicked(MouseButton::Middle)) {
					events.OnClick(target, MouseButton::Middle);
					if (events.DoubleClick) {
						if(ImGui_IsMouseDoubleClicked(MouseButton::Middle)) {
							events.DoubleClick(target, MouseButton::Middle);
						}
					}
				}
				else if (ImGui_IsItemClicked(MouseButton::Right)) {
					events.OnClick(target, MouseButton::Right);
					if (events.DoubleClick) {
						if (ImGui_IsMouseDoubleClicked(MouseButton::Right)) {
							events.DoubleClick(target, MouseButton::Right);
						}
					}
				}
			}
			if (events.Always) {
				events.Always(target);
			}
		}
	}
}
