cmake_minimum_required(VERSION 3.10)

project(Tara VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-W2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Od -Zi")
set(CMAKE_CXX_FLAGS_RELEASE "-Ox -Ot -Oi")
#set(CMAKE_CXX_COMPILER "g++")

set(Root "${CMAKE_CURRENT_SOURCE_DIR}")
set(BIN_DIR "${Root}/bin")
set(ENGINE_DIR "${Root}/src")

# Core Library
#add_compile_definitions(WIN32)
#add_compile_definitions(_DEBUG)
#add_compile_definitions(_WINDOWS)
#add_compile_definitions(_USRDLL)
file(GLOB_RECURSE Engine_Files
	"${ENGINE_DIR}/engine/*.h"
	"${ENGINE_DIR}/engine/*.hpp"
	"${ENGINE_DIR}/engine/*.c"
	"${ENGINE_DIR}/engine/*.cpp")
file(GLOB_RECURSE Engine_Lib_Files
	"${ENGINE_DIR}/lib/engine/*.c"
	"${ENGINE_DIR}/lib/engine/*.cpp")
add_library(Engine SHARED ${Engine_Files} ${Engine_Lib_Files})
source_group(TREE "${ENGINE_DIR}" FILES ${Engine_Files})
source_group(TREE "${ENGINE_DIR}" FILES ${Engine_Lib_Files})
set_target_properties(Engine PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Engine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Engine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Engine PUBLIC TARA_API=DLLEXPORT)

target_include_directories(Engine PUBLIC "${Root}/lib/glfw/include")
target_include_directories(Engine PUBLIC "${Root}/lib/glad/include")
target_include_directories(Engine PUBLIC "${Root}/lib/glm")
target_include_directories(Engine PUBLIC "${Root}/lib/devil/include")
target_include_directories(Engine PUBLIC "${Root}/lib/stb")
target_include_directories(Engine PUBLIC "${Root}/lib/utility")
target_include_directories(Engine PUBLIC "${Root}/lib/backward-cpp")
target_include_directories(Engine PUBLIC "${Root}/lib/assimp/include")
target_include_directories(Engine PUBLIC "${Root}/lib/base64")
target_include_directories(Engine PUBLIC "${Root}/lib/json/include")
target_include_directories(Engine PUBLIC "${Root}/lib/libarchive/libarchive")

target_link_directories(Engine PUBLIC "${Root}/lib/glfw/lib-vc2022")
target_link_directories(Engine PUBLIC "${Root}/lib/devil/lib/x64/Release")
target_link_directories(Engine PUBLIC "${Root}/lib/assimp/lib/Release")
target_link_directories(Engine PUBLIC "${Root}/lib/libarchive/libarchive/Release")

target_link_libraries(Engine PUBLIC "glfw3dll.lib")
target_link_libraries(Engine PUBLIC "DevIL.lib")
target_link_libraries(Engine PUBLIC "ILU.lib")
target_link_libraries(Engine PUBLIC "ILUT.lib")
target_link_libraries(Engine PUBLIC "assimp-vc142-mt.lib")
target_link_libraries(Engine PUBLIC "archive.lib")

# Editor Library
file(GLOB_RECURSE EDITOR_Files 
	"${ENGINE_DIR}/editor/*.h"
	"${ENGINE_DIR}/editor/*.hpp"
	"${ENGINE_DIR}/editor/*.c"
	"${ENGINE_DIR}/editor/*.cpp")
file(GLOB_RECURSE EDITOR_Lib_Files 
	"${ENGINE_DIR}/lib/editor/*.c"
	"${ENGINE_DIR}/lib/editor/*.cpp")
	
add_library(Editor SHARED ${EDITOR_Files} ${EDITOR_Lib_Files})
source_group(TREE "${ENGINE_DIR}" FILES ${EDITOR_Files})
source_group(TREE "${ENGINE_DIR}" FILES ${EDITOR_Lib_Files})
set_target_properties(Editor PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Editor PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Editor PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Editor PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Editor PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Editor PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Editor PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Editor PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Editor PRIVATE TARA_EDITOR_API=DLLEXPORT)

target_include_directories(Editor PUBLIC "${ENGINE_DIR}")
target_include_directories(Editor PUBLIC "${Root}/lib/glfw/include")
target_include_directories(Editor PUBLIC "${Root}/lib/glad/include")
target_include_directories(Editor PUBLIC "${Root}/lib/glm")
target_include_directories(Editor PUBLIC "${Root}/lib/json/include")
target_include_directories(Editor PUBLIC "${Root}/lib/imgui/imgui")
target_include_directories(Editor PUBLIC "${Root}/lib/imgui/imgui/backends")
target_include_directories(Editor PUBLIC "${Root}/lib/imgui/imgui_curve")
target_include_directories(Editor PUBLIC "${Root}/lib/imgui/imgui_markdown")
target_include_directories(Editor PUBLIC "${Root}/lib/imgui/ImGuiColorTextEdit")
target_include_directories(Editor PUBLIC "${Root}/lib/imgui/ImGuizmo")
target_include_directories(Editor PUBLIC "${Root}/lib/imgui/imgui-notify/example/src")

target_link_directories(Editor PUBLIC "${BIN_DIR}")
target_link_directories(Editor PUBLIC "${Root}/lib/glfw/lib-vc2022")

target_link_libraries(Editor PUBLIC "Engine.lib")
target_link_libraries(Editor PUBLIC "glfw3dll.lib")

# App Executable
file(GLOB_RECURSE App_Files 
	"${ENGINE_DIR}/app/*.h"
	"${ENGINE_DIR}/app/*.hpp"
	"${ENGINE_DIR}/app/*.c"
	"${ENGINE_DIR}/app/*.cpp")
file(GLOB_RECURSE App_Lib_Files 
	"${ENGINE_DIR}/lib/app/*.c"
	"${ENGINE_DIR}/lib/app/*.cpp")
	
add_executable(App ${App_Files} ${App_Lib_Files})
source_group(TREE "${ENGINE_DIR}" FILES ${App_Files})
source_group(TREE "${ENGINE_DIR}" FILES ${App_Lib_Files})
set_target_properties(App PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(App PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(App PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(App PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(App PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(App PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(App PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(App PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(App PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(App PUBLIC "${ENGINE_DIR}")
target_include_directories(App PUBLIC "${Root}/lib/glm")
target_include_directories(App PUBLIC "${Root}/lib/json/include")

target_link_directories(App PUBLIC "${BIN_DIR}")

target_link_libraries(App PUBLIC "Engine.lib")
target_link_libraries(App PUBLIC "Editor.lib")


# Single Build
file(GLOB_RECURSE Single_Files 
	"${ENGINE_DIR}/*.h"
	"${ENGINE_DIR}/*.hpp"
	"${ENGINE_DIR}/*.c"
	"${ENGINE_DIR}/*.cpp")
file(GLOB_RECURSE Single_Lib_Files 
	"${ENGINE_DIR}/lib/*.c"
	"${ENGINE_DIR}/lib/*.cpp")
list(REMOVE_ITEM ${Single_Lib_Files} "${ENGINE_DIR}/lib/editor/glad.cpp")
	
add_executable(Single ${Single_Files} ${Single_Lib_Files})
source_group(TREE "${ENGINE_DIR}" FILES ${Single_Files})
source_group(TREE "${ENGINE_DIR}" FILES ${Single_Lib_Files})
set_target_properties(Single PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Single PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Single PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Single PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Single PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Single PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Single PUBLIC TARA_API=)
target_compile_definitions(Single PUBLIC TARA_EDITOR_API=)
target_include_directories(Single PUBLIC "${Root}/lib/glfw/include")
target_include_directories(Single PUBLIC "${Root}/lib/glad/include")
target_include_directories(Single PUBLIC "${Root}/lib/glm")
target_include_directories(Single PUBLIC "${Root}/lib/devil/include")
target_include_directories(Single PUBLIC "${Root}/lib/stb")
target_include_directories(Single PUBLIC "${Root}/lib/utility")
target_include_directories(Single PUBLIC "${Root}/lib/backward-cpp")
target_include_directories(Single PUBLIC "${Root}/lib/assimp/include")
target_include_directories(Single PUBLIC "${Root}/lib/base64")
target_include_directories(Single PUBLIC "${Root}/lib/json/include")
target_include_directories(Single PUBLIC "${Root}/lib/libarchive/libarchive")
target_include_directories(Single PUBLIC "${Root}/lib/imgui/imgui")
target_include_directories(Single PUBLIC "${Root}/lib/imgui/imgui/backends")
target_include_directories(Single PUBLIC "${Root}/lib/imgui/imgui_curve")
target_include_directories(Single PUBLIC "${Root}/lib/imgui/imgui_markdown")
target_include_directories(Single PUBLIC "${Root}/lib/imgui/ImGuiColorTextEdit")
target_include_directories(Single PUBLIC "${Root}/lib/imgui/ImGuizmo")
target_include_directories(Single PUBLIC "${Root}/lib/imgui/imgui-node-editor/NodeEditor/Source")
target_include_directories(Single PUBLIC "${Root}/lib/imgui/imgui-node-editor/NodeEditor/Include")
target_include_directories(Single PUBLIC "${Root}/lib/imgui/imgui-notify/example/src")

target_link_directories(Single PUBLIC "${Root}/lib/glfw/lib-vc2022")
target_link_directories(Single PUBLIC "${Root}/lib/devil/lib/x64/Release")
target_link_directories(Single PUBLIC "${Root}/lib/assimp/lib/Release")
target_link_directories(Single PUBLIC "${Root}/lib/libarchive/libarchive/Release")

target_link_libraries(Single PUBLIC "glfw3.lib")
target_link_libraries(Single PUBLIC "DevIL.lib")
target_link_libraries(Single PUBLIC "ILU.lib")
target_link_libraries(Single PUBLIC "ILUT.lib")
target_link_libraries(Single PUBLIC "assimp-vc142-mt.lib")
target_link_libraries(Single PUBLIC "archive.lib")
