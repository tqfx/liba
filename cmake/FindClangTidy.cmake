#.rst:
# FindClangTidy
# -------------
#
# Find clang-tidy executable.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``CLANG_TIDY_FOUND``, ``ClangTidy_FOUND``
#
# ``CLANG_TIDY_EXECUTABLE``
#
# ``CLANG_TIDY_VERSION``
#
# Functions
# ^^^^^^^^^
#
# .. command:: add_clang_tidy
#
#   ::
#
#     add_clang_tidy([OPTIONS opt] [TARGETS tgt ...] [tgt ...])
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
mark_as_advanced(CLANG_TIDY_EXECUTABLE)

if(EXISTS "${CLANG_TIDY_EXECUTABLE}")
  execute_process(COMMAND ${CLANG_TIDY_EXECUTABLE} --version OUTPUT_VARIABLE CLANG_TIDY_VERSION)
  string(REGEX REPLACE ".*version ([^\n ]+).*" "\\1" CLANG_TIDY_VERSION "${CLANG_TIDY_VERSION}")
endif()

find_package_handle_standard_args(ClangTidy
  FOUND_VAR
    ClangTidy_FOUND
  REQUIRED_VARS
    CLANG_TIDY_EXECUTABLE
  VERSION_VAR
    CLANG_TIDY_VERSION
)

if(ClangTidy_FOUND)
  set(CLANG_TIDY_FOUND 1)
  function(add_clang_tidy)
    if(CMAKE_VERSION VERSION_LESS 3.6)
      return()
    endif()
    cmake_parse_arguments(CLANG_TIDY "" "" "TARGETS;OPTIONS" ${ARGN})
    list(APPEND CLANG_TIDY_TARGETS ${CLANG_TIDY_UNPARSED_ARGUMENTS})
    get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)
    foreach(lang ${ENABLED_LANGUAGES})
      set_target_properties(${CLANG_TIDY_TARGETS} PROPERTIES ${lang}_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE};${CLANG_TIDY_OPTIONS}")
    endforeach()
  endfunction()
endif()
