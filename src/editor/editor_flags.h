#pragma once
#include <iostream>
#include "editor_config.h"

/*
	
*/
namespace Tara {
	namespace UI {
		/*
			Summary:
				The flag struct base
		*/
		struct TARA_EDITOR_API ImGui_FlagBase
		{
		public:
			virtual int32_t	GetFlags();
		};

		struct TARA_EDITOR_API ImGui_ConditionFlags : public ImGui_FlagBase {
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
		struct TARA_EDITOR_API ImGui_WindiwFlags : public ImGui_FlagBase
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
		struct TARA_EDITOR_API ImGui_ComboFlags : public ImGui_FlagBase {
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
		struct TARA_EDITOR_API ImGui_TableFlags : public ImGui_FlagBase {
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
		struct TARA_EDITOR_API ImGui_TabFlagsFitting : public ImGui_FlagBase
		{
		public:
			bool	Resizedown = false;
			bool	Scroll = false;
			int32_t GetFlags() override;
		};
		struct TARA_EDITOR_API ImGui_TabFlags : public ImGui_FlagBase
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
		struct TARA_EDITOR_API ImGui_TabitemsFlags : public ImGui_FlagBase
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
		struct TARA_EDITOR_API ImGui_PopupFlags : public ImGui_FlagBase {
		public:
			bool		MouseButtonLeft = false;
			bool		MouseButtonRight = false;
			bool		MouseButtonMiddle = false;
			bool		MouseButtonMask = false;
			bool		MouseButtonDefault = false;
			bool		NoOpenOverExistingPopup = false;
			bool		NoOpenOverItems = false;
			bool		AnyPopupId = false;
			bool		AnyPopupLevel = false;
			int32_t GetFlags() override;
		};
		struct TARA_EDITOR_API ImGui_SelectableFlags : public ImGui_FlagBase {
		public:
			bool		DontClosePopups = false;
			bool		SpanAllColumns = false;
			bool		AllowDoubleClick = false;
			bool		Disabled = false;
			bool		AllowItemOverlap = false;
			int32_t GetFlags() override;
		};
	}
}