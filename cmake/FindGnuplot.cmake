# .rst:
# FindGnuplot
# -----------
#
# Find gnuplot executable. http://www.gnuplot.info
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``GNUPLOT_FOUND``
#
# ``GNUPLOT_EXECUTABLE``
#
# ``GNUPLOT_VERSION``
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_program(GNUPLOT_EXECUTABLE NAMES gnuplot pgnuplot wgnupl32)
mark_as_advanced(GNUPLOT_EXECUTABLE)

if(EXISTS "${GNUPLOT_EXECUTABLE}")
  execute_process(COMMAND ${GNUPLOT_EXECUTABLE} --version OUTPUT_VARIABLE GNUPLOT_VERSION)
  string(REGEX REPLACE "[^0-9]+([^\n ]+).*" "\\1" GNUPLOT_VERSION "${GNUPLOT_VERSION}")
endif()

find_package_handle_standard_args(Gnuplot
  FOUND_VAR
    GNUPLOT_FOUND
  REQUIRED_VARS
    GNUPLOT_EXECUTABLE
  VERSION_VAR
    GNUPLOT_VERSION
)
