file(GLOB_RECURSE Creator_ConsoleFile
	"${ENGINE_DIR}/app/panels/console/*.h"
	"${ENGINE_DIR}/app/panels/console/*.hpp"
	"${ENGINE_DIR}/app/panels/console/*.c"
	"${ENGINE_DIR}/app/panels/console/*.cpp")
	
add_library(Creator_Console SHARED ${Creator_ConsoleFile})
source_group(TREE "${ENGINE_DIR}/app/panels/console" FILES ${Creator_ConsoleFile})
set_target_properties(Creator_Console PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_Console PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Console PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Console PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Console PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Console PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Console PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_Console PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(Creator_Console PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Creator_Console PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(Creator_Console PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_Console PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_Console PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_Console PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_Console PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_Console PUBLIC "AppCore.lib")
target_link_libraries(Creator_Console PUBLIC "Engine.lib")
target_link_libraries(Creator_Console PUBLIC "Editor.lib")

set_target_properties(Creator_Console PROPERTIES FOLDER Application/Panels)
