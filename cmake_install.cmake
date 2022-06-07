# Install script for directory: C:/Users/chuel/source/repos/Tara

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Tara")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/chuel/source/repos/Tara/src/core/engine/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/core/editor/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/core/appcore/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/asset/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/code_editor/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/console/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/debug/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/export/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/explorer/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/framebuffer_view/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/helper/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/hierarchy/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/node/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/project_creation/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/property/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/scene/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/setting/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/panels/timeline/cmake_install.cmake")
  include("C:/Users/chuel/source/repos/Tara/src/app/creator/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/chuel/source/repos/Tara/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
