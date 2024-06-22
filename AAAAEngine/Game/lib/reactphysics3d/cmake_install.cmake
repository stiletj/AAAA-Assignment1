# Install script for directory: C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/lib/reactphysics3d

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/AAAGameEngine")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/build/lib/reactphysics3d/Debug/reactphysics3d.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/build/lib/reactphysics3d/Release/reactphysics3d.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/build/lib/reactphysics3d/MinSizeRel/reactphysics3d.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/build/lib/reactphysics3d/RelWithDebInfo/reactphysics3d.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/lib/reactphysics3d/include/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ReactPhysics3D/ReactPhysics3DConfig.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ReactPhysics3D/ReactPhysics3DConfig.cmake"
         "C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/build/lib/reactphysics3d/CMakeFiles/Export/169343ac99728a0b59f4954842cb6dc9/ReactPhysics3DConfig.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ReactPhysics3D/ReactPhysics3DConfig-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ReactPhysics3D/ReactPhysics3DConfig.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ReactPhysics3D" TYPE FILE FILES "C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/build/lib/reactphysics3d/CMakeFiles/Export/169343ac99728a0b59f4954842cb6dc9/ReactPhysics3DConfig.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ReactPhysics3D" TYPE FILE FILES "C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/build/lib/reactphysics3d/CMakeFiles/Export/169343ac99728a0b59f4954842cb6dc9/ReactPhysics3DConfig-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ReactPhysics3D" TYPE FILE FILES "C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/build/lib/reactphysics3d/CMakeFiles/Export/169343ac99728a0b59f4954842cb6dc9/ReactPhysics3DConfig-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ReactPhysics3D" TYPE FILE FILES "C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/build/lib/reactphysics3d/CMakeFiles/Export/169343ac99728a0b59f4954842cb6dc9/ReactPhysics3DConfig-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ReactPhysics3D" TYPE FILE FILES "C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/build/lib/reactphysics3d/CMakeFiles/Export/169343ac99728a0b59f4954842cb6dc9/ReactPhysics3DConfig-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ReactPhysics3D" TYPE FILE FILES "C:/Users/tjsti/GitHub/AAAAEngine/AAAAGameEngine2/AAAAGameEngine2/build/lib/reactphysics3d/ReactPhysics3DConfigVersion.cmake")
endif()

