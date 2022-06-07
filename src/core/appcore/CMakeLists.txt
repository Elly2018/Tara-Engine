file(GLOB_RECURSE AppCoreFile
	"${ENGINE_DIR}/core/appcore/*.h"
	"${ENGINE_DIR}/core/appcore/*.hpp"
	"${ENGINE_DIR}/core/appcore/*.c"
	"${ENGINE_DIR}/core/appcore/*.cpp")
	
add_library(AppCore SHARED ${AppCoreFile})
source_group(TREE "${ENGINE_DIR}/core/appcore" FILES ${AppCoreFile})
set_target_properties(AppCore PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(AppCore PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(AppCore PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(AppCore PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(AppCore PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(AppCore PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(AppCore PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(AppCore PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(AppCore PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(AppCore PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(AppCore PUBLIC "${ENGINE_DIR}/core")
target_include_directories(AppCore PUBLIC "${Root}/lib/glm")
target_include_directories(AppCore PUBLIC "${Root}/lib/json/include")
target_include_directories(AppCore PUBLIC "${Root}/lib/uuid4")

target_link_directories(AppCore PUBLIC "${BIN_DIR}")

target_link_libraries(AppCore PUBLIC "Engine.lib")
target_link_libraries(AppCore PUBLIC "Editor.lib")

set_target_properties(AppCore PROPERTIES FOLDER Core)
