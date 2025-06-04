# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/stats-src"
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/stats-build"
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/stats-subbuild/stats-populate-prefix"
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/stats-subbuild/stats-populate-prefix/tmp"
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/stats-subbuild/stats-populate-prefix/src/stats-populate-stamp"
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/stats-subbuild/stats-populate-prefix/src"
  "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/stats-subbuild/stats-populate-prefix/src/stats-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/stats-subbuild/stats-populate-prefix/src/stats-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/mads/Devel/questionnaire_gform/Plugin/build/_deps/stats-subbuild/stats-populate-prefix/src/stats-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
