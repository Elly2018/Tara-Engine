file(GLOB_RECURSE Creator_PropertyFile
	"${ENGINE_DIR}/app/panels/property/*.h"
	"${ENGINE_DIR}/app/panels/property/*.hpp"
	"${ENGINE_DIR}/app/panels/property/*.c"
	"${ENGINE_DIR}/app/panels/property/*.cpp")
	
add_library(Creator_Property SHARED ${Creator_PropertyFile})
source_group(TREE "${ENGINE_DIR}/app/panels/property" FILES ${Creator_PropertyFile})
set_target_properties(Creator_Property PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_Property PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Property PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Property PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Property PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Property PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Property PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_Property PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(Creator_Property PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Creator_Property PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(Creator_Property PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_Property PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_Property PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_Property PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_Property PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_Property PUBLIC "AppCore.lib")
target_link_libraries(Creator_Property PUBLIC "Engine.lib")
target_link_libraries(Creator_Property PUBLIC "Editor.lib")

set_target_properties(Creator_Property PROPERTIES FOLDER Application/Panels)
