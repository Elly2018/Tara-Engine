# Editor Library
file(GLOB_RECURSE EDITOR_Files 
	"${ENGINE_DIR}/core/editor/*.h"
	"${ENGINE_DIR}/core/editor/*.hpp"
	"${ENGINE_DIR}/core/editor/*.c"
	"${ENGINE_DIR}/core/editor/*.cpp")
	
add_library(Editor SHARED ${EDITOR_Files})
source_group(TREE "${ENGINE_DIR}/core/editor" FILES ${EDITOR_Files})
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
target_include_directories(Editor PUBLIC "${Root}/lib/uuid4")

target_link_directories(Editor PUBLIC "${BIN_DIR}")
target_link_directories(Editor PUBLIC "${Root}/lib/glfw/lib-vc2022")

target_link_libraries(Editor PUBLIC "Engine.lib")
target_link_libraries(Editor PUBLIC "glfw3dll.lib")

set_target_properties(Editor PROPERTIES FOLDER Core)
