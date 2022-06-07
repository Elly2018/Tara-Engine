cmake_minimum_required(VERSION 3.10)

project(Tara VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-W2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Od -Zi")
set(CMAKE_CXX_FLAGS_RELEASE "-Ox -Ot -Oi")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_compile_options("$<$<CONFIG:DEBUG>:-D_TDEBUG>")
add_compile_options("$<$<CONFIG:RELEASE>:-D_TRELEASE>")
#set(CMAKE_CXX_COMPILER "g++")

set(Root "${CMAKE_CURRENT_SOURCE_DIR}")
set(BIN_DIR "${Root}/bin")
set(ENGINE_DIR "${Root}/src")

set(Platform "Window")
set(RenderAPI "OpenGL")

if(${Platform} STREQUAL "Window")
	add_compile_definitions(WIN32)
	add_compile_definitions(_WINDOWS)
	add_compile_definitions(_USRDLL)
	message(STATUS "Platform: Window")
elseif(${Platform} STREQUAL "MacOS")
elseif(${Platform} STREQUAL "Linux")
endif()

if(${RenderAPI} STREQUAL "OpenGL")
	message(STATUS "RenderAPI: OpenGL")
elseif(${Platform} STREQUAL "Vulkan")
elseif(${Platform} STREQUAL "DirectX")
endif()

include("${Root}/cmake/buildall.cmake")
