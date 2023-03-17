#.rst:
# FindIWYU
# --------
#
# Find include-what-you-use executable.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``IWYU_FOUND``
#
# ``IWYU_EXECUTABLE``
#
# ``IWYU_VERSION``
#
# Functions
# ^^^^^^^^^
#
# .. command:: add_include_what_you_use
#
#   ::
#
#     add_include_what_you_use([OPTIONS opt] [TARGETS tgt ...] [tgt ...])
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_program(IWYU_EXECUTABLE NAMES include-what-you-use)
mark_as_advanced(IWYU_EXECUTABLE)

if(EXISTS "${IWYU_EXECUTABLE}")
  execute_process(COMMAND ${IWYU_EXECUTABLE} --version OUTPUT_VARIABLE IWYU_VERSION)
  string(REGEX REPLACE ".*use ([^ ]+).*" "\\1" IWYU_VERSION "${IWYU_VERSION}")
endif()

find_package_handle_standard_args(IWYU
  FOUND_VAR
    IWYU_FOUND
  REQUIRED_VARS
    IWYU_EXECUTABLE
  VERSION_VAR
    IWYU_VERSION
)

if(IWYU_FOUND)
  function(add_include_what_you_use)
    if(CMAKE_VERSION VERSION_LESS 3.3)
      return()
    endif()
    cmake_parse_arguments(IWYU "" "" "TARGETS;OPTIONS" ${ARGN})
    list(APPEND IWYU_TARGETS ${IWYU_UNPARSED_ARGUMENTS})
    set_target_properties(${IWYU_TARGETS} PROPERTIES C_INCLUDE_WHAT_YOU_USE "${IWYU_EXECUTABLE};${IWYU_OPTIONS}")
    set_target_properties(${IWYU_TARGETS} PROPERTIES CXX_INCLUDE_WHAT_YOU_USE "${IWYU_EXECUTABLE};${IWYU_OPTIONS}")
  endfunction()
endif()
