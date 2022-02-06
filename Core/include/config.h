#pragma once
#define DllExport __declspec( dllexport )

/*
	Contain some useful macro.
	And a engine configuration pre-processes definition.
*/

#include <iostream>
#include <stdio.h>
#include <logger.h>

/*
	Summary:
		printf color normal
*/
#define KNRM  "\x1B[0m"
/*
	Summary:
		printf color red
*/
#define KRED  "\x1B[31m"
/*
	Summary:	
		printf color green
*/
#define KGRN  "\x1B[32m"
/*
	Summary:
		printf color yellow
*/
#define KYEL  "\x1B[33m"
/*
	Summary:
		printf color blue
*/
#define KBLU  "\x1B[34m"
/*
	Summary:
		printf color magenta
*/
#define KMAG  "\x1B[35m"
/*
	Summary:
		printf color cyan
*/
#define KCYN  "\x1B[36m"
/*
	Summary:
		printf color white
*/
#define KWHT  "\x1B[37m"

/*
	Summary:
		Easy way to combine text together
*/
#define CHAR_COMBINE(a, b, c, d) a b c d
/*
	Summary:
		Default ecomponent constrctor without function bracket
*/
#define DEFAULT_CTOR(x) x(EObject* host) : EComponent(host)
/*
	Summary:
		Default ecomponent constrctor with empty function bracket
*/
#define DEFAULT_CTOR_IMPLE(x) x(EObject* host) : EComponent(host) {};
/*
	Summary:
		Default ecomponent subclass constrctor without function bracket
*/
#define DEFAULT_CTOR_INHERIT(x, y) x(EObject* host) : y(host) {};
/*
	Summary:
		Default ecomponent subclass constrctor with empty function bracket
*/
#define DEFAULT_CTOR_INHERIT_IMPLE(x, y) x(EObject* host) : y(host) {};

// Debug macro
#ifdef _DEBUG
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
	#define TARA_DEBUG_LEVEL(message, level, ...) ((level >= 0) ? TARA_DEBUG(message, __VA_ARGS__) : 0)
	/*
		Summary:
			Yellow color output
			Structure: TARA_DEBUG_LEVEL([format], [level number], [format arguments])
			Example: TARA_DEBUG_LEVEL("Debug message: %s", 2, "arugment text");
	*/
	#define TARA_WARNING_LEVEL(message, level, ...) ((level >= 0) ? TARA_WARNING(message, __VA_ARGS__) : 0)
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

