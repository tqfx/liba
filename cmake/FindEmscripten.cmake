include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_program(NODE_JS_EXECUTABLE NAMES nodejs node HINTS ENV EMSDK_NODE)
mark_as_advanced(NODE_JS_EXECUTABLE)
find_program(EMSDK_EXECUTABLE NAMES emsdk HINTS ENV EMSDK)
mark_as_advanced(EMSDK_EXECUTABLE)

if(EXISTS "${EMSDK_EXECUTABLE}")
  get_filename_component(EMSDK ${EMSDK_EXECUTABLE} DIRECTORY)
endif()

if(CMAKE_HOST_WIN32)
  set(EMCC_SUFFIX .bat)
else()
  set(EMCC_SUFFIX)
endif()

find_program(EMCC_EXECUTABLE NAMES emcc${EMCC_SUFFIX} HINTS ${EMSDK}/upstream/emscripten)
mark_as_advanced(EMCC_EXECUTABLE)

find_program(EMXX_EXECUTABLE NAMES em++${EMCC_SUFFIX} HINTS ${EMSDK}/upstream/emscripten)
mark_as_advanced(EMXX_EXECUTABLE)

find_program(EMAR_EXECUTABLE NAMES emar${EMCC_SUFFIX} HINTS ${EMSDK}/upstream/emscripten)
mark_as_advanced(EMAR_EXECUTABLE)

find_program(EMRANLIB_EXECUTABLE NAMES emranlib${EMCC_SUFFIX} HINTS ${EMSDK}/upstream/emscripten)
mark_as_advanced(EMRANLIB_EXECUTABLE)

if(EXISTS "${EMCC_EXECUTABLE}")
  execute_process(COMMAND ${EMCC_EXECUTABLE} -v ERROR_VARIABLE EMSCRIPTEN_VERSION OUTPUT_QUIET)
  string(REGEX REPLACE "emcc \\(.*\\) ([^ ]+).*" "\\1" EMSCRIPTEN_VERSION "${EMSCRIPTEN_VERSION}")
endif()

find_program(EM_CONFIG_EXECUTABLE NAMES em-config${EMCC_SUFFIX} HINTS ${EMSDK}/upstream/emscripten)
mark_as_advanced(EM_CONFIG_EXECUTABLE)
if(EXISTS "${EM_CONFIG_EXECUTABLE}")
  execute_process(COMMAND ${EM_CONFIG_EXECUTABLE} CACHE
    OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE EMSCRIPTEN_SYSROOT
  )
  file(TO_CMAKE_PATH "${EMSCRIPTEN_SYSROOT}" EMSCRIPTEN_SYSROOT)
  set(EMSCRIPTEN_SYSROOT "${EMSCRIPTEN_SYSROOT}/sysroot")
endif()

find_package_handle_standard_args(Emscripten
  FOUND_VAR
    EMSCRIPTEN_FOUND
  REQUIRED_VARS
    EMCC_EXECUTABLE
    EMXX_EXECUTABLE
    EMAR_EXECUTABLE
  VERSION_VAR
    EMSCRIPTEN_VERSION
)
