file(GLOB_RECURSE Creator_ProjectCreation 
	"${ENGINE_DIR}/app/panels/project_creation/*.h"
	"${ENGINE_DIR}/app/panels/project_creation/*.hpp"
	"${ENGINE_DIR}/app/panels/project_creation/*.c"
	"${ENGINE_DIR}/app/panels/project_creation/*.cpp")
	
add_library(Creator_ProjectCreation SHARED ${Creator_ProjectCreation})
source_group(TREE "${ENGINE_DIR}/app/panels/project_creation" FILES ${Creator_ProjectCreation})
set_target_properties(Creator_ProjectCreation PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_ProjectCreation PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_ProjectCreation PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_ProjectCreation PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_ProjectCreation PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_ProjectCreation PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_ProjectCreation PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_ProjectCreation PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(Creator_ProjectCreation PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Creator_ProjectCreation PUBLIC TARA_Editor_API=DLLIMPORT)

target_include_directories(Creator_ProjectCreation PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_ProjectCreation PUBLIC "${ENGINE_DIR}/app/panels/explorer")
target_include_directories(Creator_ProjectCreation PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_ProjectCreation PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_ProjectCreation PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_ProjectCreation PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_ProjectCreation PUBLIC "AppCore.lib")
target_link_libraries(Creator_ProjectCreation PUBLIC "Engine.lib")
target_link_libraries(Creator_ProjectCreation PUBLIC "Editor.lib")
target_link_libraries(Creator_ProjectCreation PUBLIC "Creator_FileExplorer.lib")

set_target_properties(Creator_ProjectCreation PROPERTIES FOLDER Application/Panels)
