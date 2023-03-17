#.rst:
# FindTalloc
# ----------
#
# Find Talloc include dirs and libraries.
#
# Imported Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines the following :ref:`Imported Targets <Imported Targets>`:
#
# ``Talloc::talloc``
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``TALLOC_FOUND``
#
# ``TALLOC_INCLUDE_DIRS``
#
# ``TALLOC_LIBRARIES``
#
# ``TALLOC_VERSION``
#
# ``TALLOC_VERSION_MAJOR``
#
# ``TALLOC_VERSION_MINOR``
#
# Cache variables
# ^^^^^^^^^^^^^^^
#
# Search results are saved persistently in CMake cache entries:
#
# ``TALLOC_INCLUDE_DIR``
#
# ``TALLOC_LIBRARY``
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_package(PkgConfig QUIET)

if(PKG_CONFIG_FOUND)
  if(CMAKE_VERSION VERSION_GREATER 3.6)
    pkg_check_modules(talloc QUIET IMPORTED_TARGET talloc)
  else()
    pkg_check_modules(talloc QUIET talloc)
  endif()
  if(talloc_FOUND)
    if(talloc_VERSION)
      set(TALLOC_VERSION ${talloc_VERSION})
    endif()
  endif()
endif()

find_library(TALLOC_LIBRARY
  NAMES talloc NAMES_PER_DIR
  HINTS ${talloc_LIBRARY_DIRS}
)
mark_as_advanced(TALLOC_LIBRARY)
if(EXISTS "${TALLOC_LIBRARY}")
  list(APPEND TALLOC_LIBRARIES ${TALLOC_LIBRARY})
endif()

find_path(TALLOC_INCLUDE_DIR
  NAMES talloc.h
  HINTS ${talloc_INCLUDE_DIRS}
)
mark_as_advanced(TALLOC_INCLUDE_DIR)
if(EXISTS "${TALLOC_INCLUDE_DIR}")
  list(APPEND TALLOC_INCLUDE_DIRS ${TALLOC_INCLUDE_DIR})
endif()

if(NOT TALLOC_VERSION AND EXISTS "${TALLOC_INCLUDE_DIR}/talloc.h")
  file(STRINGS ${TALLOC_INCLUDE_DIR}/talloc.h text REGEX "TALLOC_VERSION")
  string(REGEX REPLACE ".*VERSION_MAJOR[^0-9]+([0-9]+).*" "\\1" TALLOC_VERSION_MAJOR ${text})
  string(REGEX REPLACE ".*VERSION_MINOR[^0-9]+([0-9]+).*" "\\1" TALLOC_VERSION_MINOR ${text})
  set(TALLOC_VERSION ${TALLOC_VERSION_MAJOR}.${TALLOC_VERSION_MINOR})
  set(text)
endif()

find_package_handle_standard_args(Talloc
  FOUND_VAR
    TALLOC_FOUND
  REQUIRED_VARS
    TALLOC_LIBRARY
    TALLOC_INCLUDE_DIR
  VERSION_VAR
    TALLOC_VERSION
)

if(TARGET PkgConfig::talloc)
  add_library(Talloc::talloc ALIAS PkgConfig::talloc)
endif()
if(NOT TARGET Talloc::talloc AND EXISTS "${TALLOC_LIBRARY}")
  add_library(Talloc::talloc UNKNOWN IMPORTED)
  set_target_properties(Talloc::talloc PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${TALLOC_INCLUDE_DIR}"
    IMPORTED_LOCATION "${TALLOC_LIBRARY}"
    IMPORTED_LINK_INTERFACE_LANGUAGES C
  )
endif()
