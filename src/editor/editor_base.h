#pragma once
#include <functional>
#include "editor_config.h"

/*
	Gui base, states or enum or const that is often use.
*/
namespace Tara {
	namespace UI {
		enum class TARA_EDITOR_API MouseButton {
			Left = 0,
			Right = 1,
			Middle = 2,
			COUNT = 5,
		};
		/*
			Summary:
				Use for arrow button functional call
		*/
		enum class TARA_EDITOR_API ArrowDirection
		{
			None = -1,
			Left = 0,
			Right = 1,
			Up = 2,
			Down = 3,
			COUNT
		};

		enum class TARA_EDITOR_API EditorKey {
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

		enum class TARA_EDITOR_API EditorModifieKey {
			None = 0,
			Ctrl = 1 << 0,
			Shift = 1 << 1,
			Alt = 1 << 2,
			Super = 1 << 3
		};

		enum class TARA_EDITOR_API PinType
		{
			Flow,
			Bool,
			Int,
			Float,
			String,
			Object,
			Function,
			Delegate,
		};

		enum class TARA_EDITOR_API PinKind
		{
			Output,
			Input
		};

		enum class TARA_EDITOR_API NodeType
		{
			Blueprint,
			Simple,
			Tree,
			Comment
		};

		struct TARA_EDITOR_API Node;

		struct TARA_EDITOR_API Pin
		{
			uintptr_t ID;
			Node* Node;
			std::string Name;
			PinType     Type;
			PinKind     Kind;

			Pin(int id, const char* name, PinType type) :
				ID(id), Node(nullptr), Name(name), Type(type), Kind(PinKind::Input)
			{
			}
		};

		struct TARA_EDITOR_API Node
		{
			uintptr_t ID;
			std::string Name;
			std::vector<Pin> Inputs;
			std::vector<Pin> Outputs;
			glm::vec3 Color;
			NodeType Type;
			glm::vec2 Size;

			std::string State;
			std::string SavedState;

			Node(int id, const char* name, glm::vec3 color = glm::vec3(255, 255, 255)) :
				ID(id), Name(name), Color(color), Type(NodeType::Blueprint), Size(0, 0)
			{
			}
		};

		struct TARA_EDITOR_API Link
		{
			uintptr_t ID;

			uintptr_t StartPinID;
			uintptr_t EndPinID;

			glm::vec3 Color;

			Link(uintptr_t id, uintptr_t startPinId, uintptr_t endPinId) :
				ID(id), StartPinID(startPinId), EndPinID(endPinId), Color(255, 255, 255)
			{
			}
		};

		template<typename T>
		class TARA_EDITOR_API ImGui_EventPack {
		public:
			std::function<void(T*, MouseButton)> OnClick = NULL;
			std::function<void(T*, MouseButton)> DoubleClick = NULL;
			std::function<void(T*)> Tooltop = NULL;
			std::function<void(T*)> Hovered = NULL;
			std::function<void(T*)> Always = NULL;
		};
	}
}