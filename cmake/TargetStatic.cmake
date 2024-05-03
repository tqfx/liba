get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)
include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)

if(NOT CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL .lib)
  list(FIND ENABLED_LANGUAGES C index)
  if(${index} GREATER -1)
    set(CMAKE_REQUIRED_FLAGS -static-libgcc)
    check_c_compiler_flag(-static-libgcc ld-static-libgcc)
    set(CMAKE_REQUIRED_FLAGS)
  endif()
  set(index)
endif()

if(NOT CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL .lib)
  list(FIND ENABLED_LANGUAGES CXX index)
  if(${index} GREATER -1)
    set(CMAKE_REQUIRED_FLAGS -static-libstdc++)
    check_cxx_compiler_flag(-static-libstdc++ ld-static-libstdcxx)
    set(CMAKE_REQUIRED_FLAGS)
  endif()
  set(index)
endif()

function(target_link_static_3_13)
  function(string_append var)
    foreach(arg ${ARGN})
      string(FIND "${${var}}" "${arg}" index)
      if(${index} EQUAL -1)
        string(STRIP "${${var}} ${arg}" ${var})
      endif()
    endforeach()
    set(${var} "${${var}}" PARENT_SCOPE)
  endfunction()
  foreach(target ${ARGN})
    if(TARGET ${target})
      get_property(LINK_FLAGS TARGET ${target} PROPERTY LINK_FLAGS)
      if(ld-static-libgcc)
        string_append(LINK_FLAGS -static-libgcc)
      endif()
      if(ld-static-libstdcxx)
        string_append(LINK_FLAGS -static-libstdc++)
      endif()
      set_property(TARGET ${target} PROPERTY LINK_FLAGS "${LINK_FLAGS}")
    endif()
  endforeach()
endfunction()

function(target_link_static_3_15)
  foreach(target ${ARGN})
    if(TARGET ${target})
      set_property(TARGET ${target} PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
      )
    endif()
  endforeach()
endfunction()

function(target_link_static)
  if(CMAKE_VERSION VERSION_LESS 3.13)
    target_link_static_3_13(${ARGN})
    return()
  endif()
  if(NOT CMAKE_VERSION VERSION_LESS 3.15)
    target_link_static_3_15(${ARGN})
  endif()
  set(scope PRIVATE)
  foreach(target ${ARGN})
    if(target MATCHES "^INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()
    if(ld-static-libgcc)
      target_link_options(${target} ${scope} -static-libgcc)
    endif()
    if(ld-static-libstdcxx)
      target_link_options(${target} ${scope} $<$<COMPILE_LANGUAGE:CXX>:-static-libstdc++>)
    endif()
  endforeach()
endfunction()