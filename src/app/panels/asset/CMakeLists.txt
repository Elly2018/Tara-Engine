file(GLOB_RECURSE Creator_AssetFile
	"${ENGINE_DIR}/app/panels/asset/*.h"
	"${ENGINE_DIR}/app/panels/asset/*.hpp"
	"${ENGINE_DIR}/app/panels/asset/*.c"
	"${ENGINE_DIR}/app/panels/asset/*.cpp")
	
add_library(Creator_Asset SHARED ${Creator_AssetFile})
source_group(TREE "${ENGINE_DIR}/app/panels/asset" FILES ${Creator_AssetFile})
set_target_properties(Creator_Asset PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_Asset PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Asset PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Asset PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Asset PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Asset PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Asset PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_Asset PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(Creator_Asset PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Creator_Asset PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(Creator_Asset PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_Asset PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_Asset PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_Asset PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_Asset PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_Asset PUBLIC "AppCore.lib")
target_link_libraries(Creator_Asset PUBLIC "Engine.lib")
target_link_libraries(Creator_Asset PUBLIC "Editor.lib")

set_target_properties(Creator_Asset PROPERTIES FOLDER Application/Panels)
