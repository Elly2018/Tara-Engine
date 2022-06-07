file(GLOB_RECURSE Creator_HierarchyFile
	"${ENGINE_DIR}/app/panels/hierarchy/*.h"
	"${ENGINE_DIR}/app/panels/hierarchy/*.hpp"
	"${ENGINE_DIR}/app/panels/hierarchy/*.c"
	"${ENGINE_DIR}/app/panels/hierarchy/*.cpp")
	
add_library(Creator_Hierarchy SHARED ${Creator_HierarchyFile})
source_group(TREE "${ENGINE_DIR}/app/panels/hierarchy" FILES ${Creator_HierarchyFile})
set_target_properties(Creator_Hierarchy PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_Hierarchy PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Hierarchy PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Hierarchy PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Hierarchy PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Hierarchy PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Hierarchy PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_Hierarchy PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(Creator_Hierarchy PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Creator_Hierarchy PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(Creator_Hierarchy PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_Hierarchy PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_Hierarchy PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_Hierarchy PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_Hierarchy PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_Hierarchy PUBLIC "AppCore.lib")
target_link_libraries(Creator_Hierarchy PUBLIC "Engine.lib")
target_link_libraries(Creator_Hierarchy PUBLIC "Editor.lib")

set_target_properties(Creator_Hierarchy PROPERTIES FOLDER Application/Panels)
