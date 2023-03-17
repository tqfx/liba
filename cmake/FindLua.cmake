#.rst:
# FindLua
# -------
#
# Find lua include dirs and libraries.
#
# Optional COMPONENTS
# ^^^^^^^^^^^^^^^^^^^
#
# ``lua`` and ``luac``
#
# Imported Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines the following :ref:`Imported Targets <Imported Targets>`:
#
# ``lualib``
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``LUA_FOUND``
#
# ``LUA_INCLUDE_DIR``
#
# ``LUA_LIBRARIES``
#
# ``LUA_VERSION``
#
# ``LUA_VERSION_MAJOR``
#
# ``LUA_VERSION_MINOR``
#
# ``LUA_VERSION_PATCH``
#
# ``Lua_lua_FOUND``
#
# ``LUA_EXECUTABLE``
#
# ``Lua_luac_FOUND``
#
# ``LUAC_EXECUTABLE``
#
# Cache variables
# ^^^^^^^^^^^^^^^
#
# Search results are saved persistently in CMake cache entries:
#
# ``LUA_INCLUDE_DIR``
#
# ``LUA_LIBRARY``
#
# ``LUA_MATH_LIBRARY``
#
# ``LUA_EXECUTABLE``
#
# ``LUAC_EXECUTABLE``
#
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
list(APPEND LUA_REQUIRED_VARS LUA_LIBRARIES LUA_INCLUDE_DIR)

foreach(VERSION ${Lua_FIND_VERSION} 5.4 5.3 5.2 5.1 5.0)
  string(REGEX MATCH "^([0-9]+)\\.([0-9]+)" VERSION "${VERSION}")
  find_path(LUA_INCLUDE_DIR lua.h PATH_SUFFIXES
    include/lua${CMAKE_MATCH_1}${CMAKE_MATCH_2}
    include/lua${CMAKE_MATCH_1}.${CMAKE_MATCH_2}
    include/lua-${CMAKE_MATCH_1}.${CMAKE_MATCH_2}
    include HINTS ENV LUA_DIR
  )
  if(LUA_INCLUDE_DIR)
    break()
  endif()
endforeach()
mark_as_advanced(LUA_INCLUDE_DIR)

if(EXISTS "${LUA_INCLUDE_DIR}/lua.h")
  file(STRINGS ${LUA_INCLUDE_DIR}/lua.h VERSION REGEX "^#define[ \t]+LUA_(RELEASE[ \t]+\"Lua [0-9]|VERSION([ \t]+\"Lua [0-9]|_[MR])).*")
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

if(NOT DEFINED ENV{LUA_DIR} AND EXISTS "${LUA_INCLUDE_DIR}")
  get_filename_component(LUA_DIR "${LUA_INCLUDE_DIR}" DIRECTORY)
  get_filename_component(modules "${LUA_INCLUDE_DIR}" NAME)
  if(NOT modules STREQUAL "include")
    get_filename_component(LUA_DIR "${LUA_DIR}" DIRECTORY)
  endif()
elseif(DEFINED ENV{LUA_DIR})
  file(TO_CMAKE_PATH "$ENV{LUA_DIR}" LUA_DIR)
endif()

string(REGEX MATCHALL "(luac|lua)" modules "${Lua_FIND_COMPONENTS}")
if(modules)
  list(REMOVE_DUPLICATES modules)
endif()
foreach(module ${modules})
  string(TOUPPER ${module} MODULE)
  find_program(${MODULE}_EXECUTABLE NAMES
    ${module}${LUA_VERSION_MAJOR}${LUA_VERSION_MINOR}
    ${module}${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
    ${module}-${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
    ${module} HINTS ${LUA_DIR} PATH_SUFFIXES bin
  )
  mark_as_advanced(${MODULE}_EXECUTABLE)
  if(Lua_FIND_REQUIRED_${module})
    list(APPEND LUA_REQUIRED_VARS ${MODULE}_EXECUTABLE)
  endif()
  if(EXISTS ${${MODULE}_EXECUTABLE})
    set(Lua_${module}_FOUND 1)
  endif()
  set(MODULE)
endforeach()
set(modules)

if(NOT LUA_VERSION)
  if(EXISTS "${LUA_EXECUTABLE}")
    execute_process(COMMAND ${LUA_EXECUTABLE} -v OUTPUT_VARIABLE LUA_VERSION ERROR_VARIABLE LUA_VERSION)
    get_filename_component(LUA_DIR "${LUA_EXECUTABLE}" DIRECTORY)
  elseif(EXISTS "${LUAC_EXECUTABLE}")
    execute_process(COMMAND ${LUAC_EXECUTABLE} -v OUTPUT_VARIABLE LUA_VERSION ERROR_VARIABLE LUA_VERSION)
    get_filename_component(LUA_DIR "${LUAC_EXECUTABLE}" DIRECTORY)
  endif()
  if(LUA_VERSION)
    get_filename_component(LUA_DIR "${LUA_DIR}" DIRECTORY)
    find_path(LUA_INCLUDE_DIR lua.h HINTS ${LUA_DIR} PATH_SUFFIXES include)
    string(REGEX REPLACE "Lua[ ]+([^ ]+).*" "\\1" LUA_VERSION "${LUA_VERSION}")
    string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]).*" "\\1" LUA_VERSION_PATCH "${LUA_VERSION}")
    string(REGEX REPLACE "^[0-9]+\\.([0-9]).*" "\\1" LUA_VERSION_MINOR "${LUA_VERSION}")
    string(REGEX REPLACE "^([0-9]).*" "\\1" LUA_VERSION_MAJOR "${LUA_VERSION}")
  endif()
endif()

find_library(LUA_LIBRARY NAMES_PER_DIR NAMES
  lua${LUA_VERSION_MAJOR}${LUA_VERSION_MINOR}
  lua${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
  lua-${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
  lua HINTS ${LUA_DIR} PATH_SUFFIXES lib
)
mark_as_advanced(LUA_LIBRARY)

if(EXISTS "${LUA_LIBRARY}")
  list(APPEND LUA_LIBRARIES ${LUA_LIBRARY})
  if(UNIX AND NOT APPLE AND NOT BEOS)
    find_library(LUA_MATH_LIBRARY m)
    mark_as_advanced(LUA_MATH_LIBRARY)
    if(NOT EXISTS "${LUA_MATH_LIBRARY}")
      list(APPEND LUA_LIBRARIES m)
    else()
      list(APPEND LUA_LIBRARIES ${LUA_MATH_LIBRARY})
    endif()
    get_filename_component(ext ${LUA_LIBRARY} EXT)
    if(CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL ext)
      list(APPEND LUA_LIBRARIES ${CMAKE_DL_LIBS})
    endif()
    set(ext)
  endif()
endif()

find_package_handle_standard_args(Lua
  FOUND_VAR
    LUA_FOUND
  REQUIRED_VARS
    ${LUA_REQUIRED_VARS}
  VERSION_VAR
    LUA_VERSION
  HANDLE_COMPONENTS
)

if(LUA_FOUND)
  if(NOT TARGET lualib AND EXISTS "${LUA_LIBRARY}")
    add_library(lualib UNKNOWN IMPORTED)
    set_target_properties(lualib PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${LUA_INCLUDE_DIR}"
      IMPORTED_LINK_INTERFACE_LANGUAGES C
      IMPORTED_LOCATION "${LUA_LIBRARY}"
    )
    set(libraries ${LUA_LIBRARIES})
    list(REMOVE_ITEM libraries ${LUA_LIBRARY})
    set_property(TARGET lualib APPEND PROPERTY
      INTERFACE_LINK_LIBRARIES ${libraries}
    )
    set(libraries)
  endif()
endif()
