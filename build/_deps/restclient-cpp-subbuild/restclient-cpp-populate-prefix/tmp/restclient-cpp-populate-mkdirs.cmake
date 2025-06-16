# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-src"
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-build"
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-subbuild/restclient-cpp-populate-prefix"
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-subbuild/restclient-cpp-populate-prefix/tmp"
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-subbuild/restclient-cpp-populate-prefix/src/restclient-cpp-populate-stamp"
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-subbuild/restclient-cpp-populate-prefix/src"
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-subbuild/restclient-cpp-populate-prefix/src/restclient-cpp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-subbuild/restclient-cpp-populate-prefix/src/restclient-cpp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/restclient-cpp-subbuild/restclient-cpp-populate-prefix/src/restclient-cpp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
