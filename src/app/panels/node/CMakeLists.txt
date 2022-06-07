file(GLOB_RECURSE Creator_NodeFile
	"${ENGINE_DIR}/app/panels/node/*.h"
	"${ENGINE_DIR}/app/panels/node/*.hpp"
	"${ENGINE_DIR}/app/panels/node/*.c"
	"${ENGINE_DIR}/app/panels/node/*.cpp")
	
add_library(Creator_Node SHARED ${Creator_NodeFile})
source_group(TREE "${ENGINE_DIR}/app/panels/node" FILES ${Creator_NodeFile})
set_target_properties(Creator_Node PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_Node PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Node PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Node PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Node PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Node PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Node PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_Node PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(Creator_Node PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Creator_Node PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(Creator_Node PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_Node PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_Node PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_Node PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_Node PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_Node PUBLIC "AppCore.lib")
target_link_libraries(Creator_Node PUBLIC "Engine.lib")
target_link_libraries(Creator_Node PUBLIC "Editor.lib")

set_target_properties(Creator_Node PROPERTIES FOLDER Application/Panels)
