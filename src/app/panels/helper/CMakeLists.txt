file(GLOB_RECURSE Creator_HelperFile
	"${ENGINE_DIR}/app/panels/helper/*.h"
	"${ENGINE_DIR}/app/panels/helper/*.hpp"
	"${ENGINE_DIR}/app/panels/helper/*.c"
	"${ENGINE_DIR}/app/panels/helper/*.cpp")
	
add_library(Creator_Helper SHARED ${Creator_HelperFile})
source_group(TREE "${ENGINE_DIR}/app/panels/helper" FILES ${Creator_HelperFile})
set_target_properties(Creator_Helper PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_Helper PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Helper PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Helper PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Helper PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Helper PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Helper PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_Helper PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(Creator_Helper PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Creator_Helper PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(Creator_Helper PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_Helper PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_Helper PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_Helper PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_Helper PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_Helper PUBLIC "AppCore.lib")
target_link_libraries(Creator_Helper PUBLIC "Engine.lib")
target_link_libraries(Creator_Helper PUBLIC "Editor.lib")

set_target_properties(Creator_Helper PROPERTIES FOLDER Application/Panels)
