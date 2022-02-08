#include "einput.h"

namespace Tara {
	#pragma region Static Member Declaration
	double EInput::m_time = 0;
	double EInput::m_delta = 0;
	glm::dvec2 EInput::mouse_position = glm::dvec2(0);
	glm::dvec2 EInput::mouse_delta = glm::dvec2(0);
	glm::dvec2 EInput::scroll = glm::dvec2(0);
	char EInput::last_char_input = NULL;
	std::map<int, std::pair<int, int>> EInput::mousebutton = std::map<int, std::pair<int, int>>();
	std::map<int, std::pair<int, int>> EInput::mousebutton_last = std::map<int, std::pair<int, int>>();
	std::map<int, std::pair<int, int>> EInput::keyboard = std::map<int, std::pair<int, int>>();
	std::map<int, std::pair<int, int>> EInput::keyboard_last = std::map<int, std::pair<int, int>>();
	#pragma endregion

	#pragma region Application Register Callback
	void EInput::KeyInput(int key, int scancode, int action, int mods)
	{
		UpdateKey();
		TARA_DEBUG("%i %i %i %i", key, scancode, action, mods);
		keyboard[key] = std::pair<int, int>(action, mods);
	}
	void EInput::ScrollInput(double xoffset, double yoffset)
	{
		scroll.x = xoffset;
		scroll.y = yoffset;
	}
	void EInput::MouseButtonInput(int button, int action, int mods)
	{
		UpdateMouse();
		mousebutton[button] = std::pair<int, int>(action, mods);
	}
	void EInput::PosInput(double xpos, double ypos)
	{
		mouse_delta.x = xpos - mouse_position.x;
		mouse_delta.y = ypos - mouse_position.y;
		mouse_position.x = xpos;
		mouse_position.y = ypos;
	}
	void EInput::CharInput(unsigned int codepoint)
	{
		last_char_input = codepoint;
	}
	void EInput::Update(double time)
	{
		UpdateMouse();
		UpdateKey();
		m_delta = time - m_time;
		m_time = time;
		mouse_delta = glm::vec2();
	}
	void EInput::Reset()
	{
		m_time = 0;
		m_delta = 0;
	}
	#pragma endregion

	#pragma region Functions
	bool EInput::IsMouseButton(button_action button, int modifier)
	{
		if (mousebutton.find((int)button) == mousebutton.end()) return false;
		std::pair<int, int> buffer = mousebutton[(int)button];
		return buffer.first == 1 && ~((~modifier) | buffer.second) == 0;
	}
	bool EInput::IsMouseButtonDown(button_action button, int modifier)
	{
		if (mousebutton_last.find((int)button) == mousebutton_last.end()) return false;
		if (mousebutton.find((int)button) == mousebutton.end()) return false;
		std::pair<int, int> buffer_last = mousebutton_last[(int)button];
		std::pair<int, int> buffer = mousebutton[(int)button];
		return buffer.first == 1 && buffer_last.first == 0 && ~((~modifier) | buffer.second) == 0;
	}
	bool EInput::IsMouseButtonUp(button_action button, int modifier)
	{
		if (mousebutton_last.find((int)button) == mousebutton_last.end()) return false;
		if (mousebutton.find((int)button) == mousebutton.end()) return false;
		std::pair<int, int> buffer_last = mousebutton_last[(int)button];
		std::pair<int, int> buffer = mousebutton[(int)button];
		return buffer.first == 0 && buffer_last.first == 1 && ~((~modifier) | buffer.second) == 0;
	}
	bool EInput::IsKey(keycode key, int modifier)
	{
		if (keyboard.find((int)key) == keyboard.end()) return false;
		std::pair<int, int> buffer = keyboard[(int)key];
		return buffer.first >= 1 && ~((~modifier) | buffer.second) == 0;
	}
	bool EInput::IsKeyDown(keycode key, int modifier)
	{
		if (keyboard_last.find((int)key) == keyboard_last.end()) return false;
		if (keyboard.find((int)key) == keyboard.end()) return false;
		std::pair<int, int> buffer_last = keyboard_last[(int)key];
		std::pair<int, int> buffer = keyboard[(int)key];
		return buffer.first >= 1 && buffer_last.first >= 0 && ~((~modifier) | buffer.second) == 0;
	}
	bool EInput::IsKeyUp(keycode key, int modifier)
	{
		if (keyboard_last.find((int)key) == keyboard_last.end()) return false;
		if (keyboard.find((int)key) == keyboard.end()) return false;
		std::pair<int, int> buffer_last = keyboard_last[(int)key];
		std::pair<int, int> buffer = keyboard[(int)key];
		return buffer.first == 0 && buffer_last.first == 1 && ~((~modifier) | buffer.second) == 0;
	}
	glm::vec2 EInput::GetMousePosition()
	{
		return mouse_position;
	}
	glm::vec2 EInput::GetMouseDelta()
	{
		return mouse_delta;
	}
	glm::vec2 EInput::GetScrollPosition()
	{
		return scroll;
	}
	char EInput::GetLastChar()
	{
		return last_char_input;
	}
	double EInput::Time()
	{
		return m_time;
	}
	double EInput::Delta()
	{
		return m_delta;
	}
	void EInput::UpdateMouse()
	{
		mousebutton_last = std::map<int, std::pair<int, int>>(mousebutton);
	}
	void EInput::UpdateKey()
	{
		keyboard_last = std::map<int, std::pair<int, int>>(keyboard);
	}
	#pragma endregion
};