#.rst:
# FindZig
# -------
#
# Find zig executable.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``ZIG_FOUND``
#
# ``ZIG_EXECUTABLE``
#
# ``ZIG_VERSION``
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_program(ZIG_EXECUTABLE zig DOC "Zig compiler")
mark_as_advanced(ZIG_EXECUTABLE)

if(EXISTS "${ZIG_EXECUTABLE}")
  execute_process(COMMAND ${ZIG_EXECUTABLE} version
    OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE ZIG_VERSION
  )
endif()

find_package_handle_standard_args(Zig
  FOUND_VAR
    ZIG_FOUND
  REQUIRED_VARS
    ZIG_EXECUTABLE
  VERSION_VAR
    ZIG_VERSION
)
