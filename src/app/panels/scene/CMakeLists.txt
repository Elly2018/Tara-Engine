file(GLOB_RECURSE Creator_SceneFile
	"${ENGINE_DIR}/app/panels/scene/*.h"
	"${ENGINE_DIR}/app/panels/scene/*.hpp"
	"${ENGINE_DIR}/app/panels/scene/*.c"
	"${ENGINE_DIR}/app/panels/scene/*.cpp")
	
add_library(Creator_Scene SHARED ${Creator_SceneFile})
source_group(TREE "${ENGINE_DIR}/app/panels/scene" FILES ${Creator_SceneFile})
set_target_properties(Creator_Scene PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_Scene PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Scene PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Scene PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_Scene PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Scene PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_Scene PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_Scene PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(Creator_Scene PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Creator_Scene PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(Creator_Scene PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_Scene PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_Scene PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_Scene PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_Scene PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_Scene PUBLIC "AppCore.lib")
target_link_libraries(Creator_Scene PUBLIC "Engine.lib")
target_link_libraries(Creator_Scene PUBLIC "Editor.lib")

set_target_properties(Creator_Scene PROPERTIES FOLDER Application/Panels)
