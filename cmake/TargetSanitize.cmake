get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)
include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)

function(list_append var)
  foreach(arg ${ARGN})
    list(FIND ${var} ${arg} index)
    if(${index} EQUAL -1)
      list(APPEND ${var} ${arg})
    endif()
  endforeach()
  set(${var} ${${var}} PARENT_SCOPE)
endfunction()

macro(sanitize_flag)
  foreach(arg ${ARGN})
    list_append(SANITIZE_CC ${arg})
    list_append(SANITIZE_XX ${arg})
  endforeach()
endmacro()

macro(sanitize_flag_cx)
  foreach(arg ${ARGN})
    string(REPLACE "+" "x" var ${arg})
    string(REGEX REPLACE "[^A-Za-z0-9_-]+" "-" var ${var})
    list(FIND ENABLED_LANGUAGES C index)
    if(${index} GREATER -1)
      check_c_compiler_flag(${arg} cc${var})
      if(cc${var})
        list_append(SANITIZE_CC ${arg})
      endif()
    endif()
    list(FIND ENABLED_LANGUAGES CXX index)
    if(${index} GREATER -1)
      check_cxx_compiler_flag(${arg} xx${var})
      if(xx${var})
        list_append(SANITIZE_XX ${arg})
      endif()
    endif()
    set(var)
  endforeach()
  set(index)
endmacro()

macro(sanitize_flag_ld)
  foreach(arg ${ARGN})
    string(REPLACE "+" "x" var ${arg})
    string(REGEX REPLACE "[^A-Za-z0-9_-]+" "-" var ${var})
    list(FIND ENABLED_LANGUAGES CXX index)
    if(${index} GREATER -1)
      check_cxx_compiler_flag(${arg} ld${var})
      if(ld${var})
        list_append(SANITIZE_LD ${arg})
      endif()
    endif()
    list(FIND ENABLED_LANGUAGES C index)
    if(${index} GREATER -1)
      check_c_compiler_flag(${arg} ld${var})
      if(ld${var})
        list_append(SANITIZE_LD ${arg})
      endif()
    endif()
    set(var)
  endforeach()
  set(index)
endmacro()

if(
  CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang" OR
  CMAKE_C_COMPILER_ID MATCHES "IntelLLVM" OR
  CMAKE_C_COMPILER_ID MATCHES "GNU" OR
  CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang" OR
  CMAKE_CXX_COMPILER_ID MATCHES "IntelLLVM" OR
  CMAKE_CXX_COMPILER_ID MATCHES "GNU"
)
  sanitize_flag(-fsanitize=address)
  sanitize_flag_cx(-fsanitize=undefined)
  sanitize_flag_cx(-fno-omit-frame-pointer)
  sanitize_flag_cx(-fsanitize-recover=address)
  if(NOT(
    CMAKE_C_COMPILER_ID MATCHES "Apple[Cc]lang" OR
    CMAKE_CXX_COMPILER_ID MATCHES "Apple[Cc]lang"
    ))
    sanitize_flag_cx(-fsanitize=leak)
  endif()
  if(
    CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang" OR
    CMAKE_C_COMPILER_ID MATCHES "IntelLLVM" OR
    CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang" OR
    CMAKE_CXX_COMPILER_ID MATCHES "IntelLLVM"
  )
    sanitize_flag_ld(-static-libsan)
  endif()
elseif(
  CMAKE_C_COMPILER_ID MATCHES "MSVC" OR
  CMAKE_CXX_COMPILER_ID MATCHES "MSVC"
)
  sanitize_flag_cx(/fsanitize=address)
endif()

function(target_compile_sanitize_3_3)
  foreach(target ${ARGN})
    if(TARGET ${target})
      target_compile_options(${target} ${scope} ${SANITIZE_CC} ${SANITIZE_XX})
    endif()
  endforeach()
endfunction()

function(target_compile_sanitize)
  set(scope PRIVATE)
  if(CMAKE_VERSION VERSION_LESS 3.3)
    target_compile_sanitize_3_3(${ARGN})
    return()
  endif()
  foreach(target ${ARGN})
    if(target MATCHES "^INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()
    target_compile_options(${target} ${scope}
      $<$<COMPILE_LANGUAGE:C>:${SANITIZE_CC}>
      $<$<COMPILE_LANGUAGE:CXX>:${SANITIZE_XX}>
    )
  endforeach()
endfunction()

function(target_link_sanitize_3_13)
  foreach(target ${ARGN})
    if(TARGET ${target})
      get_property(LINK_FLAGS TARGET ${target} PROPERTY LINK_FLAGS)
      string_append(LINK_FLAGS ${SANITIZE_CC} ${SANITIZE_XX} ${SANITIZE_LD})
      set_property(TARGET ${target} PROPERTY LINK_FLAGS "${LINK_FLAGS}")
    endif()
  endforeach()
endfunction()

function(target_link_sanitize)
  if(MSVC)
    return()
  endif()
  if(CMAKE_VERSION VERSION_LESS 3.13)
    target_link_sanitize_3_13(${ARGN})
    return()
  endif()
  set(scope PRIVATE)
  foreach(target ${ARGN})
    if(target MATCHES "^INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
      continue()
    endif()
    target_link_options(${target} ${scope}
      $<$<COMPILE_LANGUAGE:C>:${SANITIZE_CC}>
      $<$<COMPILE_LANGUAGE:CXX>:${SANITIZE_XX}>
      ${SANITIZE_LD}
    )
  endforeach()
endfunction()
