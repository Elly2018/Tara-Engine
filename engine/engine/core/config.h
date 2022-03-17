#pragma once
#define DllExport __declspec( dllexport )
#define DllImport __declspec( dllimport )
#define TARA_API

/*
	Contain some useful macro.
	And a engine configuration pre-processes definition.
*/

#include <iostream>
#include <stdio.h>
#include "logger.h"

/*
	Define the current build mode.
	It will depend on build mode to import features.
*/
#pragma region Build Mode
/*
	Core build:
		The very basic tara core, it remove all the extensions and extra features.
		Result will be a very lightweight library.
*/
#ifdef TARA_CORE
	#define TARA_NO_IMGUI
	#define TARA_NO_BUILDIN_2D
	#define TARA_NO_BUILDIN_3D
	#define TARA_NO_EXTENSION_2D
	#define TARA_NO_EXTENSION_3D
	#define TARA_NO_POSTPROCESSING
	#define TARA_NO_LOGGER
#endif
/*
	Engine build:
		Keep the GUI features !
		And some heavy computing features.
*/
#ifdef TARA_3D_ENGINE
// Exclude none !
// Import all the features !!
#endif

#ifdef TARA_2D_ENGINE
// Will exclude 3D relative features.
	#define TARA_NO_EXTENSION_3D
	#define TARA_NO_BUILDIN_3D
#endif

#ifdef TARA_3D_ENGINE_LIGHTWEIGHT
// Reduce size by remove buildin asset.
// User must prepare their own asset in order to use the library.
	#define TARA_NO_BUILDIN_3D
	#define TARA_NO_BUILDIN_2D
#endif

#ifdef TARA_2D_ENGINE_LIGHTWEIGHT
// Reduce size by remove buildin asset.
// User must prepare their own asset in order to use the library.
	#define TARA_NO_BUILDIN_2D
	#define TARA_NO_BUILDIN_3D
#endif
/*
	Game build:
		If it's a game build, remove the GUI and control features !
		But still keep the UI components though
*/
#ifdef TARA_3D_GAME
	#define TARA_NO_IMGUI
#endif

#ifdef TARA_2D_GAME
	#define TARA_NO_IMGUI
	#define TARA_NO_EXTENSION_3D
#endif

#ifdef TARA_3D_GAME_LIGHTWEIGHT
// Reduce size by remove buildin asset.
// User must prepare their own asset in order to use the library.
	#define TARA_NO_IMGUI
	#define TARA_NO_BUILDIN_2D
	#define TARA_NO_BUILDIN_3D
#endif

#ifdef TARA_2D_GAME_LIGHTWEIGHT
// Reduce size by remove buildin asset.
// User must prepare their own asset in order to use the library.
	#define TARA_NO_IMGUI
	#define TARA_NO_BUILDIN_2D
	#define TARA_NO_BUILDIN_3D
	#define TARA_NO_EXTENSION_3D
#endif
#pragma endregion


/*
	Some useful preprocesser const.
*/
#pragma region Const
// Mesh memory loading temp
#define MESH_IMPORT_TEMP ".\\temp\\mesh_import_temp"
#define TEXTURE_IMPORT_TEMP ".\\temp\\texture_import_temp.png"
// Printf color normal
#define KNRM  "\x1B[0m"
// Printf color red
#define KRED  "\x1B[31m"
// Printf color green
#define KGRN  "\x1B[32m"
// Printf color yellow
#define KYEL  "\x1B[33m"
// Printf color blue
#define KBLU  "\x1B[34m"
// Printf color magenta
#define KMAG  "\x1B[35m"
// Printf color cyan
#define KCYN  "\x1B[36m"
// Printf color white
#define KWHT  "\x1B[37m"
// Tara engine normal log color
#define LOGCOLOR_NORMAL glm::vec3(1, 1, 1)
// Tara engine warning log color
#define LOGCOLOR_WARNING glm::vec3(1, 1, 0)
// Tara engine error log color
#define LOGCOLOR_ERROR glm::vec3(1, 0, 0)
#pragma endregion


/*
	Some useful preprocesser macro function.
*/
#pragma region Macro
/*
	Summary:
		Easy way to combine text together
*/
#define CHAR_COMBINE(a, b, c, d) a b c d
/*
	Summary:
		Default ecomponent constrctor without function bracket
*/
#define DEFAULT_HEADER_CTOR(x) x(SceneObject* host)
/*
	Summary:
		Default ecomponent constrctor without function bracket
*/
#define DEFAULT_SRC_CTOR(x) x::x(SceneObject* host) : Component(host)
/*
	Summary:
		Default ecomponent constrctor without function bracket
*/
#define DEFAULT_CTOR(x) x(SceneObject* host) : Component(host)
/*
	Summary:
		Default ecomponent constrctor with empty function bracket
*/
#define DEFAULT_CTOR_IMPLE(x) x(SceneObject* host) : Component(host) {};
/*
	Summary:
		Default ecomponent subclass constrctor without function bracket
*/
#define DEFAULT_CTOR_INHERIT(x, y) x(SceneObject* host) : y(host) {};
/*
	Summary:
		Default ecomponent subclass constrctor with empty function bracket
*/
#define DEFAULT_CTOR_INHERIT_IMPLE(x, y) x(SceneObject* host) : y(host) {};
#pragma endregion


/*
	Debug output message macro.
	It change depends on current buildmode.
*/
#pragma region Debug Macro
// Debug macro
#ifndef TARA_NO_LOGGER
// The debug function without level control
/*
	Summary:
		Normal color output
		Structure: TARA_DEBUG_LEVEL([format], [format arguments])
		Example: TARA_DEBUG_LEVEL("Debug message: %s", "arugment text");
*/
#define TARA_DEBUG(message, ...) printf(CHAR_COMBINE("[System] ", message, "\n"), __VA_ARGS__)
/*
	Summary:
		Yellow color output
		Structure: TARA_ERROR([format], [format arguments])
		Example: TARA_ERROR("Debug message: %s", "arugment text");
*/
#define TARA_WARNING(message, ...) printf(CHAR_COMBINE("[Warning] ", message, "\n"), __VA_ARGS__)
/*
	Summary:
		Red color output
		Structure: TARA_ERROR([format], [format arguments])
		Example: TARA_ERROR("Debug message: %s", "arugment text");
*/
#define TARA_ERROR(message, ...) printf(CHAR_COMBINE("[Error] ", message, "\n"), __VA_ARGS__)
/*
	Summary:
		Throw a runtime error with input error message
		Structure: TARA_RUNTIME_ERROR([message])
		Example: TARA_RUNTIME_ERROR("index is out of range");
*/
#define TARA_RUNTIME_ERROR(x) throw new std::runtime_error(x)

// Debug level control 0 - 5
#ifndef DEBUG_LEVEL
	#define DEBUG_LEVEL 4
#endif // DEBUG_LEVEL
#ifndef DEBUG_FILENAME
	#define DEBUG_FILENAME "log.txt"
#endif // DEBUG_LEVEL
// The debug function with level control
#if DEBUG_LEVEL >= 0 && DEBUG_LEVEL <= 5
	/*
		Summary:
			Normal color output
			Structure: TARA_DEBUG_LEVEL([format], [level number], [format arguments])
			Example: TARA_DEBUG_LEVEL("Debug message: %s", 2, "arugment text");
	*/
	#define TARA_DEBUG_LEVEL(message, level, ...) ((level >= DEBUG_LEVEL) ? TARA_DEBUG(message, __VA_ARGS__) : 0)
	/*
		Summary:
			Yellow color output
			Structure: TARA_DEBUG_LEVEL([format], [level number], [format arguments])
			Example: TARA_DEBUG_LEVEL("Debug message: %s", 2, "arugment text");
	*/
	#define TARA_WARNING_LEVEL(message, level, ...) ((level >= DEBUG_LEVEL) ? TARA_WARNING(message, __VA_ARGS__) : 0)
	/*
		Summary:
			Red color output
			Structure: TARA_ERROR_LEVEL([format], [level number], [format arguments])
			Example: TARA_ERROR_LEVEL("Debug message: %s", 2, "arugment text");
	*/
	#define TARA_ERROR_LEVEL(message, level, ...) ((level >= DEBUG_LEVEL) ? TARA_ERROR(message, __VA_ARGS__) : 0)
#endif // DEBUG_LEVEL >= 0 && DEBUG_LEVEL <= 5
#else
// Remove debug function during release mode
#define TARA_DEBUG_LEVEL(message, level, ...)
#define TARA_WARNING_LEVEL(message, level, ...)
#define TARA_ERROR_LEVEL(message, level, ...)
#define TARA_DEBUG(x, ...)
#define TARA_WARNING(x, ...)
#define TARA_ERROR(x, ...)
#define TARA_RUNTIME_ERROR(x)
#endif // _DEBUG
#pragma endregion