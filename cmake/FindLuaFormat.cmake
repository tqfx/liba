#.rst:
# FindLuaFormat
# -------------
#
# Find lua-format executable.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``LUA_FORMAT_FOUND``, ``LuaFormat_FOUND``
#
# ``LUA_FORMAT_EXECUTABLE``
#
# Functions
# ^^^^^^^^^
#
# .. command:: add_lua_format
#
#   ::
#
#     add_lua_format(target [VERBOSE]
#         [WORKING_DIRECTORY dir] [COMMENT comment] [CONFIG cfg]
#         [OPTIONS opt ...] [SOURCES src ...] [src ...]
#     )
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_program(LUA_FORMAT_EXECUTABLE NAMES lua-format)
mark_as_advanced(LUA_FORMAT_EXECUTABLE)

find_package_handle_standard_args(LuaFormat
  FOUND_VAR
    LuaFormat_FOUND
  REQUIRED_VARS
    LUA_FORMAT_EXECUTABLE
)

if(LuaFormat_FOUND)
  set(LUA_FORMAT_FOUND 1)
  function(add_lua_format target)
    cmake_parse_arguments(LUA_FORMAT "VERBOSE" "WORKING_DIRECTORY;COMMENT;CONFIG" "OPTIONS;SOURCES" ${ARGN})
    list(APPEND LUA_FORMAT_SOURCES ${LUA_FORMAT_UNPARSED_ARGUMENTS})
    list(APPEND LUA_FORMAT_OPTIONS --in-place)
    if(LUA_FORMAT_VERBOSE)
      list(INSERT LUA_FORMAT_OPTIONS 0 --verbose)
    endif()
    if(EXISTS "${LUA_FORMAT_CONFIG}")
      list(APPEND LUA_FORMAT_OPTIONS --config=${LUA_FORMAT_CONFIG})
    endif()
    if(NOT LUA_FORMAT_WORKING_DIRECTORY)
      set(LUA_FORMAT_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
    if(NOT LUA_FORMAT_COMMENT)
      set(LUA_FORMAT_COMMENT "Formatting ${target} using lua-format")
    endif()
    add_custom_target(${target} # https://github.com/Koihik/LuaFormatter
      ${LUA_FORMAT_EXECUTABLE} ${LUA_FORMAT_OPTIONS} -- ${LUA_FORMAT_SOURCES}
      WORKING_DIRECTORY ${LUA_FORMAT_WORKING_DIRECTORY}
      COMMENT "${LUA_FORMAT_COMMENT}"
    )
  endfunction()
endif()
