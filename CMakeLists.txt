set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0063 NEW)
cmake_minimum_required(VERSION 2.8.12...4.0)
include(cmake/CMakeModulePath.cmake)
include(cmake/Languages.cmake)
project(liba ${LANGUAGES})
include(cmake/Project.cmake)
include(cmake/core/file.cmake)
include(cmake/core/string.cmake)
include(cmake/CMakeByteOrder.cmake)
include(cmake/CMakeBuildType.cmake)
include(cmake/EnabledLanguages.cmake)
include(cmake/TargetSupportsSharedLibs.cmake)
include(cmake/TargetSupportsExecutables.cmake)
include(cmake/TargetSupportsRelocatable.cmake)
include(cmake/TargetSupportsSymbolicLink.cmake)

option(LIBA_WARNINGS "Enable/Disable warnings" 0)

if(LIBA_WARNINGS)
  include(cmake/TargetWarnings.cmake)
endif()

option(LIBA_SANITIZE "Enable/Disable sanitize" 0)

if(LIBA_SANITIZE)
  include(cmake/TargetSanitize.cmake)
endif()

option(LIBA_STATIC "Enable/Disable static" 0)

if(LIBA_STATIC)
  include(cmake/CMakeFindLibraryStatic.cmake)
  include(cmake/TargetStatic.cmake)
endif()

option(LIBA_CCACHE "Enable/Disable ccache" 0)

if(LIBA_CCACHE)
  include(cmake/UseCCache.cmake)
endif()

if(UNIX)
  set(LIBA_MATH "m" CACHE FILEPATH "system math library")
else()
  set(LIBA_MATH "" CACHE FILEPATH "system math library")
endif()

set(A_SIZE_REAL 8 CACHE INTERNAL "real number bytes")
include(CheckLibraryExists)

function(check_math VARIABLE FUNCTION)
  get_filename_component(LOCATION "${LIBA_MATH}" DIRECTORY)
  list(APPEND CMAKE_REQUIRED_LIBRARIES ${LIBA_MATH})

  if(A_SIZE_REAL GREATER 8)
    set(FUNCTION ${FUNCTION}l)
  elseif(A_SIZE_REAL EQUAL 4)
    set(FUNCTION ${FUNCTION}f)
  endif()

  check_library_exists("${LIBA_MATH}"
    ${FUNCTION} "${LOCATION}" ${VARIABLE}
  )
endfunction()

include(CheckIncludeFile)
check_include_file(stdint.h A_HAVE_STDINT_H)
check_math(A_HAVE_HYPOT hypot)
check_math(A_HAVE_LOG1P log1p)
check_math(A_HAVE_ATAN2 atan2)
check_include_file(complex.h A_HAVE_COMPLEX_H)
check_math(A_HAVE_CSQRT csqrt)
check_math(A_HAVE_CPOW cpow)
check_math(A_HAVE_CEXP cexp)
check_math(A_HAVE_CLOG clog)
check_math(A_HAVE_CSIN csin)
check_math(A_HAVE_CCOS ccos)
check_math(A_HAVE_CTAN ctan)
check_math(A_HAVE_CSINH csinh)
check_math(A_HAVE_CCOSH ccosh)
check_math(A_HAVE_CTANH ctanh)
check_math(A_HAVE_CASIN casin)
check_math(A_HAVE_CACOS cacos)
check_math(A_HAVE_CATAN catan)
check_math(A_HAVE_CASINH casinh)
check_math(A_HAVE_CACOSH cacosh)
check_math(A_HAVE_CATANH catanh)

option(LIBA_PYTHON "Enable/Disable python" 0)

if(LIBA_PYTHON)
  find_package(Python COMPONENTS Interpreter)
  find_package(Cython)
endif()

option(LIBA_DOXYGEN "Enable/Disable doxygen" 0)

if(LIBA_DOXYGEN)
  find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
endif()

option(LIBA_CPPCHECK "Enable/Disable cppcheck" 0)

if(LIBA_CPPCHECK)
  find_package(cppcheck)
endif()

option(LIBA_CLANG_TIDY "Enable/Disable clang-tidy" 0)

if(LIBA_CLANG_TIDY)
  find_package(ClangTidy)
endif()

option(LIBA_IWYU "Enable/Disable include-what-you-use" 0)

if(LIBA_IWYU)
  find_package(IWYU)
endif()

option(LIBA_LTO "Enable/Disable interprocedural optimization" 0)

# https://cmake.org/cmake/help/latest/module/CheckIPOSupported.html
if(NOT CMAKE_VERSION VERSION_LESS 3.9 AND LIBA_LTO)
  cmake_policy(SET CMP0069 NEW)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT LIBA_LTO)
endif()

if(DEFINED ENV{ANDROID_ROOT} AND EXISTS $ENV{ANDROID_ROOT})
  option(LIBA_PIE "Enable/Disable position independent code" 1)
else()
  option(LIBA_PIE "Enable/Disable position independent code" 0)
endif()

# https://cmake.org/cmake/help/latest/module/CheckPIESupported.html
if(NOT CMAKE_VERSION VERSION_LESS 3.14)
  cmake_policy(SET CMP0083 NEW)
  include(CheckPIESupported)
  check_pie_supported()
endif()

function(set_library_options)
  if(LIBA_IWYU AND IWYU_FOUND)
    add_include_what_you_use(TARGETS ${ARGN})
  endif()

  if(LIBA_CLANG_TIDY AND CLANG_TIDY_FOUND)
    add_clang_tidy(TARGETS ${ARGN} OPTIONS --fix)
  endif()

  if(LIBA_CPPCHECK AND CPPCHECK_FOUND)
    add_cppcheck(TARGETS ${ARGN} OPTIONS --enable=warning,performance)
  endif()

  if(CMAKE_C_COMPILER_ID MATCHES "TinyCC" AND CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL .lib)
    set_property(TARGET ${ARGN} PROPERTY IMPORT_SUFFIX .def)
  endif()

  set_target_properties(${ARGN} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${LIBA_LTO}
    C_VISIBILITY_PRESET hidden CXX_VISIBILITY_PRESET hidden
  )

  if(LIBA_WARNINGS)
    target_compile_warnings(${ARGN})
  endif()
endfunction()

function(add_library_properties target scope source)
  target_compile_definitions(${target} ${scope} $<TARGET_PROPERTY:${source},${ARGV3}COMPILE_DEFINITIONS>)
  target_include_directories(${target} ${scope} $<TARGET_PROPERTY:${source},${ARGV3}INCLUDE_DIRECTORIES>)

  if(${scope} MATCHES "PUBLIC|PRIVATE")
    set_property(TARGET ${target} APPEND PROPERTY LINK_LIBRARIES $<TARGET_PROPERTY:${source},${ARGV3}LINK_LIBRARIES>)
  endif()

  if(${scope} MATCHES "PUBLIC|INTERFACE")
    set_property(TARGET ${target} APPEND PROPERTY INTERFACE_LINK_LIBRARIES $<TARGET_PROPERTY:${source},${ARGV3}LINK_LIBRARIES>)
  endif()
endfunction()

option(LIBA_MIMALLOC "Enable/Disable override using mimalloc" 0)
set(A_HAVE_MIMALLOC_H)

if(LIBA_MIMALLOC)
  find_package(mimalloc)
endif()

if(mimalloc_FOUND)
  set(A_HAVE_MIMALLOC_H 1)
endif()

find_package(Git)

if(GIT_COMMIT_DATE)
  set(PROJECT_VERSION_TWEAK ${GIT_COMMIT_DATE})
  set(${PROJECT_NAME}_VERSION_TWEAK ${GIT_COMMIT_DATE})
else()
  string(TIMESTAMP PROJECT_VERSION_TWEAK %Y%m%d%H%M)
  string(TIMESTAMP ${PROJECT_NAME}_VERSION_TWEAK %Y%m%d%H%M)
endif()

if(NOT EXISTS "${A_HAVE_H}")
  set(A_HAVE_H ${CMAKE_CURRENT_BINARY_DIR}/a.cmake.h)
  configure_file(${CMAKE_CURRENT_LIST_DIR}/include/a.cmake.h.in ${A_HAVE_H})
endif()

if(IS_ABSOLUTE "${LIBA_MATH}")
  get_filename_component(math ${LIBA_MATH} NAME_WE)
  string(REGEX REPLACE "^${CMAKE_STATIC_LIBRARY_PREFIX}(.+)" "\\1" math "${math}")
  set(LIBA_MATH $<BUILD_INTERFACE:${LIBA_MATH}> $<INSTALL_INTERFACE:${math}>)
  set(math)
endif()

if(TARGET_SUPPORTS_SYMBOLIC_LINK)
  option(LIBA_SYMLINK "Enable/Disable symbolic link" 1)
endif()

function(set_library_compile target)
  if(EXISTS "${A_HAVE_H}")
    file(RELATIVE_PATH a_have_h ${CMAKE_CURRENT_LIST_DIR}/include ${A_HAVE_H})
    target_compile_definitions(${target} PUBLIC $<BUILD_INTERFACE:A_HAVE_H="${a_have_h}">)
    set(a_have_h)
  endif()

  if((LIBA_SYMLINK OR WIN32) AND TARGET_SUPPORTS_SYMBOLIC_LINK)
    set_target_properties(${target} PROPERTIES SOVERSION
      ${PROJECT_VERSION_MAJOR} VERSION ${PROJECT_VERSION}
    )
  endif()

  set_target_properties(${target} PROPERTIES OUTPUT_NAME a
    POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL A_EXPORTS
  )
  target_compile_definitions(${target} PRIVATE A_EXPORTS)
  target_include_directories(${target} BEFORE PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  get_property(TYPE TARGET ${target} PROPERTY TYPE)

  if(${TYPE} MATCHES "(STATIC|SHARED|MODULE)_LIBRARY")
    target_link_libraries(${target} PUBLIC ${LIBA_MATH})
  endif()

  set_library_options(${target})
endfunction()

file_scaner(SOURCES RECURSE include src)
add_library(a OBJECT ${SOURCES})
set_library_compile(a)

if(A_HAVE_MIMALLOC_H AND CMAKE_VERSION VERSION_LESS 3.12)
  add_library_properties(a PUBLIC mimalloc-static INTERFACE_)
elseif(A_HAVE_MIMALLOC_H)
  target_link_libraries(a PUBLIC mimalloc-static)
endif()

if(TARGET_SUPPORTS_RELOCATABLE)
  add_subdirectory(src)
endif()

set(INSTALL_TARGETS alib)
add_library(alib $<TARGET_OBJECTS:a>)
set_library_compile(alib)

if(A_HAVE_MIMALLOC_H)
  target_link_libraries(alib PUBLIC mimalloc-static)
endif()

if(TARGET_SUPPORTS_SHARED_LIBS)
  if(BUILD_SHARED_LIBS)
    set(module STATIC)
    set(shared alib)
  else()
    set(module SHARED)
    set(shared liba)
  endif()

  list(APPEND INSTALL_TARGETS liba)
  add_library(liba ${module} $<TARGET_OBJECTS:a>)
  set_library_compile(liba)

  if(A_HAVE_MIMALLOC_H)
    target_link_libraries(liba PUBLIC mimalloc-static)
  endif()

  if(CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL .lib)
    set_property(TARGET ${shared} PROPERTY OUTPUT_NAME liba)
  endif()

  target_compile_definitions(${shared} INTERFACE A_IMPORTS)

  if(LIBA_STATIC)
    target_link_static(${shared})
  endif()
endif()

if(LIBA_SANITIZE)
  add_library(asan OBJECT ${SOURCES})
  set_library_compile(asan)
  target_compile_sanitize(asan)

  if(A_HAVE_MIMALLOC_H AND CMAKE_VERSION VERSION_LESS 3.12)
    add_library_properties(asan PUBLIC mimalloc INTERFACE_)
  elseif(A_HAVE_MIMALLOC_H)
    target_link_libraries(asan PUBLIC mimalloc)
  endif()

  if(TARGET_SUPPORTS_SHARED_LIBS)
    add_library(libasan SHARED $<TARGET_OBJECTS:asan>)
    set_library_compile(libasan)

    set_property(TARGET libasan PROPERTY OUTPUT_NAME a.san)
    target_compile_definitions(libasan INTERFACE A_IMPORTS)
    target_link_sanitize(libasan)

    if(A_HAVE_MIMALLOC_H)
      target_link_libraries(libasan PUBLIC mimalloc)
    endif()

    if(LIBA_STATIC)
      target_link_static(libasan)
    endif()
  endif()
endif()

include(cmake/InstallTargets.cmake)
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/a DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if(EXISTS "${A_HAVE_H}")
  install(FILES ${A_HAVE_H} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/a)
  install_fixup(${CMAKE_INSTALL_INCLUDEDIR}/a/a.h A_HAVE_H ${A_HAVE_H})
endif()

option(LIBA_PKGCONFIG "Enable/Disable pkgconfig" 0)

if(LIBA_PKGCONFIG)
  include(cmake/InstallPkgConfig.cmake)
  install_pkgconfig(${PROJECT_NAME} alib)
endif()

option(LIBA_LIBTOOL "Enable/Disable libtool" 0)

if(LIBA_LIBTOOL)
  include(cmake/InstallLibtool.cmake)
  install_libtool(${INSTALL_TARGETS})
endif()

option(LIBA_VCPKG "Enable/Disable vcpkg" 0)

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/vcpkg AND LIBA_VCPKG AND GIT_COMMIT)
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vcpkg DESTINATION ${CMAKE_INSTALL_DATADIR})
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/portfile.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/vcpkg/ports/${PROJECT_NAME}/portfile.cmake
    @ONLY
  )
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg.json
    ${CMAKE_CURRENT_BINARY_DIR}/vcpkg/ports/${PROJECT_NAME}/vcpkg.json
    @ONLY
  )
endif()

if(PROJECT_IS_TOP_LEVEL)
  add_custom_target(afmt)
  add_custom_target(adoc)
  include(CTest)
endif()

if(NOT CMAKE_FIND_LIBRARY_PREFIXES)
  set(CMAKE_FIND_LIBRARY_PREFIXES ";lib")
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/java/CMakeLists.txt)
  option(LIBA_JAVA "Enable/Disable java" 0)

  if(LIBA_JAVA)
    find_package(Java)
    find_package(JNI)
  endif()

  if(LIBA_JAVA AND Java_FOUND)
    add_subdirectory(java)
  endif()
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/javascript/CMakeLists.txt)
  if(EMSCRIPTEN)
    option(LIBA_JAVASCRIPT "Enable/Disable javascript" 1)
  else()
    option(LIBA_JAVASCRIPT "Enable/Disable javascript" 0)
  endif()

  if(LIBA_JAVASCRIPT)
    if(NOT EMSCRIPTEN)
      find_package(Emscripten)
    endif()

    if(EMSCRIPTEN OR EMSCRIPTEN_FOUND)
      add_subdirectory(javascript)
    endif()
  endif()
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/lua/CMakeLists.txt)
  option(LIBA_LUA "Enable/Disable lua" 0)
  option(LIBA_LUAJIT "Enable/Disable luajit" 0)
  option(WITH_LUA "Enable/Disable build with lua" 0)

  if(WITH_LUA OR LIBA_LUA OR LIBA_LUAJIT)
    add_subdirectory(lua)
  endif()
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/python/CMakeLists.txt)
  if(LIBA_PYTHON AND PYTHON_FOUND)
    add_subdirectory(python)
  endif()
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/quickjs/CMakeLists.txt)
  option(LIBA_QJS "Enable/Disable quickjs" 0)

  if(LIBA_QJS)
    find_package(QuickJS)
  endif()

  if(LIBA_QJS AND QUICKJS_FOUND)
    add_subdirectory(quickjs)
  endif()
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/swig/CMakeLists.txt)
  option(LIBA_SWIG "Enable/Disable swig" 0)

  if(LIBA_SWIG)
    if(POLICY CMP0078) # 3.13
      cmake_policy(SET CMP0078 NEW)
    endif() # UseSWIG_TARGET_NAME_PREFERENCE

    if(POLICY CMP0086) # 3.14
      cmake_policy(SET CMP0086 NEW)
    endif() # SWIG_MODULE_NAME

    find_package(SWIG)
  endif()

  if(LIBA_SWIG AND SWIG_FOUND)
    add_subdirectory(swig)
  endif()
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/test/CMakeLists.txt)
  if(PROJECT_IS_TOP_LEVEL AND BUILD_TESTING)
    add_subdirectory(test)
  endif()
endif()

set(CPACK_SOURCE_IGNORE_FILES
  ${CMAKE_CURRENT_LIST_DIR}/.git
  ${CMAKE_CURRENT_LIST_DIR}/.cache
  ${CMAKE_CURRENT_LIST_DIR}/.vscode
  ${CMAKE_CURRENT_LIST_DIR}/.github
  ${CMAKE_CURRENT_LIST_DIR}/.gitignore
  ${CMAKE_CURRENT_LIST_DIR}/.gitmodules
  ${CMAKE_CURRENT_LIST_DIR}/.gitattributes
  ${PROJECT_BINARY_DIR}
)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_LIST_DIR}/README.md)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_LIST_DIR}/LICENSE.txt)
include(CPack)

if(PROJECT_IS_TOP_LEVEL)
  find_package(ClangFormat)
  find_package(Black)
endif()

if(CLANG_FORMAT_FOUND)
  file_scaner(SOURCES RECURSE include src test java/src javascript/src lua/src quickjs/src)
  add_clang_format(aformat VERBOSE ${SOURCES})
  add_dependencies(afmt aformat)
endif()

if(BLACK_FOUND)
  add_black(ablack ${CMAKE_CURRENT_LIST_DIR})
  add_dependencies(afmt ablack)
endif()

if(PYTHON_FOUND)
  add_custom_target(apip # https://pip.readthedocs.io/en/stable
    ${PYTHON_EXECUTABLE} -m pip install -r ${CMAKE_CURRENT_LIST_DIR}/requirements.txt
    COMMENT "${PYTHON_EXECUTABLE} -m pip install -r requirements.txt"
  )
endif()

if(PYTHON_FOUND AND CYTHON_FOUND)
  set(OPTIONS)
  file_scaner(SOURCES RECURSE python/src)
  file(GLOB PRODUCTS ${PROJECT_NAME}*.so ${PROJECT_NAME}*.pyd)

  if(NOT CMAKE_VERSION VERSION_LESS 3.2)
    list(APPEND OPTIONS BYPRODUCTS ${PRODUCTS} ${SOURCES})
  endif()

  add_custom_target(apy ALL # https://cython.readthedocs.io/en/stable
    ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/setup.py ${OPTIONS}
  )
  set(OPTIONS)
endif()

if(NOT CMAKE_VERSION VERSION_LESS 3.9 AND DOXYGEN_FOUND)
  # Project related configuration options
  set(DOXYGEN_CREATE_SUBDIRS YES)
  set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)

  # Build related configuration options
  # Configuration options related to warning and progress messages
  set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)
  set(DOXYGEN_WARN_NO_PARAMDOC YES)

  # Configuration options related to the input files
  set(DOXYGEN_RECURSIVE YES)

  # Configuration options related to source browsing
  # Configuration options related to the alphabetical class index
  # Configuration options related to the HTML output
  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_USE_MATHJAX YES)
  set(DOXYGEN_MATHJAX_VERSION MathJax_3)

  # Configuration options related to the LaTeX output
  # Configuration options related to the RTF output
  # Configuration options related to the man page output
  # Configuration options related to the XML output
  set(DOXYGEN_GENERATE_XML YES)

  # Configuration options related to the DOCBOOK output
  # Configuration options for the AutoGen Definitions output
  # Configuration options related to Sqlite3 output
  # Configuration options related to the Perl module output
  # Configuration options related to the preprocessor
  set(DOXYGEN_MACRO_EXPANSION YES)
  set(DOXYGEN_EXPAND_ONLY_PREDEF YES)
  set(DOXYGEN_PREDEFINED
    "__STDC_VERSION__=201112L"
    "__cplusplus=201103L"
    "A_EXTERN:="
    "A_INTERN:="
    "A_PUBLIC:="
    "A_HIDDEN:="
  )

  # Configuration options related to external references
  # Configuration options related to the dot tool
  if(Doxygen_dot_FOUND)
    set(DOXYGEN_HAVE_DOT YES)
    set(DOXYGEN_INTERACTIVE_SVG YES)
    set(DOXYGEN_DOT_IMAGE_FORMAT svg)
    set(DOXYGEN_DOT_MULTI_TARGETS YES)
  endif()

  # https://www.doxygen.nl/manual/config.html
  doxygen_add_docs(adoxygen WORKING_DIRECTORY
    ${CMAKE_CURRENT_LIST_DIR}/include/a
    ${CMAKE_CURRENT_LIST_DIR}/include/a
    ${CMAKE_CURRENT_LIST_DIR}/README.md
  )
  add_dependencies(adoc adoxygen)
endif()
