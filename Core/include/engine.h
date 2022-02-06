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

#include <scene.h>
#include <texture.h>
#include <framebuffer.h>
#include <einput.h>
#include <world.h>
#include <renderer.h>
#include <glm/glm.hpp>
#include <utility>

using namespace glm;