#pragma once
#include "../engine/core/config.h"

#ifndef TARA_NO_IMGUI
// For imgui style change.
#include "editor_style.h"
// For low level imgui function calls.
#include "editor_lowlevel.h"
// For customize gui classes.
#include "editor_container.h"
#include "component/editor_component.h"
#endif

/*
	Summary:
		[ GUI Elements ]
		Organize the gui functions and variables to object oriented programming style,
		And adding additional utility methods to it make it easy to use.
*/

namespace Tara{
	namespace UI {
		/*
			Summary:
				Use this before Tara window is create.
				To registering the events into framework.
		*/
		TARA_API void Tara_GUI_Initialization();
		/*
			Summary:
				Use this after window shutdown or window before create.
				Prevent imgui context points to wrong glfw window.
		*/
		TARA_API void Tara_GUI_Shutdown();
		/*
			Summary:
				Insert new editor window.
		*/
		TARA_API void AddGUIWindow(ImGui_WindowBase* window);
		/*
			Summary:
				Remove editor window.
		*/
		TARA_API void RemoveGUIWindow(ImGui_WindowBase* window);
		/*
			Summary:
				Remove all editor window.
		*/
		TARA_API void CleanGUIWindow();
	}
}