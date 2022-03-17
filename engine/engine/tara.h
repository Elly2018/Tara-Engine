#pragma once

/*
	Quick way to include the Tara engine.
	Notices:
		#include <engine.h>
		Does not contain window related and gui drawing methods and classes.

	In case you need those, Use below:
		#include <ewindow.h>
		To include window related and gui drawing methods and classes.
*/

#include "core/config.h"

using namespace glm;

namespace Tara {
	/// <summary>
	/// Initialize the resources and allocate memory locations.
	/// </summary>
	TARA_API bool Tara_Initialization();
	/// <summary>
	/// Release tara resources memory.
	/// </summary>
	TARA_API bool Tara_Shutdown();
}