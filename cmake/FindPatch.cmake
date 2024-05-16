# .rst:
# FindPatch
# ----------
#
# Find patch executable.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``Patch_FOUND``
#
# ``Patch_EXECUTABLE``
#
# ``Patch_VERSION``
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)

if(CMAKE_HOST_WIN32)
  find_program(Patch_EXECUTABLE NAMES patch
    PATHS
      "$ENV{LOCALAPPDATA}/Programs/Git/bin"
      "$ENV{LOCALAPPDATA}/Programs/Git/usr/bin"
      "$ENV{APPDATA}/Programs/Git/bin"
      "$ENV{APPDATA}/Programs/Git/usr/bin"
  )
  mark_as_advanced(Patch_EXECUTABLE)
else()
  find_program(Patch_EXECUTABLE NAMES patch)
  mark_as_advanced(Patch_EXECUTABLE)
endif()

if(EXISTS "${Patch_EXECUTABLE}")
  execute_process(COMMAND ${Patch_EXECUTABLE} --version ERROR_QUIET OUTPUT_VARIABLE Patch_VERSION)
  string(REGEX REPLACE ".*patch ([^\n ]+).*" "\\1" Patch_VERSION "${Patch_VERSION}")
endif()

find_package_handle_standard_args(Patch
  FOUND_VAR
    Patch_FOUND
  REQUIRED_VARS
    Patch_EXECUTABLE
  VERSION_VAR
    Patch_VERSION
)
