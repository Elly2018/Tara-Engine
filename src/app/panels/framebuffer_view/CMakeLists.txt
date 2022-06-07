file(GLOB_RECURSE Creator_FramebufferViewFile
	"${ENGINE_DIR}/app/panels/framebuffer_view/*.h"
	"${ENGINE_DIR}/app/panels/framebuffer_view/*.hpp"
	"${ENGINE_DIR}/app/panels/framebuffer_view/*.c"
	"${ENGINE_DIR}/app/panels/framebuffer_view/*.cpp")
	
add_library(Creator_FramebufferView SHARED ${Creator_FramebufferViewFile})
source_group(TREE "${ENGINE_DIR}/app/panels/framebuffer_view" FILES ${Creator_FramebufferViewFile})
set_target_properties(Creator_FramebufferView PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Creator_FramebufferView PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_FramebufferView PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_FramebufferView PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Creator_FramebufferView PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_FramebufferView PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Creator_FramebufferView PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Creator_FramebufferView PUBLIC TARA_APP_API=DLLEXPORT)
target_compile_definitions(Creator_FramebufferView PUBLIC TARA_API=DLLIMPORT)
target_compile_definitions(Creator_FramebufferView PUBLIC TARA_EDITOR_API=DLLIMPORT)

target_include_directories(Creator_FramebufferView PUBLIC "${ENGINE_DIR}/core")
target_include_directories(Creator_FramebufferView PUBLIC "${Root}/lib/glm")
target_include_directories(Creator_FramebufferView PUBLIC "${Root}/lib/json/include")
target_include_directories(Creator_FramebufferView PUBLIC "${Root}/lib/uuid4")

target_link_directories(Creator_FramebufferView PUBLIC "${BIN_DIR}")

target_link_libraries(Creator_FramebufferView PUBLIC "AppCore.lib")
target_link_libraries(Creator_FramebufferView PUBLIC "Engine.lib")
target_link_libraries(Creator_FramebufferView PUBLIC "Editor.lib")

set_target_properties(Creator_FramebufferView PROPERTIES FOLDER Application/Panels)
