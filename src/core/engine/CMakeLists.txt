file(GLOB_RECURSE Engine_Files
	"${ENGINE_DIR}/core/engine/*.h"
	"${ENGINE_DIR}/core/engine/*.hpp"
	"${ENGINE_DIR}/core/engine/*.c"
	"${ENGINE_DIR}/core/engine/*.cpp")
add_library(Engine SHARED ${Engine_Files})
source_group(TREE "${ENGINE_DIR}/core/engine" FILES ${Engine_Files})
set_target_properties(Engine PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Engine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}")
set_target_properties(Engine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}")
target_compile_definitions(Engine PUBLIC TARA_API=DLLEXPORT)

target_include_directories(Engine PUBLIC "${Root}/lib/glfw/include")
target_include_directories(Engine PUBLIC "${Root}/lib/glad/include")
target_include_directories(Engine PUBLIC "${Root}/lib/glm")
target_include_directories(Engine PUBLIC "${Root}/lib/devil/include")
target_include_directories(Engine PUBLIC "${Root}/lib/stb")
target_include_directories(Engine PUBLIC "${Root}/lib/utility")
target_include_directories(Engine PUBLIC "${Root}/lib/backward-cpp")
target_include_directories(Engine PUBLIC "${Root}/lib/assimp/include")
target_include_directories(Engine PUBLIC "${Root}/lib/base64")
target_include_directories(Engine PUBLIC "${Root}/lib/json/include")
target_include_directories(Engine PUBLIC "${Root}/lib/libarchive/libarchive")
target_include_directories(Engine PUBLIC "${Root}/lib/uuid4")

target_link_directories(Engine PUBLIC "${Root}/lib/glfw/lib-vc2022")
target_link_directories(Engine PUBLIC "${Root}/lib/devil/lib/x64/Release")
target_link_directories(Engine PUBLIC "${Root}/lib/assimp/lib/Release")
target_link_directories(Engine PUBLIC "${Root}/lib/libarchive/libarchive/Release")

target_link_libraries(Engine PUBLIC "glfw3dll.lib")
target_link_libraries(Engine PUBLIC "DevIL.lib")
target_link_libraries(Engine PUBLIC "ILU.lib")
target_link_libraries(Engine PUBLIC "ILUT.lib")
target_link_libraries(Engine PUBLIC "assimp-vc142-mt.lib")
target_link_libraries(Engine PUBLIC "archive.lib")

set_target_properties(Engine PROPERTIES FOLDER Core)
