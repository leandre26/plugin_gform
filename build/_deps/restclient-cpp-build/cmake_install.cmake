# Install script for directory: /home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/plugin-src/usr")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-build/librestclient-cpp.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/restclient-cpp" TYPE FILE FILES
    "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-src/include/restclient-cpp/restclient.h"
    "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-build/include/restclient-cpp/version.h"
    "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-src/include/restclient-cpp/connection.h"
    "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-src/include/restclient-cpp/helpers.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/restclient-cpp/restclient-cppTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/restclient-cpp/restclient-cppTargets.cmake"
         "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-build/CMakeFiles/Export/127558578dee9f463383649fc1fad666/restclient-cppTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/restclient-cpp/restclient-cppTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/restclient-cpp/restclient-cppTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/restclient-cpp" TYPE FILE FILES "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-build/CMakeFiles/Export/127558578dee9f463383649fc1fad666/restclient-cppTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/restclient-cpp" TYPE FILE FILES "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-build/CMakeFiles/Export/127558578dee9f463383649fc1fad666/restclient-cppTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/cmake/restclient-cpp/restclient-cppConfig.cmake;/usr/local/lib/cmake/restclient-cpp/restclient-cppConfigVersion.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/lib/cmake/restclient-cpp" TYPE FILE FILES
    "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-build/restclient-cppConfig.cmake"
    "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-build/restclient-cppConfigVersion.cmake"
    )
endif()

