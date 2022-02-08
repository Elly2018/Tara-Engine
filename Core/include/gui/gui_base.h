#pragma once
#include <config.h>

/*
	Gui base, states or enum or const that is often use.
*/
namespace Tara {
	#ifndef TARA_NO_IMGUI
	namespace UI {
		enum class DllExport MouseButton {
			Left = 0,
			Right = 1,
			Middle = 2,
			COUNT = 5,
		};
		/*
			Summary:
				Use for arrow button functional call
		*/
		enum class DllExport ArrowDirection
		{
			None = -1,
			Left = 0,
			Right = 1,
			Up = 2,
			Down = 3,
			COUNT
		};

		template<typename T>
		struct DllExport ImGui_EventPack {
		public:
			typedef void (*BaseEvent)(T* target);
			BaseEvent OnClick = nullptr;
			BaseEvent Tooltop = nullptr;
			BaseEvent Hovered = nullptr;
		};
	}
#endif
}