cmake_minimum_required(VERSION 3.10)

project(Tara VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CXX_COMPILER "g++")

set(Root "${CMAKE_CURRENT_SOURCE_DIR}")
set(BIN_DIR "${Root}/bin")
set(ENGINE_DIR "${Root}/engine")

# Core library
add_compile_definitions(WIN32)
add_compile_definitions(_DEBUG)
add_compile_definitions(_WINDOWS)
add_compile_definitions(_USRDLL)
add_compile_definitions(DEBUG_LEVEL=1)

file(GLOB_RECURSE Engine_Files 
	"${CMAKE_CURRENT_SOURCE_DIR}/engine/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/engine/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/engine/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp")

add_executable(Engine ${Engine_Files})

source_group(TREE ${ENGINE_DIR} FILES ${Engine_Files})

set_target_properties(Engine PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Engine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Engine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")

target_include_directories(Engine PUBLIC "${Root}/lib/glfw/include")
target_include_directories(Engine PUBLIC "${Root}/lib/glad/include")
target_include_directories(Engine PUBLIC "${Root}/lib/glm/include")
target_include_directories(Engine PUBLIC "${Root}/lib/devil/include")
target_include_directories(Engine PUBLIC "${Root}/lib/stb")
target_include_directories(Engine PUBLIC "${Root}/lib/utility")
target_include_directories(Engine PUBLIC "${Root}/lib/backward")
target_include_directories(Engine PUBLIC "${Root}/lib/assimp/include")
target_include_directories(Engine PUBLIC "${Root}/lib/base64")
target_include_directories(Engine PUBLIC "${Root}/lib/json/include")
target_include_directories(Engine PUBLIC "${Root}/lib/libarchive-3.6.0/libarchive")
target_include_directories(Engine PUBLIC "${Root}/lib/imgui/imgui_1.87")
target_include_directories(Engine PUBLIC "${Root}/lib/imgui/imgui_curve")
target_include_directories(Engine PUBLIC "${Root}/lib/imgui/imgui_markdown")
target_include_directories(Engine PUBLIC "${Root}/lib/imgui/imgui_color-text-edit")
target_include_directories(Engine PUBLIC "${Root}/lib/imgui/imgui_gizmo-1.83")
target_include_directories(Engine PUBLIC "${Root}/lib/imgui/imgui_node-editor-0.9/NodeEditor/Source")
target_include_directories(Engine PUBLIC "${Root}/lib/imgui/imgui_node-editor-0.9/NodeEditor/Include")
target_include_directories(Engine PUBLIC "${Root}/lib/imgui/imgui-notify-2/include")

target_link_directories(Engine PUBLIC "${Root}/lib/glfw/lib-vc2019")
target_link_directories(Engine PUBLIC "${Root}/lib/devil/lib/x64/Release")
target_link_directories(Engine PUBLIC "${Root}/lib/assimp/lib64")
target_link_directories(Engine PUBLIC "${Root}/lib/libarchive-3.6.0/libarchive/Debug")

target_link_libraries(Engine PUBLIC "glfw3dll.lib")
target_link_libraries(Engine PUBLIC "DevIL.lib")
target_link_libraries(Engine PUBLIC "ILU.lib")
target_link_libraries(Engine PUBLIC "ILUT.lib")
target_link_libraries(Engine PUBLIC "assimp.lib")
target_link_libraries(Engine PUBLIC "archive.lib")