#.rst:
# FindCCache
# ----------
#
# Find ccache executable. https://ccache.dev/manual/latest.html
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``CCACHE_FOUND``
#
# ``CCACHE_EXECUTABLE``
#
# ``CCACHE_VERSION``
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_program(CCACHE_EXECUTABLE ccache)
mark_as_advanced(CCACHE_EXECUTABLE)

if(EXISTS "${CCACHE_EXECUTABLE}")
  execute_process(COMMAND ${CCACHE_EXECUTABLE} --version OUTPUT_VARIABLE CCACHE_VERSION)
  string(REGEX REPLACE "ccache version ([^\n ]+).*" "\\1" CCACHE_VERSION "${CCACHE_VERSION}")
endif()

find_package_handle_standard_args(CCache
  FOUND_VAR
    CCACHE_FOUND
  REQUIRED_VARS
    CCACHE_EXECUTABLE
  VERSION_VAR
    CCACHE_VERSION
)
