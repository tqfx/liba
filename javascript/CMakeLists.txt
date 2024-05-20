set(LIBA_JAVASCRIPT_SUFFIX ".js" CACHE STRING "The suffix for JavaScript output files.")
set_property(CACHE LIBA_JAVASCRIPT_SUFFIX PROPERTY STRINGS ".js" ".mjs" ".html" ".wasm")
set(CMAKE_EXECUTABLE_SUFFIX ${LIBA_JAVASCRIPT_SUFFIX})

if(NOT LIBA_CXX)
  enable_language(CXX)
endif()

if(NOT EMSCRIPTEN)
  include(../cmake/Emscripten.cmake)
  get_property(OBJECTS TARGET a PROPERTY SOURCES)
elseif(LIBA_SANITIZE)
  set(OBJECTS $<TARGET_OBJECTS:asan>)
else()
  set(OBJECTS $<TARGET_OBJECTS:a>)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ${LIBA_PIE})
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${LIBA_IPO})
file_scaner(SOURCES RECURSE src EXT c h cc hh cpp hpp)

if(NOT LIBA_CXX)
  file_scaner(source RECURSE ../src EXT cc hh cpp hpp)
  list(APPEND SOURCES ${source})
endif()

if(NOT DEFINED EMSDK_COMPILER_VERSION)
  set(EMSDK_COMPILER_VERSION ${CMAKE_CXX_COMPILER_VERSION})
endif()

# https://emscripten.org/docs/tools_reference/emcc.html
set(LIBA_EMCC_FLAGS "" CACHE STRING "Flags used by the emcc")
string_append(CMAKE_C_FLAGS ${LIBA_EMCC_FLAGS})
set(LIBA_EMXX_FLAGS "" CACHE STRING "Flags used by the em++")
string_append(CMAKE_CXX_FLAGS ${LIBA_EMXX_FLAGS})
set(LIBA_WASM_FLAGS "" CACHE STRING "Flags used by the linker")

set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
option(LIBA_JAVASCRIPT_TSGEN "Enable/Disable generation of TypeScript definition files" 0)
option(LIBA_JAVASCRIPT_ASYNC "Enable/Disable compilation of wasm async" 0)
option(LIBA_JAVASCRIPT_WASM "Enable/Disable JavaScript WebAssembly" 1)
option(LIBA_JAVASCRIPT_BIGINT "Enable/Disable JavaScript BigInt" 0)

if(NOT EMSCRIPTEN_VERSION VERSION_LESS 3.1.3)
  string(REPLACE "T> <" "T> -lembind <" CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_LINK_EXECUTABLE}")
  string(REPLACE "T> <" "T> -lembind <" CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
else()
  string(REPLACE "T> <" "T> --bind <" CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_LINK_EXECUTABLE}")
  string(REPLACE "T> <" "T> --bind <" CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
endif()

if(LIBA_SANITIZE)
  string_append(CMAKE_C_LINK_EXECUTABLE -fsanitize=address,leak,undefined
    -fno-omit-frame-pointer -fsanitize-recover=all -sALLOW_MEMORY_GROWTH
  )
  string_append(CMAKE_CXX_LINK_EXECUTABLE -fsanitize=address,leak,undefined
    -fno-omit-frame-pointer -fsanitize-recover=all -sALLOW_MEMORY_GROWTH
  )
endif()

if(LIBA_JAVASCRIPT_TSGEN)
  if(EMSCRIPTEN_VERSION VERSION_LESS 3.1.57)
    string_append(CMAKE_C_LINK_EXECUTABLE --embind-emit-tsd liba.gen.d.ts)
    string_append(CMAKE_CXX_LINK_EXECUTABLE --embind-emit-tsd liba.gen.d.ts)
  else()
    string_append(CMAKE_C_LINK_EXECUTABLE --emit-tsd liba.gen.d.ts)
    string_append(CMAKE_CXX_LINK_EXECUTABLE --emit-tsd liba.gen.d.ts)
  endif()
endif()

if(NOT LIBA_JAVASCRIPT_ASYNC)
  string_append(CMAKE_C_LINK_EXECUTABLE -sWASM_ASYNC_COMPILATION=0)
  string_append(CMAKE_CXX_LINK_EXECUTABLE -sWASM_ASYNC_COMPILATION=0)
endif()

if(LIBA_JAVASCRIPT_BIGINT)
  string_append(CMAKE_C_LINK_EXECUTABLE -sWASM_BIGINT)
  string_append(CMAKE_CXX_LINK_EXECUTABLE -sWASM_BIGINT)
  set_property(SOURCE ${SOURCES} APPEND PROPERTY
    COMPILE_DEFINITIONS WASM_BIGINT
  )
endif()

if(NOT LIBA_JAVASCRIPT_WASM)
  string_append(CMAKE_C_LINK_EXECUTABLE -sWASM=0)
  string_append(CMAKE_CXX_LINK_EXECUTABLE -sWASM=0)
endif()

string_append(CMAKE_C_LINK_EXECUTABLE ${LIBA_WASM_FLAGS})
string_append(CMAKE_CXX_LINK_EXECUTABLE ${LIBA_WASM_FLAGS})

add_executable(ajs ${OBJECTS} ${SOURCES})
target_compile_definitions(ajs PRIVATE $<TARGET_PROPERTY:a,COMPILE_DEFINITIONS>)
target_include_directories(ajs PRIVATE $<TARGET_PROPERTY:a,INCLUDE_DIRECTORIES>)
set_target_properties(ajs PROPERTIES OUTPUT_NAME ${PROJECT_NAME}
  RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_LIST_DIR}
  RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_LIST_DIR}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}
)

if(NOT CMAKE_VERSION VERSION_LESS 3.3 AND LIBA_WARNINGS AND UNIX)
  target_compile_options(ajs PRIVATE -Weverything -Wno-documentation
    -Wno-documentation-unknown-command -Wno-used-but-marked-unused
    $<$<COMPILE_LANGUAGE:C>:-Wno-declaration-after-statement>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-c++98-compat-pedantic>
  )

  if(NOT EMSDK_COMPILER_VERSION VERSION_LESS 16)
    target_compile_options(ajs PRIVATE -Wno-unsafe-buffer-usage)
  endif()
endif()

if(LIBA_SANITIZE)
  target_compile_options(ajs PRIVATE -fsanitize=address,leak,undefined
    -fno-omit-frame-pointer -fsanitize-recover=all
  )
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/test/CMakeLists.txt AND
  CMAKE_CROSSCOMPILING_EMULATOR)
  add_subdirectory(test)
endif()
