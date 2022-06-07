file(GLOB_RECURSE Creator_SettingFile
	"${ENGINE_DIR}/app/panels/setting/*.h"
	"${ENGINE_DIR}/app/panels/setting/*.hpp"
	"${ENGINE_DIR}/app/panels/setting/*.c"
	"${ENGINE_DIR}/app/panels/setting/*.cpp")
	
add_library(Creator_Setting SHARED ${Creator_SettingFile})
source_group(TREE "${ENGINE_DIR}/app/panels/setting" FILES ${Creator_SettingFile})
set_target_properties(Creator_Setting PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_Setting PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Setting PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Setting PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Setting PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Setting PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Setting PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_Setting PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(Creator_Setting PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Creator_Setting PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(Creator_Setting PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_Setting PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_Setting PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_Setting PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_Setting PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_Setting PUBLIC "AppCore.lib")
target_link_libraries(Creator_Setting PUBLIC "Engine.lib")
target_link_libraries(Creator_Setting PUBLIC "Editor.lib")

set_target_properties(Creator_Setting PROPERTIES FOLDER Application/Panels)
