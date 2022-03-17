#pragma once
#include <functional>
#include "../engine/core/config.h"

/*
	Gui base, states or enum or const that is often use.
*/
namespace Tara {
	namespace UI {
		enum class TARA_API MouseButton {
			Left = 0,
			Right = 1,
			Middle = 2,
			COUNT = 5,
		};
		/*
			Summary:
				Use for arrow button functional call
		*/
		enum class TARA_API ArrowDirection
		{
			None = -1,
			Left = 0,
			Right = 1,
			Up = 2,
			Down = 3,
			COUNT
		};

		enum class TARA_API EditorKey {
			Tab,
			LeftArrow,
			RightArrow,
			UpArrow,
			DownArrow,
			PageUp,
			PageDown,
			Home,
			End,
			Insert,
			Delete,
			Backspace,
			Space,
			Enter,
			Escape,
			KeyPadEnter,
			A,
			C,
			V,
			X,
			Y,
			Z,
		};

		enum class TARA_API EditorModifieKey {
			None = 0,
			Ctrl = 1 << 0,
			Shift = 1 << 1,
			Alt = 1 << 2,
			Super = 1 << 3
		};

		template<typename T>
		class TARA_API ImGui_EventPack {
		public:
			std::function<void(T*, MouseButton)> OnClick = NULL;
			std::function<void(T*, MouseButton)> DoubleClick = NULL;
			std::function<void(T*)> Tooltop = NULL;
			std::function<void(T*)> Hovered = NULL;
			std::function<void(T*)> Always = NULL;
		};
	}
}