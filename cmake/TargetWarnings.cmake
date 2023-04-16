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

macro(warnings_flag_cc)
  foreach(arg ${ARGN})
    string(REPLACE "+" "x" var ${arg})
    string(REGEX REPLACE "[^A-Za-z0-9_-]+" "-" var ${var})
    list(FIND ENABLED_LANGUAGES C index)
    if(${index} GREATER -1)
      check_c_compiler_flag(${arg} cc${var})
      if(cc${var})
        string_append(WARNINGS_C_FLAGS ${arg})
        list_append(WARNINGS_CFLAGS ${arg})
      endif()
    endif()
    set(var)
  endforeach()
  set(index)
endmacro()

macro(warnings_flag_xx)
  foreach(arg ${ARGN})
    string(REPLACE "+" "x" var ${arg})
    string(REGEX REPLACE "[^A-Za-z0-9_-]+" "-" var ${var})
    list(FIND ENABLED_LANGUAGES CXX index)
    if(${index} GREATER -1)
      check_cxx_compiler_flag(${arg} cxx${var})
      if(cxx${var})
        string_append(WARNINGS_CXX_FLAGS ${arg})
        list_append(WARNINGS_CXXFLAGS ${arg})
      endif()
    endif()
    set(var)
  endforeach()
  set(index)
endmacro()

macro(warnings_flag_cx)
  foreach(arg ${ARGN})
    string(REPLACE "+" "x" var ${arg})
    string(REGEX REPLACE "[^A-Za-z0-9_-]+" "-" var ${var})
    list(FIND ENABLED_LANGUAGES C index)
    if(${index} GREATER -1)
      check_c_compiler_flag(${arg} cc${var})
      if(cc${var})
        string_append(WARNINGS_C_FLAGS ${arg})
        list_append(WARNINGS_CFLAGS ${arg})
      endif()
    endif()
    list(FIND ENABLED_LANGUAGES CXX index)
    if(${index} GREATER -1)
      check_cxx_compiler_flag(${arg} cxx${var})
      if(cxx${var})
        string_append(WARNINGS_CXX_FLAGS ${arg})
        list_append(WARNINGS_CXXFLAGS ${arg})
      endif()
    endif()
    set(var)
  endforeach()
  set(index)
endmacro()

if(CMAKE_C_COMPILER_ID MATCHES "(ARM|Apple)?[Cc]lang" OR CMAKE_C_COMPILER_ID MATCHES "IntelLLVM" OR
  CMAKE_CXX_COMPILER_ID MATCHES "(ARM|Apple)?[Cc]lang" OR CMAKE_CXX_COMPILER_ID MATCHES "IntelLLVM")
  # https://releases.llvm.org/4.0.1/tools/clang/DiagnosticsReference.html
  # https://clang.llvm.org/docs/DiagnosticsReference.html
  warnings_flag_cx(-Weverything)
  warnings_flag_cc(-Wno-declaration-after-statement)
  warnings_flag_xx(-Wno-c++98-compat-pedantic)
  warnings_flag_cx(-Wno-unsafe-buffer-usage)
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  # https://gcc.gnu.org/onlinedocs/gcc-3.0.3/gcc/Warning-Options.html
  # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
  warnings_flag_cx(-pedantic -Wall)
  warnings_flag_cx(-Wextra) # 3.4+
  warnings_flag_xx(-Weffc++) # 2.95+
  warnings_flag_cc(-Winit-self) # 3.4+
  warnings_flag_cc(-Wc++-compat) # 4.1+
  warnings_flag_cc(-Wbad-function-cast) # 2.95+
  warnings_flag_cc(-Wstrict-prototypes) # 2.95+
  warnings_flag_cc(-Wold-style-definition) # 3.4+
  warnings_flag_cc(-Wmissing-prototypes) # 2.95+
  warnings_flag_cc(-Wnested-externs) # 2.95+
  warnings_flag_cx(-Wdouble-promotion) # 4.6+
  warnings_flag_cx(-Wnull-dereference) # 6.1+
  warnings_flag_cx(-Wmissing-include-dirs) # 4.0+
  warnings_flag_cx(-Wswitch-default) # 3.3+
  warnings_flag_cx(-Wswitch-enum) # 3.3+
  warnings_flag_cx(-Walloca) # 7.1+
  warnings_flag_cx(-Wattributes) # 4.1+
  warnings_flag_cx(-Wfloat-equal) # 3.0+
  warnings_flag_cx(-Wshadow) # 2.95+
  warnings_flag_cx(-Wundef) # 2.95+
  warnings_flag_cx(-Wunused) # 2.95+
  warnings_flag_cx(-Wunused-macros) # 7.1+
  warnings_flag_cx(-Wcast-qual) # 2.95+
  warnings_flag_cx(-Wcast-align) # 2.95+
  warnings_flag_cx(-Wconversion) # 2.95+
  warnings_flag_cx(-Wdate-time) # 4.9+
  warnings_flag_cx(-Waggregate-return) # 2.95+
  warnings_flag_cx(-Wmissing-declarations) # 2.95+
  warnings_flag_cx(-Wpacked) # 3.0+
  warnings_flag_cx(-Wpadded) # 3.0+
  warnings_flag_cx(-Wredundant-decls) # 2.95+
  warnings_flag_cx(-Winline) # 2.95+
  warnings_flag_cx(-Winvalid-pch) # 3.4+
  warnings_flag_cx(-Wdisabled-optimization) # 3.0+
  warnings_flag_cx(-Wstack-protector) # 4.1+
  warnings_flag_cx(-Wstringop-overflow) # 7.1+
  warnings_flag_cx(-Wstringop-truncation) # 8.1+
  warnings_flag_cx(-Walloc-zero) # 7.1+
  warnings_flag_cx(-Wduplicated-branches) # 7.1+
  warnings_flag_cx(-Wduplicated-cond) # 6.1+
  warnings_flag_cx(-Wzero-length-bounds) # 10.1+
  warnings_flag_cx(-Wtrampolines) # 4.6+
  warnings_flag_cx(-Wunsafe-loop-optimizations) # 4.1+
  warnings_flag_cx(-Wno-pedantic-ms-format) # 4.4+
  warnings_flag_cx(-Wlogical-op) # 4.3+
elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC" OR CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  # https://learn.microsoft.com/cpp/error-messages/compiler-warnings
  warnings_flag_cx(/sdl /Wall)
  warnings_flag_cx(/wd4464) # relative include path contains '..'
  warnings_flag_cx(/wd4514) # 'function' : unreferenced inline function has been removed
  warnings_flag_cx(/wd4710) # 'function' : function not inlined
  warnings_flag_cx(/wd4711) # function 'function' selected for inline expansion
  warnings_flag_cx(/wd4820) # 'bytes' bytes padding added after construct 'member_name'
  if(MSVC_VERSION GREATER 1911) # 15.5
    warnings_flag_cx(/wd5039) # 'function': pointer or reference to potentially throwing function passed to extern C function under -EHc
  endif()
  if(MSVC_VERSION GREATER 1913) # 15.7
    warnings_flag_cx(/wd5045) # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
  endif()
  if(MSVC_VERSION GREATER 1900) # 15.0
    warnings_flag_cx(/diagnostics:caret)
  endif()
elseif(CMAKE_C_COMPILER_ID MATCHES "TinyCC")
  # https://bellard.org/tcc/tcc-doc.html
  warnings_flag_cc(-Wall -Wunsupported)
  warnings_flag_cc(-Wwrite-strings)
endif()

function(target_compile_warnings)
  if(CMAKE_VERSION VERSION_LESS 3.3)
    return()
  endif()
  foreach(target ${ARGN})
    target_compile_options(${target} PRIVATE
      $<$<COMPILE_LANGUAGE:C>:${WARNINGS_CFLAGS}>
      $<$<COMPILE_LANGUAGE:CXX>:${WARNINGS_CXXFLAGS}>
    )
  endforeach()
endfunction()
