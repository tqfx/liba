#.rst:
# Findcppcheck
# ------------
#
# Find cppcheck executable.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``CPPCHECK_FOUND``
#
# ``CPPCHECK_EXECUTABLE``
#
# ``CPPCHECK_VERSION``
#
# Functions
# ^^^^^^^^^
#
# .. command:: add_cppcheck
#
#   ::
#
#     add_cppcheck([OPTIONS opt] [TARGETS tgt ...] [tgt ...])
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_program(CPPCHECK_EXECUTABLE NAMES cppcheck)
mark_as_advanced(CPPCHECK_EXECUTABLE)

if(EXISTS "${CPPCHECK_EXECUTABLE}")
  execute_process(COMMAND ${CPPCHECK_EXECUTABLE} --version OUTPUT_VARIABLE CPPCHECK_VERSION)
  string(REGEX REPLACE ".*check ([^\n ]+).*" "\\1" CPPCHECK_VERSION "${CPPCHECK_VERSION}")
endif()

find_package_handle_standard_args(cppcheck
  FOUND_VAR
    CPPCHECK_FOUND
  REQUIRED_VARS
    CPPCHECK_EXECUTABLE
  VERSION_VAR
    CPPCHECK_VERSION
)

if(CPPCHECK_FOUND)
  function(add_cppcheck)
    if(CMAKE_VERSION VERSION_LESS 3.10)
      return()
    endif()
    cmake_parse_arguments(CPPCHECK "" "" "TARGETS;OPTIONS" ${ARGN})
    list(APPEND CPPCHECK_TARGETS ${CPPCHECK_UNPARSED_ARGUMENTS})
    set_target_properties(${CPPCHECK_TARGETS} PROPERTIES C_CPPCHECK "${CPPCHECK_EXECUTABLE};${CPPCHECK_OPTIONS}")
    set_target_properties(${CPPCHECK_TARGETS} PROPERTIES CXX_CPPCHECK "${CPPCHECK_EXECUTABLE};${CPPCHECK_OPTIONS}")
  endfunction()
endif()
