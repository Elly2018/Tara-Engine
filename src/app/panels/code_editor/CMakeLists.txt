file(GLOB_RECURSE Creator_CodeEditorFile
	"${ENGINE_DIR}/app/panels/code_editor/*.h"
	"${ENGINE_DIR}/app/panels/code_editor/*.hpp"
	"${ENGINE_DIR}/app/panels/code_editor/*.c"
	"${ENGINE_DIR}/app/panels/code_editor/*.cpp")
	
add_library(Creator_CodeEditor SHARED ${Creator_CodeEditorFile})
source_group(TREE "${ENGINE_DIR}/app/panels/code_editor" FILES ${Creator_CodeEditorFile})
set_target_properties(Creator_CodeEditor PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_CodeEditor PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_CodeEditor PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_CodeEditor PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_CodeEditor PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_CodeEditor PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_CodeEditor PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_CodeEditor PUBLIC TARA_API=DLLEXPORT)
target_compile_definitions(Creator_CodeEditor PUBLIC TARA_EDITOR_API=DLLEXPORT)

target_include_directories(Creator_CodeEditor PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_CodeEditor PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_CodeEditor PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_CodeEditor PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_CodeEditor PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_CodeEditor PUBLIC "AppCore.lib")
target_link_libraries(Creator_CodeEditor PUBLIC "Engine.lib")
target_link_libraries(Creator_CodeEditor PUBLIC "Editor.lib")

set_target_properties(Creator_CodeEditor PROPERTIES FOLDER Application/Panels)
