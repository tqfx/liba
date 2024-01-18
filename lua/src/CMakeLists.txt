cmake_minimum_required(VERSION 2.8.12...4.0)
project(lua C)

file(GLOB LUA_H lua.h src/lua.h)
file(STRINGS "${LUA_H}" VERSION REGEX "^#define[ \t]+LUA_(RELEASE[ \t]+\"Lua [0-9]|VERSION([ \t]+\"Lua [0-9]|_[MR])).*")
string(REGEX REPLACE ".*;#define[ \t]+LUA_VERSION_MAJOR[^0-9]+([0-9]+)[^;]*;.*" "\\1" LUA_VERSION_MAJOR ";${VERSION};")
if(LUA_VERSION_MAJOR MATCHES "^[0-9]+$")
  string(REGEX REPLACE ".*;#define[ \t]+LUA_VERSION_MINOR[^0-9]+([0-9]+)[^;]*;.*" "\\1" LUA_VERSION_MINOR ";${VERSION};")
  string(REGEX REPLACE ".*;#define[ \t]+LUA_VERSION_RELEASE[^0-9(]+([0-9]+)[^;]*;.*" "\\1" LUA_VERSION_PATCH ";${VERSION};")
  set(LUA_RELEASE "${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}.${LUA_VERSION_PATCH}")
else()
  string(REGEX REPLACE ".*;#define[ \t]+LUA_RELEASE[ \t]+\"Lua ([0-9.]+)\"[ \t]*;.*" "\\1" LUA_RELEASE ";${VERSION};")
  if(NOT LUA_RELEASE MATCHES "^[0-9.]+$")
    string(REGEX REPLACE ".*;#define[ \t]+LUA_VERSION[ \t]+\"Lua ([0-9.]+)\"[ \t]*;.*" "\\1" LUA_RELEASE ";${VERSION};")
  endif()
  string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]).*" "\\1" LUA_VERSION_PATCH "${LUA_RELEASE}")
  string(REGEX REPLACE "^[0-9]+\\.([0-9]).*" "\\1" LUA_VERSION_MINOR "${LUA_RELEASE}")
  string(REGEX REPLACE "^([0-9]).*" "\\1" LUA_VERSION_MAJOR "${LUA_RELEASE}")
endif()
set(LUA_VERSION "${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}")

set(PROJECT_VERSION ${LUA_RELEASE})
set(PROJECT_VERSION_MAJOR ${LUA_VERSION_MAJOR})
set(PROJECT_VERSION_MINOR ${LUA_VERSION_MINOR})
set(PROJECT_VERSION_PATCH ${LUA_VERSION_PATCH})
set(PROJECT_DESCRIPTION "A powerful, efficient, lightweight, embeddable scripting language.")
set(PROJECT_HOMEPAGE_URL "http://www.lua.org")
set(CMAKE_C_EXTENSIONS 1)
set(CMAKE_C_STANDARD 99)

if(LUA_STATIC)
  list(REMOVE_ITEM CMAKE_FIND_LIBRARY_PREFIXES "${CMAKE_STATIC_LIBRARY_PREFIX}")
  list(REMOVE_ITEM CMAKE_FIND_LIBRARY_SUFFIXES "${CMAKE_STATIC_LIBRARY_SUFFIX}")
  list(INSERT CMAKE_FIND_LIBRARY_PREFIXES 0 "${CMAKE_STATIC_LIBRARY_PREFIX}")
  list(INSERT CMAKE_FIND_LIBRARY_SUFFIXES 0 "${CMAKE_STATIC_LIBRARY_SUFFIX}")
endif()

option(LUA_IPO "Enable/Disable interprocedural optimization" 0)
if(NOT CMAKE_VERSION VERSION_LESS 3.9 AND LUA_IPO)
  cmake_policy(SET CMP0069 NEW)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT LUA_IPO)
endif()

if(DEFINED ENV{ANDROID_ROOT} AND EXISTS $ENV{ANDROID_ROOT})
  option(LUA_PIE "Enable/Disable position independent code" 1)
else()
  option(LUA_PIE "Enable/Disable position independent code" 0)
endif()
set(CMAKE_POSITION_INDEPENDENT_CODE ${LUA_PIE})
if(NOT CMAKE_VERSION VERSION_LESS 3.14)
  cmake_policy(SET CMP0083 NEW)
  include(CheckPIESupported)
  check_pie_supported()
endif()

if(CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL .lib)
  list(APPEND LUA_PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(NOT LUA_VERSION VERSION_LESS 5.1)
  option(LUA_APICHECK "Enable/Disable checks on the C API" 0)
  if(LUA_APICHECK)
    list(APPEND LUA_PRIVATE LUA_USE_APICHECK)
  endif()
else()
  unset(LUA_APICHECK CACHE)
endif()

macro(load name text)
  file(READ ${name} ${text})
  file(READ ${name} ${text}_)
endmacro()
macro(save name text)
  if(NOT ${text} STREQUAL ${text}_)
    file(WRITE ${name} "${${text}}")
    message(STATUS "write ${name}")
  endif()
  set(${text}_)
  set(${text})
endmacro()

file(GLOB LUACONF_H luaconf.h src/luaconf.h)
if(EXISTS ${LUACONF_H})
  load(${LUACONF_H} LUACONF_H_TEXT)
  if(APPLE)
    list(APPEND LUA_PUBLIC LUA_USE_MACOSX)
  elseif(UNIX)
    list(APPEND LUA_PUBLIC LUA_USE_LINUX)
  elseif(NOT WIN32)
    list(APPEND LUA_PUBLIC LUA_USE_POSIX)
  endif()
endif()
option(LUA_COMPAT "Enable/Disable build lua compatibility" 0)
if(LUA_COMPAT)
  if(NOT LUA_VERSION VERSION_LESS 5.4)
    list(APPEND LUA_PUBLIC LUA_COMPAT_5_3)
  elseif(NOT LUA_VERSION VERSION_LESS 5.3)
    list(APPEND LUA_PUBLIC LUA_COMPAT_5_2 LUA_COMPAT_5_1)
  elseif(NOT LUA_VERSION VERSION_LESS 5.2)
    list(APPEND LUA_PUBLIC LUA_COMPAT_ALL)
  endif()
endif()
string(REGEX REPLACE "#define LUA_USE_READLINE[^\n]*\n" "" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
if(NOT LUA_VERSION VERSION_LESS 5.1 AND LUA_VERSION VERSION_LESS 5.2 AND LUA_COMPAT)
  string(REPLACE "#undef LUA_COMPAT_GETN" "#define LUA_COMPAT_GETN" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REPLACE "#undef LUA_COMPAT_LOADLIB" "#define LUA_COMPAT_LOADLIB" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
elseif(NOT LUA_VERSION VERSION_LESS 5.1 AND LUA_VERSION VERSION_LESS 5.2)
  string(REPLACE "#define LUA_COMPAT_GETN" "#undef LUA_COMPAT_GETN" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REPLACE "#define LUA_COMPAT_LOADLIB" "#undef LUA_COMPAT_LOADLIB" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
endif()

if(NOT LUA_VERSION VERSION_LESS 5.3)
  option(LUA_NOCVTN2S "Disable/Enable automatic coercion from strings to numbers" 0)
  if(LUA_NOCVTN2S)
    string(REGEX REPLACE "[^\n]*#define LUA_NOCVTN2S[^\n]*" "#define LUA_NOCVTN2S" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  else()
    string(REGEX REPLACE "[^\n]*#define LUA_NOCVTN2S[^\n]*" "/* #define LUA_NOCVTN2S */" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  endif()
  option(LUA_NOCVTS2N "Disable/Enable automatic coercion from numbers to strings" 0)
  if(LUA_NOCVTS2N)
    string(REGEX REPLACE "[^\n]*#define LUA_NOCVTS2N[^\n]*" "#define LUA_NOCVTS2N" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  else()
    string(REGEX REPLACE "[^\n]*#define LUA_NOCVTS2N[^\n]*" "/* #define LUA_NOCVTS2N */" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  endif()
else()
  unset(LUA_NOCVTN2S CACHE)
  unset(LUA_NOCVTS2N CACHE)
endif()

option(LUA_32BITS "Enable/Disable build lua 32bits" 0)
if(LUA_32BITS)
  string(REGEX REPLACE "[^\n]*#define LUA_32BITS[^\n]*" "#define LUA_32BITS\t1" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
elseif(NOT LUA_VERSION VERSION_LESS 5.4)
  string(REGEX REPLACE "[^\n]*#define LUA_32BITS[^\n]*" "#define LUA_32BITS\t0" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
elseif(NOT LUA_VERSION VERSION_LESS 5.3)
  string(REGEX REPLACE "[^\n]*#define LUA_32BITS[^\n]*" "/* #define LUA_32BITS */" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
endif()
if(LUA_VERSION VERSION_LESS 5.3 AND LUA_32BITS)
  string(REPLACE "#define LUA_NUMBER_DOUBLE" "#define LUA_NUMBER_FLOAT" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REGEX REPLACE "#define LUA_NUMBER([ \t])+[^\n]*" "#define LUA_NUMBER\\1float" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REGEX REPLACE "#define LUAI_UACNUMBER([ \t])+[^\n]*" "#define LUAI_UACNUMBER\\1float" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REGEX REPLACE "#define LUA_NUMBER_SCAN([ \t])+[^\n]*" "#define LUA_NUMBER_SCAN\\1\"%f\"" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REGEX REPLACE "#define LUA_NUMBER_FMT([ \t])+[^\n]*" "#define LUA_NUMBER_FMT\\1\"%.7g\"" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REGEX REPLACE "#define l_mathop\\(([^)]+)\\)([ \t])+[^\n]*" "#define l_mathop(\\1)\\2(\\1##f)" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REPLACE "strtod(" "strtof(" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
elseif(LUA_VERSION VERSION_LESS 5.3)
  string(REPLACE "#define LUA_NUMBER_FLOAT" "#define LUA_NUMBER_DOUBLE" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REGEX REPLACE "#define LUA_NUMBER([ \t])+[^\n]*" "#define LUA_NUMBER\\1double" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REGEX REPLACE "#define LUAI_UACNUMBER([ \t])+[^\n]*" "#define LUAI_UACNUMBER\\1double" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REGEX REPLACE "#define LUA_NUMBER_SCAN([ \t])+[^\n]*" "#define LUA_NUMBER_SCAN\\1\"%lf\"" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REGEX REPLACE "#define LUA_NUMBER_FMT([ \t])+[^\n]*" "#define LUA_NUMBER_FMT\\1\"%.14g\"" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REGEX REPLACE "#define l_mathop\\(([^)]+)\\)([ \t])+[^\n]*" "#define l_mathop(\\1)\\2(\\1)" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  string(REPLACE "strtof(" "strtod(" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
endif()

if(NOT WIN32)
  string(REGEX REPLACE "([^/\\]+)$" "\\1/" LUA_ROOT "${CMAKE_INSTALL_PREFIX}")
  string(REGEX REPLACE "#define LUA_ROOT([ \t])+[^\n]*" "#define LUA_ROOT\\1\"${LUA_ROOT}\"" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
endif()
if(APPLE)
  if(NOT LUA_VERSION VERSION_LESS 5.2)
    set(LUA_CPATH_DEFAULT ".so;\" \\\n\t\tLUA_CDIR\"?.dylib;\" LUA_CDIR\"loadall.dylib;\" \"./?.dylib\"\n")
  else()
    set(LUA_CPATH_DEFAULT ".so;\" \\\n\t\"./?.dylib;\" LUA_CDIR\"?.dylib;\" LUA_CDIR\"loadall.dylib\"\n")
  endif()
  string(REPLACE ".so\"\n" "${LUA_CPATH_DEFAULT}" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
endif()

file(GLOB LOSLIB_C loslib.c src/loslib.c)
if(EXISTS ${LOSLIB_C})
  load(${LOSLIB_C} LOSLIB_C_TEXT)
endif()

string(REGEX REPLACE "([^/\\]+)[/\\]*$" "\\1/tmp/lua_XXXXXX" LUA_TMPNAMTEMPLATE "$ENV{PREFIX}")
if(LUA_TMPNAMTEMPLATE)
  string(LENGTH "${LUA_TMPNAMTEMPLATE} " LUA_TMPNAMBUFSIZE)
  if(NOT LUA_VERSION VERSION_LESS 5.2)
    string(REGEX REPLACE "\"[^\"]*/tmp/lua_XXXXXX\"" "\"${LUA_TMPNAMTEMPLATE}\"" LOSLIB_C_TEXT "${LOSLIB_C_TEXT}")
    string(REGEX REPLACE "LUA_TMPNAMBUFSIZE\t[0-9]*\n" "LUA_TMPNAMBUFSIZE\t${LUA_TMPNAMBUFSIZE}\n" LOSLIB_C_TEXT "${LOSLIB_C_TEXT}")
  else()
    string(REGEX REPLACE "\"[^\"]*/tmp/lua_XXXXXX\"" "\"${LUA_TMPNAMTEMPLATE}\"" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
    string(REGEX REPLACE "LUA_TMPNAMBUFSIZE\t[0-9]*\n" "LUA_TMPNAMBUFSIZE\t${LUA_TMPNAMBUFSIZE}\n" LUACONF_H_TEXT "${LUACONF_H_TEXT}")
  endif()
endif()

file(GLOB LUA_C lua.c src/lua.c)
if(EXISTS ${LUA_C})
  load(${LUA_C} LUA_C_TEXT)
endif()

string(FIND "${LUA_C_TEXT}" "LUA_READLINE_C" index)
if(${index} EQUAL -1)
  set(index "#include \"lua.h\"")
  string(REPLACE "${index}" "${index}\n#if defined(LUA_READLINE_C)\n#include LUA_READLINE_C\n#endif" LUA_C_TEXT "${LUA_C_TEXT}")
endif()
string(FIND "${LUA_C_TEXT}" "lua_initreadline" index)
if(${index} EQUAL -1)
  set(index "  while ((status = loadline(L)) != -1)")
  string(REPLACE "${index}" "#if defined(lua_initreadline)\n  lua_initreadline(L);\n#endif\n${index}" LUA_C_TEXT "${LUA_C_TEXT}")
endif()
set(index)

if(EXISTS ${LUA_C})
  save(${LUA_C} LUA_C_TEXT)
endif()
if(EXISTS ${LOSLIB_C})
  save(${LOSLIB_C} LOSLIB_C_TEXT)
endif()
if(EXISTS ${LUACONF_H})
  save(${LUACONF_H} LUACONF_H_TEXT)
endif()

set(LUA_USER_H CACHE FILEPATH "generic extra include file")
function(lua_library target)
  target_compile_definitions(${target} PUBLIC ${LUA_PUBLIC})
  target_include_directories(${target} PUBLIC $<INSTALL_INTERFACE:include>)
  if(EXISTS ${LUA_USER_H})
    get_filename_component(lua_user_h ${LUA_USER_H} DIRECTORY)
    target_include_directories(${target} PUBLIC $<BUILD_INTERFACE:${lua_user_h}>)
    get_filename_component(lua_user_h ${LUA_USER_H} NAME)
    target_compile_definitions(${target} PUBLIC $<BUILD_INTERFACE:LUA_USER_H="${lua_user_h}">)
    set(lua_user_h)
  endif()
  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/src)
    target_include_directories(${target} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>)
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "TinyCC" AND CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL .lib)
    set_target_properties(${target} PROPERTIES IMPORT_SUFFIX .def)
  endif()
  set_target_properties(${target} PROPERTIES POSITION_INDEPENDENT_CODE 1
    INTERPROCEDURAL_OPTIMIZATION ${LUA_IPO}
  )
endfunction()

if(NOT LUA_MATH_LIBRARY AND WIN32)
  unset(LUA_MATH_LIBRARY CACHE)
elseif(NOT LUA_MATH_LIBRARY)
  set(LUA_MATH_LIBRARY m)
endif()
function(lua_library_link)
  foreach(target ${ARGN})
    target_link_libraries(${target} INTERFACE ${CMAKE_DL_LIBS} ${LUA_MATH_LIBRARY})
  endforeach()
endfunction()

file(GLOB LUA_C lua.c src/lua.c)
file(GLOB LUAC_C luac.c src/luac.c)
file(GLOB SOURCES *.[ch] src/*.[ch])
list(REMOVE_ITEM SOURCES ${LUA_C} ${LUAC_C})

add_library(lua.o OBJECT ${SOURCES})
lua_library(lua.o)
add_library(lualib SHARED $<TARGET_OBJECTS:lua.o>)
lua_library(lualib)
add_library(liblua STATIC $<TARGET_OBJECTS:lua.o>)
lua_library(liblua)
add_executable(lua ${LUA_C})
add_executable(luac ${LUAC_C})
lua_library_link(lualib liblua)
target_link_libraries(lua PRIVATE lualib)
target_link_libraries(luac PRIVATE liblua)
if(WIN32)
  set_property(TARGET lualib PROPERTY PREFIX "")
  set_property(TARGET liblua PROPERTY PREFIX lib)
  set(suffix ${PROJECT_VERSION_MAJOR}${PROJECT_VERSION_MINOR})
else()
  set(suffix ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
  set_target_properties(luac lua PROPERTIES SUFFIX ${suffix})
endif()
set_property(TARGET lualib liblua PROPERTY OUTPUT_NAME lua${suffix})
set_property(TARGET luac lua PROPERTY INTERPROCEDURAL_OPTIMIZATION ${LUA_IPO})
set_property(TARGET luac lua lua.o APPEND PROPERTY COMPILE_DEFINITIONS ${LUA_PRIVATE})
if(WIN32)
  set_property(TARGET lua.o APPEND PROPERTY COMPILE_DEFINITIONS LUA_BUILD_AS_DLL)
  set_property(TARGET lualib APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS LUA_BUILD_AS_DLL)
endif()

include(GNUInstallDirs)
file(GLOB PUBLIC_HEADER ${LUA_USER_H}
  lauxlib.h src/lauxlib.h
  luaconf.h src/luaconf.h
  lualib.h src/lualib.h
  lua.h src/lua.h
  lua.hpp src/lua.hpp etc/lua.hpp
)
set(LUA_INSTALL_CMOD ${CMAKE_INSTALL_LIBDIR}/lua/${LUA_VERSION})
set(LUA_INSTALL_LMOD ${CMAKE_INSTALL_DATADIR}/lua/${LUA_VERSION})
set(LUA_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/lua${LUA_VERSION})
install(FILES ${PUBLIC_HEADER} DESTINATION ${LUA_INCLUDE_DIR})
install(TARGETS lualib liblua lua luac EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(EXPORT ${PROJECT_NAME}-targets FILE ${PROJECT_NAME}-targets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lua${LUA_VERSION}
)
include(CMakePackageConfigHelpers)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake "@PACKAGE_INIT@\n"
  "include(\"\${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@-targets.cmake\")\n"
  "set(LUA_INSTALL_CMOD \"\${PACKAGE_PREFIX_DIR}/@LUA_INSTALL_CMOD@\")\n"
  "set(LUA_INSTALL_LMOD \"\${PACKAGE_PREFIX_DIR}/@LUA_INSTALL_LMOD@\")\n"
  "set(LUA_INCLUDE_DIR \"\${PACKAGE_PREFIX_DIR}/@LUA_INCLUDE_DIR@\")\n"
  "set(LUA_BINDIR \"\${PACKAGE_PREFIX_DIR}/@CMAKE_INSTALL_BINDIR@\")\n"
  "set(LUA_LIBDIR \"\${PACKAGE_PREFIX_DIR}/@CMAKE_INSTALL_LIBDIR@\")\n"
)
configure_package_config_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lua${LUA_VERSION}
)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  VERSION ${PROJECT_VERSION} COMPATIBILITY AnyNewerVersion
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lua${LUA_VERSION}
)
get_property(prop TARGET lualib PROPERTY INTERFACE_COMPILE_DEFINITIONS)
string(REPLACE "<BUILD_" "<INSTALL_" PC_CFLAGS "-D$<JOIN:${prop}, -D>")
get_property(prop TARGET lualib PROPERTY INTERFACE_LINK_LIBRARIES)
string(REGEX REPLACE "\\$<BUILD_INTERFACE:[^>]*>" "" prop "${prop}")
string(REPLACE "INSTALL_INTERFACE" "BUILD_INTERFACE" prop "${prop}")
string(REPLACE "-l$<JOIN:, -l>" "" PC_LDFLAGS "-l$<JOIN:${prop}, -l>")
file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/lua${LUA_VERSION}.pc CONTENT
"prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=\${prefix}
libdir=\${exec_prefix}/${CMAKE_INSTALL_LIBDIR}
includedir=\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}/lua${LUA_VERSION}
INSTALL_LMOD=\${prefix}/${CMAKE_INSTALL_DATADIR}/lua/${LUA_VERSION}
INSTALL_CMOD=\${prefix}/${CMAKE_INSTALL_LIBDIR}/lua/${LUA_VERSION}\n
Name: ${PROJECT_NAME}
Description: ${PROJECT_DESCRIPTION}
Version: ${PROJECT_VERSION}
URL: ${PROJECT_HOMEPAGE_URL}
Cflags: -I\${includedir} ${PC_CFLAGS}
Libs: -L\${libdir} -llua${suffix}
Libs.private: ${PC_LDFLAGS}
")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lua${LUA_VERSION}.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
install(FILES doc/lua.1 RENAME lua${LUA_VERSION}.1
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man1
)
install(FILES doc/luac.1 RENAME luac${LUA_VERSION}.1
  DESTINATION ${CMAKE_INSTALL_MANDIR}/man1
)
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
include(CPack)

if(EXISTS ${LUA_USER_H})
  get_filename_component(LUA_USER_H ${LUA_USER_H} NAME)
  install(CODE "file(READ \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/lua${LUA_VERSION}/lua.h\" text)
  string(REGEX REPLACE \"/([^/]+)#if defined\\\\(LUA_USER_H\\\\)\" \"/\\\\1#include \\\"${LUA_USER_H}\\\"\\n#if defined(LUA_USER_H)\" text \"\${text}\")
  file(WRITE \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/lua${LUA_VERSION}/lua.h\" \"\${text}\")")
endif()
