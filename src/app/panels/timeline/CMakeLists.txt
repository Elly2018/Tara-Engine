file(GLOB_RECURSE Creator_TimelineFile
	"${ENGINE_DIR}/app/panels/timeline/*.h"
	"${ENGINE_DIR}/app/panels/timeline/*.hpp"
	"${ENGINE_DIR}/app/panels/timeline/*.c"
	"${ENGINE_DIR}/app/panels/timeline/*.cpp")
	
add_library(Creator_Timeline SHARED ${Creator_TimelineFile})
source_group(TREE "${ENGINE_DIR}/app/panels/timeline" FILES ${Creator_TimelineFile})
set_target_properties(Creator_Timeline PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_Timeline PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Timeline PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Timeline PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Timeline PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Timeline PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Timeline PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_Timeline PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(Creator_Timeline PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Creator_Timeline PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(Creator_Timeline PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_Timeline PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_Timeline PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_Timeline PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_Timeline PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_Timeline PUBLIC "AppCore.lib")
target_link_libraries(Creator_Timeline PUBLIC "Engine.lib")
target_link_libraries(Creator_Timeline PUBLIC "Editor.lib")

set_target_properties(Creator_Timeline PROPERTIES FOLDER Application/Panels)
