#.rst:
# FindLDoc
# --------
#
# Find ldoc executable.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``LDOC_FOUND``
#
# ``LDOC_EXECUTABLE``
#
# ``LDOC_VERSION``
#
# Functions
# ^^^^^^^^^
#
# .. command:: create_ldoc
#
#   ::
#
#     create_ldoc(target [QUIET] [VERBOSE]
#         [WORKING_DIRECTORY dir] [COMMENT comment] [CONFIG cfg]
#         [OPTIONS opt ...] [SOURCES src ...] [src ...]
#     )
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_program(LDOC_EXECUTABLE NAMES ldoc)
mark_as_advanced(LDOC_EXECUTABLE)

if(EXISTS "${LDOC_EXECUTABLE}")
  execute_process(COMMAND ${LDOC_EXECUTABLE} ERROR_VARIABLE LDOC_VERSION)
  string(REGEX REPLACE ".*vs ([^\n ]+).*" "\\1" LDOC_VERSION "${LDOC_VERSION}")
endif()

find_package_handle_standard_args(LDoc
  FOUND_VAR
    LDOC_FOUND
  REQUIRED_VARS
    LDOC_EXECUTABLE
  VERSION_VAR
    LDOC_VERSION
)

if(LDOC_FOUND)
  function(create_ldoc target)
    cmake_parse_arguments(LDOC "QUIET;VERBOSE" "WORKING_DIRECTORY;COMMENT;CONFIG" "OPTIONS;SOURCES" ${ARGN})
    list(APPEND LDOC_SOURCES ${LDOC_UNPARSED_ARGUMENTS})
    if(LDOC_QUIET)
      list(INSERT LDOC_OPTIONS 0 --quiet)
    endif()
    if(LDOC_VERBOSE)
      list(INSERT LDOC_OPTIONS 0 --verbose)
    endif()
    if(EXISTS "${LDOC_CONFIG}")
      list(APPEND LDOC_OPTIONS -c ${LDOC_CONFIG})
    endif()
    if(NOT LDOC_WORKING_DIRECTORY)
      set(LDOC_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()
    if(NOT LDOC_COMMENT)
      set(LDOC_COMMENT "Generate API documentation for ${target}")
    endif()
    add_custom_target(${target} # https://stevedonovan.github.io/ldoc/manual/doc.md.html
      COMMAND ${LDOC_EXECUTABLE} ${LDOC_OPTIONS} ${LDOC_SOURCES}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "${LDOC_COMMENT}"
    )
  endfunction()
endif()
