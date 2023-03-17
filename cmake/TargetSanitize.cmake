get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)
include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)

function(string_append var)
  foreach(arg ${ARGN})
    string(FIND "${${var}}" "${arg}" index)
    if(${index} EQUAL -1)
      string(STRIP "${${var}} ${arg}" ${var})
    endif()
  endforeach()
  set(${var} "${${var}}" PARENT_SCOPE)
endfunction()

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
    string_append(SANITIZE_C_FLAGS ${arg})
    list_append(SANITIZE_CFLAGS ${arg})
    string_append(SANITIZE_CXX_FLAGS ${arg})
    list_append(SANITIZE_CXXFLAGS ${arg})
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
        string_append(SANITIZE_C_FLAGS ${arg})
        list_append(SANITIZE_CFLAGS ${arg})
      endif()
    endif()
    list(FIND ENABLED_LANGUAGES CXX index)
    if(${index} GREATER -1)
      check_cxx_compiler_flag(${arg} cxx${var})
      if(cxx${var})
        string_append(SANITIZE_CXX_FLAGS ${arg})
        list_append(SANITIZE_CXXFLAGS ${arg})
      endif()
    endif()
    set(var)
  endforeach()
  set(index)
endmacro()

macro(warnings_flag_ld)
  foreach(arg ${ARGN})
    string(REPLACE "+" "x" var ${arg})
    string(REGEX REPLACE "[^A-Za-z0-9_-]+" "-" var ${var})
    list(FIND ENABLED_LANGUAGES C index)
    if(${index} GREATER -1)
      check_c_compiler_flag(${arg} ld${var})
      if(ld${var})
        string_append(SANITIZE_LD_FLAGS ${arg})
        list_append(SANITIZE_LDFLAGS ${arg})
      endif()
    endif()
    list(FIND ENABLED_LANGUAGES CXX index)
    if(${index} GREATER -1)
      check_cxx_compiler_flag(${arg} ld${var})
      if(ld${var})
        string_append(SANITIZE_LD_FLAGS ${arg})
        list_append(SANITIZE_LDFLAGS ${arg})
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
    if(
      CMAKE_C_COMPILER_ID MATCHES "GNU" OR
      CMAKE_CXX_COMPILER_ID MATCHES "GNU"
    )
      warnings_flag_ld(-static-liblsan)
    endif()
  endif()
  if(
    CMAKE_C_COMPILER_ID MATCHES "GNU" OR
    CMAKE_CXX_COMPILER_ID MATCHES "GNU"
  )
    warnings_flag_ld(-static-libubsan)
  endif()
  if(
    CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang" OR
    CMAKE_C_COMPILER_ID MATCHES "IntelLLVM" OR
    CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang" OR
    CMAKE_CXX_COMPILER_ID MATCHES "IntelLLVM"
  )
    warnings_flag_ld(-static-libsan)
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
      target_compile_options(${target} ${scope} ${SANITIZE_CFLAGS} ${SANITIZE_CXXFLAGS})
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
      $<$<COMPILE_LANGUAGE:C>:${SANITIZE_CFLAGS}>
      $<$<COMPILE_LANGUAGE:CXX>:${SANITIZE_CXXFLAGS}>
    )
  endforeach()
endfunction()

function(target_link_sanitize_3_13)
  foreach(target ${ARGN})
    if(TARGET ${target})
      get_property(LINK_FLAGS TARGET ${target} PROPERTY LINK_FLAGS)
      string_append(LINK_FLAGS ${SANITIZE_CFLAGS} ${SANITIZE_CXXFLAGS} ${SANITIZE_LDFLAGS})
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
      $<$<COMPILE_LANGUAGE:C>:${SANITIZE_CFLAGS}>
      $<$<COMPILE_LANGUAGE:CXX>:${SANITIZE_CXXFLAGS}>
      ${SANITIZE_LDFLAGS}
    )
  endforeach()
endfunction()
