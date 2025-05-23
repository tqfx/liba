set(OBJECTS $<TARGET_OBJECTS:a>)

if(LIBA_WITH_LUA)
  include(${CMAKE_CURRENT_LIST_DIR}/lua.cmake)
  add_subdirectory(${LUA_SOURCE_DIR} ${LUA_BINARY_DIR})

  if(DEFINED MSVC_VERSION AND MSVC_VERSION LESS 1800)
    option(LUA_ISOCLINE "Enable/Disable isocline in Lua" 0)
  else()
    option(LUA_ISOCLINE "Enable/Disable isocline in Lua" 1)
  endif()

  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/isocline/src/isocline.c AND LUA_ISOCLINE)
    file(RELATIVE_PATH LUA_READLINE_C ${LUA_SOURCE_DIR}/src ${CMAKE_CURRENT_LIST_DIR}/isocline.c)
    target_compile_definitions(lua PRIVATE LUA_READLINE_C="${LUA_READLINE_C}")
  endif()

  set(LUA_LIBRARIES lualib)
  set(LUA_EXECUTABLE ${CMAKE_CROSSCOMPILING_EMULATOR} $<TARGET_FILE:lua>)
  string(REGEX MATCHALL "[0-9]+" VERSION "${LUA_VERSION}.0.0")
  list(GET VERSION 0 LUA_VERSION_MAJOR)
  list(GET VERSION 1 LUA_VERSION_MINOR)

  if(LIBA_SANITIZE)
    target_compile_sanitize(PUBLIC liblua lualib lua.o)
    target_link_sanitize(PUBLIC liblua lualib lua luac)
    set(OBJECTS $<TARGET_OBJECTS:asan>)
  endif()
endif()

if(LIBA_CXX)
  file_scaner(SOURCES RECURSE src EXT c h cc hh cpp hpp)
else()
  file_scaner(SOURCES RECURSE src EXT c h)
endif()

set(CMAKE_SHARED_MODULE_PREFIX "")
add_library(alua MODULE ${OBJECTS} ${SOURCES})
set_target_properties(alua PROPERTIES DEFINE_SYMBOL A_EXPORTS OUTPUT_NAME ${PROJECT_NAME})
target_link_libraries(alua PRIVATE ${LUA_LIBRARIES})
add_library_properties(alua PRIVATE alib)
set_library_options(alua)

if("${LIBA_INSTALL}" MATCHES "^[Ll]ua$")
  install(TARGETS alua
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
else()
  install(TARGETS alua
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/lua/${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/lua/${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/lua/${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}
  )
endif()

if(PROJECT_IS_TOP_LEVEL AND BUILD_TESTING)
  file(GLOB_RECURSE SOURCES test/*.lua)

  function(find_format)
    find_package(StyLua)

    if(STYLUA_FOUND)
      add_stylua(afmt.lua VERBOSE ${ARGN})
      add_dependencies(afmt afmt.lua)
      return()
    endif()

    find_package(LuaFormat)

    if(LUA_FORMAT_FOUND)
      add_lua_format(afmt.lua VERBOSE ${ARGN})
      add_dependencies(afmt afmt.lua)
      return()
    endif()
  endfunction()

  find_format(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} ${SOURCES})
endif()

option(LIBA_LDOC "Enable/Disable ffi ldoc" 0)

if(LIBA_LDOC)
  find_package(LDoc)
endif()

if(LIBA_LDOC AND LDOC_FOUND)
  file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/LDoc
    CONTENT "project = '${PROJECT_NAME}'
description = '${PROJECT_DESCRIPTION}'
format = 'markdown'
")
  create_ldoc(adoc.lua CONFIG ${CMAKE_CURRENT_BINARY_DIR}/LDoc
    OPTIONS --not_luadoc ${CMAKE_CURRENT_SOURCE_DIR}/src
  )
  add_dependencies(adoc adoc.lua)
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/test/CMakeLists.txt AND LUA_EXECUTABLE)
  get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

  if(NOT CMAKE_VERSION VERSION_LESS 3.0)
    set(WORKING_DIRECTORY $<TARGET_FILE_DIR:alua>)
  elseif(IS_MULTI_CONFIG)
    set(WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
  else()
    set(WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  endif()

  add_subdirectory(test)
endif()
