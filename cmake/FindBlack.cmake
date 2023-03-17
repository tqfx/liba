#.rst:
# FindBlack
# ---------
#
# Find black executable.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``BLACK_FOUND``
#
# ``BLACK_EXECUTABLE``
#
# ``BLACK_VERSION``
#
# Functions
# ^^^^^^^^^
#
# .. command:: add_black
#
#   ::
#
#     add_black(target [QUIET] [VERBOSE]
#         [WORKING_DIRECTORY dir] [COMMENT comment]
#         [OPTIONS opt ...] [SOURCES src ...] [src ...]
#     )
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)

if(EXISTS "${Python_EXECUTABLE}")
  execute_process(COMMAND ${Python_EXECUTABLE} -c "import black; print(black.__version__)"
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE BLACK_VERSION
  )
endif()

if(BLACK_VERSION)
  set(BLACK_EXECUTABLE ${Python_EXECUTABLE} -m black)
else()
  find_program(BLACK_EXECUTABLE NAMES black)
  mark_as_advanced(BLACK_EXECUTABLE)
  set(BLACK_VERSION)
endif()

if(NOT BLACK_VERSION AND EXISTS "${BLACK_EXECUTABLE}")
  execute_process(COMMAND ${BLACK_EXECUTABLE} --version ERROR_QUIET OUTPUT_VARIABLE BLACK_VERSION)
  string(REGEX REPLACE "black[^0-9]+([^ ]+).*" "\\1" BLACK_VERSION "${BLACK_VERSION}")
endif()

find_package_handle_standard_args(Black
  FOUND_VAR
    BLACK_FOUND
  REQUIRED_VARS
    BLACK_EXECUTABLE
  VERSION_VAR
    BLACK_VERSION
)

if(BLACK_FOUND)
  function(add_black target)
    cmake_parse_arguments(BLACK "QUIET;VERBOSE" "WORKING_DIRECTORY;COMMENT" "OPTIONS;SOURCES" ${ARGN})
    list(APPEND BLACK_SOURCES ${BLACK_UNPARSED_ARGUMENTS})
    if(BLACK_QUIET)
      list(INSERT BLACK_OPTIONS 0 --quiet)
    endif()
    if(BLACK_VERBOSE)
      list(INSERT BLACK_OPTIONS 0 --verbose)
    endif()
    if(NOT BLACK_WORKING_DIRECTORY)
      set(BLACK_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
    if(NOT BLACK_COMMENT)
      set(BLACK_COMMENT "Formatting ${target} using black")
    endif()
    add_custom_target(${target} # https://black.readthedocs.io/en/stable
      ${BLACK_EXECUTABLE} ${BLACK_OPTIONS} ${BLACK_SOURCES}
      WORKING_DIRECTORY ${BLACK_WORKING_DIRECTORY}
      COMMENT "${BLACK_COMMENT}"
    )
  endfunction()
endif()
