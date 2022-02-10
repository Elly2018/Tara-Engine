#pragma once
#include <map>
#include <glm/glm.hpp>
#include <config.h>
#include <ewindow.h>

namespace Tara {
	#pragma region Enum
	/*
		Summary:
			Button index, it can use on mouse button.
			Left mouse button = Button1.
			Right mouse button = Button2... etc.
	*/
	DllExport enum class button_action {
		Button1 = 0,
		Button2 = 1,
		Button3 = 2,
	};
	/*
		Summary:
			The modifier state for button input, It can check multiple states.
	*/
	DllExport enum class button_modifier {
		Shift = 1,
		Control = 2,
		Alt = 4,
		Super = 8,
		Cap_Lock = 16,
		Num_Lock = 32,
	};
	/*
		Summary:
			Keyboard input enum.
	*/
	DllExport enum class keycode {
		UNKNOWN = -1,
		SPACE = 32,
		/// <summary>
		/// '
		/// </summary>
		APOSTROPHE = 39,
		/// <summary>
		/// ,
		/// </summary>
		COMMA = 44,
		/// <summary>
		/// -
		/// </summary>
		MINUS = 45,
		/// <summary>
		/// .
		/// </summary>
		PERIOD = 46,
		/// <summary>
		/// /
		/// </summary>
		SLASH = 47,
		KEY_0 = 48,
		KEY_1 = 49,
		KEY_2 = 50,
		KEY_3 = 51,
		KEY_4 = 52,
		KEY_5 = 53,
		KEY_6 = 54,
		KEY_7 = 55,
		KEY_8 = 56,
		KEY_9 = 57,
		/// <summary>
		/// ;
		/// </summary>
		SEMICOLON = 59,
		/// <summary>
		/// =
		/// </summary>
		EQUAL = 61,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		/// <summary>
		/// [
		/// </summary>
		LEFT_BRACKET = 91,
		/// <summary>
		/// \
		/// </summary>
		BACKSLASH = 92,
		/// <summary>
		/// ]
		/// </summary>
		RIGHT_BRACKET = 93,
		/// <summary>
		/// `
		/// </summary>
		GRAVE_ACCOUNT = 96,
		WORLD_1 = 161,
		WORLD_2 = 162,
		ESCAPE = 256,
		ENTER = 257,
		TAB = 258,
		BACKSPACE = 259,
		INSERT = 260,
		_DELETE = 261,
		RIGHT = 262,
		LEFT = 263,
		DOWN = 264,
		UP = 265,
		PAGE_UP = 266,
		PAGE_DOWN = 267,
		HOME = 268,
		END = 269,
		CAPS_LOCK = 280,
		SCROLL_LOCK = 281,
		NUM_LOCK = 282,
		PRINT_SCREEN = 283,
		PAUSE = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		KP_0 = 320,
		KP_1 = 321,
		KP_2 = 322,
		KP_3 = 323,
		KP_4 = 324,
		KP_5 = 325,
		KP_6 = 326,
		KP_7 = 327,
		KP_8 = 328,
		KP_9 = 329,
		KP_DECIMAL = 330,
		KP_DIVIDE = 331,
		KP_MULTIPLY = 332,
		KP_SUBTRACT = 333,
		KP_ADD = 334,
		KP_ENTER = 335,
		KP_EQUAL = 336,
		LEFT_SHIFT = 340,
		LEFT_CONTROL = 341,
		LEFT_ALT = 342,
		LEFT_SUPER = 343,
		RIGHT_SHIFT = 344,
		RIGHT_CONTROL = 345,
		RIGHT_ALT = 346,
		RIGHT_SUPER = 347,
		MENU = 348
	};
	#pragma endregion

	/*
		Summary:
			Application global input state.
	*/
	class DllExport EInput
	{
		// Let window class access private application register callback methods.
		friend class EWindow;
	#pragma region Application Register Callback
	private:
		/*
			Summary: 
				Application register callback, Do not manually call this method.
		*/
		static void KeyInput(int key, int scancode, int action, int mods);
		/*
			Summary:
				Application register callback, Do not manually call this method.
		*/
		static void ScrollInput(double xoffset, double yoffset);
		/*
			Summary:
				Application register callback, Do not manually call this method.
		*/
		static void MouseButtonInput(int button, int action, int mods);
		/*
			Summary:
				Application register callback, Do not manually call this method.
		*/
		static void PosInput(double xpos, double ypos);
		/*
			Summary:
				Application register callback, Do not manually call this method.
		*/
		static void CharInput(unsigned int codepoint);
		/*
			Summary:
				Application register callback, Do not manually call this method.
		*/
		static void Update(double time);
		/*
			Summary:
				Application register callback, Do not manually call this method.
		*/
		static void Reset();
	#pragma endregion

	#pragma region Functions
	public:
		/*
			Summary:
				Check if mouse button is presse at current frame.
		*/
		static bool IsMouseButton(button_action button, int modifier = 0);
		/*
			Summary:
				Check if mouse button is presse at the moment.
		*/
		static bool IsMouseButtonDown(button_action button, int modifier = 0);
		/*
			Summary:
				Check if mouse button is release at the moment.
		*/
		static bool IsMouseButtonUp(button_action button, int modifier = 0);
		/*
			Summary:
				Check if key is presse at current frame.
		*/
		static bool IsKey(keycode key, int modifier = 0);
		/*
			Summary:
				Check if key is presse at the moment.
		*/
		static bool IsKeyDown(keycode key, int modifier = 0);
		/*
			Summary:
				Check if key is release at the moment.
		*/
		static bool IsKeyUp(keycode key, int modifier = 0);
		/*
			Summary:
				Get current mouse position.
		*/
		static glm::vec2 GetMousePosition();
		/*
			Summary:
				Get current mouse delta vector.
		*/
		static glm::vec2 GetMouseDelta();
		/*
			Summary:
				Get current scroll vector.
		*/
		static glm::vec2 GetScrollPosition();
		/*
			Summary:
				Get last keyborad input.
		*/
		static char GetLastChar();
	#pragma endregion

	public:
		/*
			Summary:
				Get total time pass.
		*/
		static double_t Time();
		/*
			Summary:
				Get current frame update delta time.
		*/
		static double_t Delta();
	private:
		/*
			Summary:
				Each mouse relate method get called,
				it will update the state,
				prepare for next update called.
		*/
		static void UpdateMouse();
		/*
			Summary:
				Each key relate method get called,
				it will update the state,
				prepare for next update called.
		*/
		static void UpdateKey();

		static double_t m_time;
		static double_t m_delta;
		static glm::dvec2 mouse_position;
		static glm::dvec2 mouse_delta;
		static glm::dvec2 scroll;
		static char last_char_input;
		static std::map<int, std::pair<int, int>> mousebutton;
		static std::map<int, std::pair<int, int>> mousebutton_last;
		static std::map<int, std::pair<int, int>> keyboard;
		static std::map<int, std::pair<int, int>> keyboard_last;
	};
}