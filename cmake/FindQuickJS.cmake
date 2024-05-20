# .rst:
# FindQuickJS
# -----------
#
# Find quickjs include dirs and libraries.
#
# Imported Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines the following :ref:`Imported Targets <Imported Targets>`:
#
# ``quickjs``
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``QUICKJS_FOUND``
#
# ``QUICKJS_INCLUDE_DIR``
#
# ``QUICKJS_LIBRARIES``
#
# ``QUICKJS_VERSION``
#
# ``QJSC_EXECUTABLE``
#
# ``QJS_EXECUTABLE``
#
# Cache variables
# ^^^^^^^^^^^^^^^
#
# Search results are saved persistently in CMake cache entries:
#
# ``QUICKJS_INCLUDE_DIR``
#
# ``QUICKJS_LTO_LIBRARY``
#
# ``QUICKJS_LIBRARY``
#
# ``QJSC_EXECUTABLE``
#
# ``QJS_EXECUTABLE``
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_path(QUICKJS_INCLUDE_DIR NAMES quickjs.h PATH_SUFFIXES quickjs)
mark_as_advanced(QUICKJS_INCLUDE_DIR)

find_program(QJSC_EXECUTABLE NAMES qjsc)
mark_as_advanced(QJSC_EXECUTABLE)

find_program(QJS_EXECUTABLE NAMES qjs)
mark_as_advanced(QJS_EXECUTABLE)

if(EXISTS "${QJS_EXECUTABLE}")
  execute_process(COMMAND ${QJS_EXECUTABLE} -h OUTPUT_VARIABLE QUICKJS_VERSION)
elseif(EXISTS "${QJSC_EXECUTABLE}")
  execute_process(COMMAND ${QJSC_EXECUTABLE} -h OUTPUT_VARIABLE QUICKJS_VERSION)
endif()
if(QUICKJS_VERSION)
  string(REGEX REPLACE ".*version[ ]+([^\n ]+).*" "\\1" QUICKJS_VERSION "${QUICKJS_VERSION}")
endif()

find_library(QUICKJS_LTO_LIBRARY NAMES quickjs.lto PATH_SUFFIXES quickjs)
find_library(QUICKJS_LIBRARY NAMES quickjs PATH_SUFFIXES quickjs)
mark_as_advanced(QUICKJS_LTO_LIBRARY QUICKJS_LIBRARY)

set(QUICKJS_LIBRARY2)
get_filename_component(ext "${QUICKJS_LIBRARY}" EXT)
if(NOT APPLE AND UNIX)
  find_library(QUICKJS_MATH_LIBRARY m)
  mark_as_advanced(QUICKJS_MATH_LIBRARY)
  if(EXISTS "${QUICKJS_MATH_LIBRARY}")
    list(APPEND QUICKJS_LIBRARY2 ${QUICKJS_MATH_LIBRARY})
  else()
    list(APPEND QUICKJS_LIBRARY2 m)
  endif()
  if(ext STREQUAL CMAKE_STATIC_LIBRARY_SUFFIX)
    list(APPEND QUICKJS_LIBRARY2 ${CMAKE_DL_LIBS})
  endif()
endif()
if(ext STREQUAL CMAKE_STATIC_LIBRARY_SUFFIX)
  find_package(Threads)
  if(CMAKE_USE_PTHREADS_INIT)
    list(APPEND QUICKJS_LIBRARY2 pthread)
  endif()
endif()

if(EXISTS "${QUICKJS_LIBRARY}")
  set(QUICKJS_LIBRARIES
    ${QUICKJS_LIBRARY} ${QUICKJS_LIBRARY2}
  )
endif()

find_package_handle_standard_args(QuickJS
  FOUND_VAR
    QUICKJS_FOUND
  REQUIRED_VARS
    QUICKJS_LIBRARIES
    QUICKJS_INCLUDE_DIR
    QJSC_EXECUTABLE
    QJS_EXECUTABLE
  VERSION_VAR
    QUICKJS_VERSION
)

if(QUICKJS_FOUND)
  if(NOT TARGET quickjs.lto AND EXISTS "${QUICKJS_LTO_LIBRARY}")
    add_library(quickjs.lto UNKNOWN IMPORTED)
    set_target_properties(quickjs.lto PROPERTIES
      IMPORTED_LINK_INTERFACE_LANGUAGES C
      INTERFACE_INCLUDE_DIRECTORIES "${QUICKJS_INCLUDE_DIR}"
      IMPORTED_LOCATION "${QUICKJS_LTO_LIBRARY}"
    )
    set_property(TARGET quickjs.lto APPEND PROPERTY
      INTERFACE_LINK_LIBRARIES ${QUICKJS_LIBRARY2}
    )
  endif()
  if(NOT TARGET quickjs AND EXISTS "${QUICKJS_LIBRARY}")
    add_library(quickjs UNKNOWN IMPORTED)
    set_target_properties(quickjs PROPERTIES
      IMPORTED_LINK_INTERFACE_LANGUAGES C
      INTERFACE_INCLUDE_DIRECTORIES "${QUICKJS_INCLUDE_DIR}"
      IMPORTED_LOCATION "${QUICKJS_LIBRARY}"
    )
    set_property(TARGET quickjs APPEND PROPERTY
      INTERFACE_LINK_LIBRARIES ${QUICKJS_LIBRARY2}
    )
  endif()
endif()
