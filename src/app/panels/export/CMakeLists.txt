file(GLOB_RECURSE Creator_ExportFile
	"${ENGINE_DIR}/app/panels/export/*.h"
	"${ENGINE_DIR}/app/panels/export/*.hpp"
	"${ENGINE_DIR}/app/panels/export/*.c"
	"${ENGINE_DIR}/app/panels/export/*.cpp")
	
add_library(Creator_Export SHARED ${Creator_ExportFile})
source_group(TREE "${ENGINE_DIR}/app/panels/export" FILES ${Creator_ExportFile})
set_target_properties(Creator_Export PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_Export PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Export PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Export PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Export PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Export PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Export PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_Export PUBLIC TARA_API=DLLEXPORT)
target_compile_definitions(Creator_Export PUBLIC TARA_EDITOR_API=DLLEXPORT)

target_include_directories(Creator_Export PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_Export PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_Export PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_Export PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_Export PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_Export PUBLIC "AppCore.lib")
target_link_libraries(Creator_Export PUBLIC "Engine.lib")
target_link_libraries(Creator_Export PUBLIC "Editor.lib")

set_target_properties(Creator_Export PROPERTIES FOLDER Application/Panels)
