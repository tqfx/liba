#.rst:
# FindLuaJIT
# ----------
#
# Find luajit include dirs and libraries.
#
# Optional COMPONENTS
# ^^^^^^^^^^^^^^^^^^^
#
# ``luajit``
#
# Imported Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines the following :ref:`Imported Targets <Imported Targets>`:
#
# ``luajit``
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``LUAJIT_FOUND``
#
# ``LUAJIT_INCLUDE_DIR``
#
# ``LUAJIT_LIBRARIES``
#
# ``LUAJIT_VERSION``
#
# ``LUAJIT_VERSION_MAJOR``
#
# ``LUAJIT_VERSION_MINOR``
#
# ``LUAJIT_VERSION_PATCH``
#
# ``LuaJIT_luajit_FOUND``
#
# ``LUAJIT_EXECUTABLE``
#
# Cache variables
# ^^^^^^^^^^^^^^^
#
# Search results are saved persistently in CMake cache entries:
#
# ``LUAJIT_INCLUDE_DIR``
#
# ``LUAJIT_LIBRARY``
#
# ``LUA_MATH_LIBRARY``
#
# ``LUAJIT_EXECUTABLE``
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
list(APPEND LUAJIT_REQUIRED_VARS LUAJIT_LIBRARIES LUAJIT_INCLUDE_DIR)

foreach(VERSION ${LuaJIT_FIND_VERSION} 2.1 2.0)
  string(REGEX MATCH "^([0-9]+)\\.([0-9]+)" VERSION "${VERSION}")
  find_path(LUAJIT_INCLUDE_DIR luajit.h PATH_SUFFIXES include
    include/luajit${CMAKE_MATCH_1}${CMAKE_MATCH_2}
    include/luajit${CMAKE_MATCH_1}.${CMAKE_MATCH_2}
    include/luajit-${CMAKE_MATCH_1}.${CMAKE_MATCH_2}
  )
  if(LUAJIT_INCLUDE_DIR)
    break()
  endif()
endforeach()
mark_as_advanced(LUAJIT_INCLUDE_DIR)

if(EXISTS "${LUAJIT_INCLUDE_DIR}/luajit.h")
  file(STRINGS ${LUAJIT_INCLUDE_DIR}/luajit.h LUAJIT_VERSION REGEX "^#define[ \t]+LUAJIT_VERSION[ \t]+.*")
  string(REGEX REPLACE ".*LUAJIT_VERSION[^0-9]+([^\"]+).*" "\\1" LUAJIT_VERSION ${LUAJIT_VERSION})
  string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]).*" "\\1" LUAJIT_VERSION_PATCH "${LUAJIT_VERSION}")
  string(REGEX REPLACE "^[0-9]+\\.([0-9]).*" "\\1" LUAJIT_VERSION_MINOR "${LUAJIT_VERSION}")
  string(REGEX REPLACE "^([0-9]).*" "\\1" LUAJIT_VERSION_MAJOR "${LUAJIT_VERSION}")
endif()

if(EXISTS "${LUAJIT_INCLUDE_DIR}/lua.h")
  file(STRINGS ${LUAJIT_INCLUDE_DIR}/lua.h VERSION REGEX "^#define[ \t]+LUA_(RELEASE[ \t]+\"Lua [0-9]|VERSION([ \t]+\"Lua [0-9]|_[MR])).*")
  string(REGEX REPLACE ".*;#define[ \t]+LUA_VERSION_MAJOR[ \t]+\"([0-9])\"[ \t]*;.*" "\\1" LUA_VERSION_MAJOR ";${VERSION};")
  if(LUA_VERSION_MAJOR MATCHES "^[0-9]+$")
    string(REGEX REPLACE ".*;#define[ \t]+LUA_VERSION_MINOR[ \t]+\"([0-9])\"[ \t]*;.*" "\\1" LUA_VERSION_MINOR ";${VERSION};")
    string(REGEX REPLACE ".*;#define[ \t]+LUA_VERSION_RELEASE[ \t]+\"([0-9])\"[ \t]*;.*" "\\1" LUA_VERSION_PATCH ";${VERSION};")
    set(LUA_VERSION "${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}.${LUA_VERSION_PATCH}")
  else()
    string(REGEX REPLACE ".*;#define[ \t]+LUA_RELEASE[ \t]+\"Lua ([0-9.]+)\"[ \t]*;.*" "\\1" LUA_VERSION ";${VERSION};")
    if(NOT LUA_VERSION MATCHES "^[0-9.]+$")
      string(REGEX REPLACE ".*;#define[ \t]+LUA_VERSION[ \t]+\"Lua ([0-9.]+)\"[ \t]*;.*" "\\1" LUA_VERSION ";${VERSION};")
    endif()
    string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]).*" "\\1" LUA_VERSION_PATCH "${LUA_VERSION}")
    string(REGEX REPLACE "^[0-9]+\\.([0-9]).*" "\\1" LUA_VERSION_MINOR "${LUA_VERSION}")
    string(REGEX REPLACE "^([0-9]).*" "\\1" LUA_VERSION_MAJOR "${LUA_VERSION}")
  endif()
endif()

list(FIND LuaJIT_FIND_COMPONENTS "luajit" index)
if(${index} GREATER -1)
  find_program(LUAJIT_EXECUTABLE NAMES luajit-${LUAJIT_VERSION} luajit)
  mark_as_advanced(LUAJIT_EXECUTABLE)
endif()
if(LuaJIT_FIND_REQUIRED_luajit)
  list(APPEND LUAJIT_REQUIRED_VARS LUAJIT_EXECUTABLE)
endif()
if(EXISTS "${LUAJIT_EXECUTABLE}")
  set(LuaJIT_luajit_FOUND 1)
endif()
set(index)

if(NOT LUAJIT_VERSION AND EXISTS "${LUAJIT_EXECUTABLE}")
  get_filename_component(LUAJIT_DIR "${LUAJIT_EXECUTABLE}" DIRECTORY)
  get_filename_component(LUAJIT_DIR "${LUAJIT_DIR}" DIRECTORY)
  execute_process(COMMAND ${LUAJIT_EXECUTABLE} -v OUTPUT_VARIABLE LUAJIT_VERSION)
  find_path(LUAJIT_INCLUDE_DIR luajit.h HINTS ${LUAJIT_DIR} PATH_SUFFIXES include)
  string(REGEX REPLACE "LuaJIT[ ]+([^ ]+).*" "\\1" LUAJIT_VERSION "${LUAJIT_VERSION}")
  string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]).*" "\\1" LUAJIT_VERSION_PATCH "${LUAJIT_VERSION}")
  string(REGEX REPLACE "^[0-9]+\\.([0-9]).*" "\\1" LUAJIT_VERSION_MINOR "${LUAJIT_VERSION}")
  string(REGEX REPLACE "^([0-9]).*" "\\1" LUAJIT_VERSION_MAJOR "${LUAJIT_VERSION}")
endif()

find_library(LUAJIT_LIBRARY NAMES_PER_DIR NAMES luajit-5.1 lua51 lua5.1 lua-5.1)
mark_as_advanced(LUAJIT_LIBRARY)
if(EXISTS "${LUAJIT_LIBRARY}")
  list(APPEND LUAJIT_LIBRARIES ${LUAJIT_LIBRARY})
  if(UNIX AND NOT APPLE AND NOT BEOS)
    find_library(LUA_MATH_LIBRARY m)
    mark_as_advanced(LUA_MATH_LIBRARY)
    if(NOT EXISTS "${LUA_MATH_LIBRARY}")
      list(APPEND LUAJIT_LIBRARIES m)
    else()
      list(APPEND LUAJIT_LIBRARIES ${LUA_MATH_LIBRARY})
    endif()
    get_filename_component(ext ${LUAJIT_LIBRARY} EXT)
    if(CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL ext)
      list(APPEND LUAJIT_LIBRARIES ${CMAKE_DL_LIBS})
    endif()
    set(ext)
  endif()
endif()

find_package_handle_standard_args(LuaJIT
  FOUND_VAR
    LUAJIT_FOUND
  REQUIRED_VARS
    ${LUAJIT_REQUIRED_VARS}
  VERSION_VAR
    LUAJIT_VERSION
  HANDLE_COMPONENTS
)

if(LUAJIT_FOUND)
  if(NOT TARGET luajit AND EXISTS "${LUAJIT_LIBRARY}")
    add_library(luajit UNKNOWN IMPORTED)
    set_target_properties(luajit PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${LUAJIT_INCLUDE_DIR}"
      IMPORTED_LINK_INTERFACE_LANGUAGES C
      IMPORTED_LOCATION "${LUAJIT_LIBRARY}"
    )
    set(libraries ${LUAJIT_LIBRARIES})
    list(REMOVE_ITEM libraries ${LUAJIT_LIBRARY})
    set_property(TARGET luajit APPEND PROPERTY
      INTERFACE_LINK_LIBRARIES ${libraries}
    )
    set(libraries)
  endif()
endif()
