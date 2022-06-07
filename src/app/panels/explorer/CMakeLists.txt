file(GLOB_RECURSE Creator_FileExplorerFile
	"${ENGINE_DIR}/app/panels/explorer/*.h"
	"${ENGINE_DIR}/app/panels/explorer/*.hpp"
	"${ENGINE_DIR}/app/panels/explorer/*.c"
	"${ENGINE_DIR}/app/panels/explorer/*.cpp")
	
add_library(Creator_FileExplorer SHARED ${Creator_FileExplorerFile})
source_group(TREE "${ENGINE_DIR}/app/panels/explorer" FILES ${Creator_FileExplorerFile})
set_target_properties(Creator_FileExplorer PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_FileExplorer PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_FileExplorer PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_FileExplorer PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_FileExplorer PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_FileExplorer PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_FileExplorer PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_FileExplorer PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(Creator_FileExplorer PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Creator_FileExplorer PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(Creator_FileExplorer PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_FileExplorer PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_FileExplorer PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_FileExplorer PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_FileExplorer PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_FileExplorer PUBLIC "AppCore.lib")
target_link_libraries(Creator_FileExplorer PUBLIC "Engine.lib")
target_link_libraries(Creator_FileExplorer PUBLIC "Editor.lib")

set_target_properties(Creator_FileExplorer PROPERTIES FOLDER Application/Panels)
