#include "editor_flags.h"
#include <imgui.h>

namespace Tara {
	namespace UI {
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
			if (UnSave) buffer |= ImGuiTabItemFlags_UnsavedDocument;
			if (SetSelect) buffer |= ImGuiTabItemFlags_SetSelected;
			if (NoCloseMiddleMouse) buffer |= ImGuiTabItemFlags_NoCloseWithMiddleMouseButton;
			if (NoPushID) buffer |= ImGuiTabItemFlags_NoPushId;
			if (NoTooltip) buffer |= ImGuiTabItemFlags_NoTooltip;
			if (NoReOrder) buffer |= ImGuiTabItemFlags_NoReorder;
			if (Leading) buffer |= ImGuiTabItemFlags_Leading;
			if (Trailing) buffer |= ImGuiTabItemFlags_Trailing;
			return buffer;
		}
		int32_t ImGui_PopupFlags::GetFlags()
		{
			int32_t buffer = 0;
			if (MouseButtonLeft) buffer |= ImGuiPopupFlags_MouseButtonLeft;
			if (MouseButtonRight) buffer |= ImGuiPopupFlags_MouseButtonRight;
			if (MouseButtonMiddle) buffer |= ImGuiPopupFlags_MouseButtonMiddle;
			if (MouseButtonMask) buffer |= ImGuiPopupFlags_MouseButtonMask_;
			if (MouseButtonDefault) buffer |= ImGuiPopupFlags_MouseButtonDefault_;
			if (NoOpenOverExistingPopup) buffer |= ImGuiPopupFlags_NoOpenOverExistingPopup;
			if (NoOpenOverItems) buffer |= ImGuiPopupFlags_NoOpenOverItems;
			if (AnyPopupId) buffer |= ImGuiPopupFlags_AnyPopupId;
			if (AnyPopupLevel) buffer |= ImGuiPopupFlags_AnyPopupLevel;
			return buffer;
		}
		int32_t ImGui_SelectableFlags::GetFlags()
		{
			int32_t buffer = 0;
			if (DontClosePopups) buffer |= ImGuiSelectableFlags_DontClosePopups;
			if (SpanAllColumns) buffer |= ImGuiSelectableFlags_SpanAllColumns;
			if (AllowDoubleClick) buffer |= ImGuiSelectableFlags_AllowDoubleClick;
			if (Disabled) buffer |= ImGuiSelectableFlags_Disabled;
			if (AllowItemOverlap) buffer |= ImGuiSelectableFlags_AllowItemOverlap;
			return buffer;
		}
}
}