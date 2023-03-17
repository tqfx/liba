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
# ``QUICKJS_LIBRARY_IPO``
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

find_library(QUICKJS_LIBRARY_IPO NAMES quickjs.lto PATH_SUFFIXES quickjs)
find_library(QUICKJS_LIBRARY NAMES quickjs PATH_SUFFIXES quickjs)
mark_as_advanced(QUICKJS_LIBRARY_IPO QUICKJS_LIBRARY)
if(EXISTS "${QUICKJS_LIBRARY}" OR EXISTS "${QUICKJS_LIBRARY_IPO}")
  if(EXISTS "${QUICKJS_LIBRARY_IPO}")
    list(APPEND QUICKJS_LIBRARIES ${QUICKJS_LIBRARY_IPO})
  elseif(EXISTS "${QUICKJS_LIBRARY}")
    list(APPEND QUICKJS_LIBRARIES ${QUICKJS_LIBRARY})
  endif()
  if(UNIX)
    list(APPEND QUICKJS_LIBRARIES m ${CMAKE_DL_LIBS})
  endif()
  find_library(QUICKJS_PTHREAD_LIBRARY pthread)
  mark_as_advanced(QUICKJS_PTHREAD_LIBRARY)
  if(QUICKJS_PTHREAD_LIBRARY)
    list(APPEND QUICKJS_LIBRARIES pthread)
  endif()
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

if(NOT TARGET quickjs AND QUICKJS_FOUND)
  set(libraries ${QUICKJS_LIBRARIES})
  if(EXISTS "${QUICKJS_LIBRARY_IPO}" OR EXISTS "${QUICKJS_LIBRARY}")
    add_library(quickjs UNKNOWN IMPORTED)
    set_target_properties(quickjs PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${QUICKJS_INCLUDE_DIR}"
      IMPORTED_LINK_INTERFACE_LANGUAGES C
    )
    if(EXISTS "${QUICKJS_LIBRARY_IPO}")
      list(REMOVE_ITEM libraries ${QUICKJS_LIBRARY_IPO})
      set_property(TARGET quickjs PROPERTY
        IMPORTED_LOCATION "${QUICKJS_LIBRARY_IPO}"
      )
    elseif(EXISTS "${QUICKJS_LIBRARY}")
      list(REMOVE_ITEM libraries ${QUICKJS_LIBRARY})
      set_property(TARGET quickjs PROPERTY
        IMPORTED_LOCATION "${QUICKJS_LIBRARY}"
      )
    endif()
    set_property(TARGET quickjs APPEND PROPERTY
      INTERFACE_LINK_LIBRARIES ${libraries}
    )
  endif()
  set(libraries)
endif()
