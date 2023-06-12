if(NOT EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX .js)
  set(CMAKE_C_COMPILER ${EMCC_EXECUTABLE})
  set(CMAKE_CXX_COMPILER ${EMXX_EXECUTABLE})
  set(CMAKE_C_COMPILER_AR ${EMAR_EXECUTABLE})
  set(CMAKE_CXX_COMPILER_AR ${EMAR_EXECUTABLE})
  set(CMAKE_C_COMPILER_RANLIB ${EMRANLIB_EXECUTABLE})
  set(CMAKE_CXX_COMPILER_RANLIB ${EMRANLIB_EXECUTABLE})
  set(CMAKE_CROSSCOMPILING_EMULATOR ${NODE_JS_EXECUTABLE})
  list(FIND CMAKE_C_COMPILER_PREDEFINES_COMMAND -m64 emcc)

  if(${emcc} GREATER 0)
    unset(CMAKE_C_COMPILER_ARG${emcc} CACHE)
    unset(CMAKE_C_COMPILER_ARG${emcc})
  endif()

  list(FIND CMAKE_CXX_COMPILER_PREDEFINES_COMMAND -m64 emxx)

  if(${emxx} GREATER 0)
    unset(CMAKE_CXX_COMPILER_ARG${emxx} CACHE)
    unset(CMAKE_CXX_COMPILER_ARG${emxx})
  endif()
endif()

if(NOT DEFINED EMSDK_COMPILER_VERSION)
  set(EMSDK_COMPILER_VERSION ${CMAKE_C_COMPILER_VERSION})
endif()

if(EMSCRIPTEN)
  set(OBJECTS $<TARGET_OBJECTS:a>)
else()
  get_property(OBJECTS TARGET a PROPERTY SOURCES)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ${LIBA_PIE})
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${LIBA_IPO})
file_scaner(SOURCES RECURSE src EXT c h cc hh cpp hpp)

# https://emscripten.org/docs/tools_reference/emcc.html
string_append(LDFLAGS -sSINGLE_FILE=1 -sWASM=0)
string_append(LDFLAGS -sWASM_ASYNC_COMPILATION=0)
string_append(LDFLAGS -sEXPORTED_RUNTIME_METHODS=ccall,cwrap)

add_executable(ajs ${OBJECTS} ${SOURCES})
target_compile_definitions(ajs PRIVATE $<TARGET_PROPERTY:a,COMPILE_DEFINITIONS>)
target_include_directories(ajs PRIVATE $<TARGET_PROPERTY:a,INCLUDE_DIRECTORIES>)
set_target_properties(ajs PROPERTIES LINK_FLAGS ${LDFLAGS} OUTPUT_NAME liba)
target_link_libraries(ajs PRIVATE embind)

if(NOT CMAKE_VERSION VERSION_LESS 3.3 AND LIBA_WARNINGS)
  target_compile_options(ajs PRIVATE -Weverything -Wno-documentation
    -Wno-documentation-unknown-command -Wno-used-but-marked-unused
    $<$<COMPILE_LANGUAGE:C>:-Wno-declaration-after-statement>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-c++98-compat-pedantic>
  )

  if(NOT EMSDK_COMPILER_VERSION VERSION_LESS 16)
    target_compile_options(ajs PRIVATE -Wno-unsafe-buffer-usage)
  endif()
endif()

if(CMAKE_CROSSCOMPILING_EMULATOR)
  get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

  if(NOT CMAKE_VERSION VERSION_LESS 3.0)
    set(WORKING_DIRECTORY $<TARGET_FILE_DIR:ajs>)
  elseif(IS_MULTI_CONFIG)
    set(WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
  else()
    set(WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  endif()

  add_subdirectory(test)
endif()
