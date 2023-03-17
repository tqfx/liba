#.rst:
# FindStyLua
# ----------
#
# Find stylua executable.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``STYLUA_FOUND``
#
# ``STYLUA_EXECUTABLE``
#
# ``STYLUA_VERSION``
#
# Functions
# ^^^^^^^^^
#
# .. command:: add_stylua
#
#   ::
#
#     add_stylua(target [VERBOSE]
#         [WORKING_DIRECTORY dir] [COMMENT comment] [CONFIG cfg]
#         [OPTIONS opt ...] [SOURCES src ...] [src ...]
#     )
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_program(STYLUA_EXECUTABLE NAMES stylua)
mark_as_advanced(STYLUA_EXECUTABLE)

if(EXISTS "${STYLUA_EXECUTABLE}")
  execute_process(COMMAND ${STYLUA_EXECUTABLE} --version OUTPUT_VARIABLE STYLUA_VERSION)
  string(REGEX REPLACE "stylua ([^\n ]+).*" "\\1" STYLUA_VERSION "${STYLUA_VERSION}")
endif()

find_package_handle_standard_args(StyLua
  FOUND_VAR
    STYLUA_FOUND
  REQUIRED_VARS
    STYLUA_EXECUTABLE
  VERSION_VAR
    STYLUA_VERSION
)

if(STYLUA_FOUND)
  function(add_stylua target)
    cmake_parse_arguments(STYLUA "VERBOSE" "WORKING_DIRECTORY;COMMENT;CONFIG" "OPTIONS;SOURCES" ${ARGN})
    list(APPEND STYLUA_SOURCES ${STYLUA_UNPARSED_ARGUMENTS})
    if(STYLUA_VERBOSE)
      list(INSERT STYLUA_OPTIONS 0 --verbose)
    endif()
    if(EXISTS "${STYLUA_CONFIG}")
      list(APPEND STYLUA_OPTIONS --config-path ${STYLUA_CONFIG})
    endif()
    if(NOT STYLUA_WORKING_DIRECTORY)
      set(STYLUA_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
    if(NOT STYLUA_COMMENT)
      set(STYLUA_COMMENT "Formatting ${target} using stylua")
    endif()
    add_custom_target(${target} # https://github.com/JohnnyMorganz/StyLua
      ${STYLUA_EXECUTABLE} ${STYLUA_OPTIONS} -- ${STYLUA_SOURCES}
      WORKING_DIRECTORY ${STYLUA_WORKING_DIRECTORY}
      COMMENT "${STYLUA_COMMENT}"
    )
  endfunction()
endif()
