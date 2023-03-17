#.rst:
# FindClangFormat
# ---------------
#
# Find clang-format executable.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``CLANG_FORMAT_FOUND``, ``ClangFormat_FOUND``
#
# ``CLANG_FORMAT_EXECUTABLE``
#
# ``CLANG_FORMAT_VERSION``
#
# Functions
# ^^^^^^^^^
#
# .. command:: add_clang_format
#
#   ::
#
#     add_clang_format(target [VERBOSE]
#         [WORKING_DIRECTORY dir] [COMMENT comment]
#         [OPTIONS opt ...] [SOURCES src ...] [src ...]
#     )
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
mark_as_advanced(CLANG_FORMAT_EXECUTABLE)

if(EXISTS "${CLANG_FORMAT_EXECUTABLE}")
  execute_process(COMMAND ${CLANG_FORMAT_EXECUTABLE} --version OUTPUT_VARIABLE CLANG_FORMAT_VERSION)
  string(REGEX REPLACE ".*version ([^\n ]+).*" "\\1" CLANG_FORMAT_VERSION "${CLANG_FORMAT_VERSION}")
endif()

find_package_handle_standard_args(ClangFormat
  FOUND_VAR
    ClangFormat_FOUND
  REQUIRED_VARS
    CLANG_FORMAT_EXECUTABLE
  VERSION_VAR
    CLANG_FORMAT_VERSION
)

if(ClangFormat_FOUND)
  set(CLANG_FORMAT_FOUND 1)
  function(add_clang_format target)
    cmake_parse_arguments(CLANG_FORMAT "VERBOSE" "WORKING_DIRECTORY;COMMENT" "SOURCES" ${ARGN})
    list(APPEND CLANG_FORMAT_SOURCES ${CLANG_FORMAT_UNPARSED_ARGUMENTS})
    list(APPEND CLANG_FORMAT_OPTIONS --style=file -i)
    if(CLANG_FORMAT_VERBOSE)
      list(INSERT CLANG_FORMAT_OPTIONS 0 --verbose)
    endif()
    if(NOT CLANG_FORMAT_WORKING_DIRECTORY)
      set(CLANG_FORMAT_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
    if(NOT CLANG_FORMAT_COMMENT)
      set(CLANG_FORMAT_COMMENT "Formatting ${target} using clang-format")
    endif()
    add_custom_target(${target} # https://clang.llvm.org/docs/ClangFormat.html
      ${CLANG_FORMAT_EXECUTABLE} ${CLANG_FORMAT_OPTIONS} ${CLANG_FORMAT_SOURCES}
      WORKING_DIRECTORY ${CLANG_FORMAT_WORKING_DIRECTORY}
      COMMENT "${CLANG_FORMAT_COMMENT}"
    )
  endfunction()
endif()
