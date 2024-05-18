set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0063 NEW)
cmake_minimum_required(VERSION 2.8.12...4.0)

project(quickjs C)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
get_filename_component(CONFIG_CC "${CMAKE_C_COMPILER}" NAME_WE)
file(STRINGS ${CMAKE_CURRENT_LIST_DIR}/VERSION PROJECT_VERSION)
set(PROJECT_DESCRIPTION "QuickJS is a small and embeddable Javascript engine.")
set(PROJECT_HOMEPAGE_URL "https://bellard.org/quickjs")
set(CMAKE_C_EXTENSIONS 1)
set(CMAKE_C_STANDARD 99)
set(QJS_DEPENDS qjsc)

if(CMAKE_HOST_WIN32)
  set(SUFFIX ".exe")
else()
  set(SUFFIX "")
endif()

if(NOT QUICKJS_CROSSCOMPILING AND CMAKE_CROSSCOMPILING)
  if(CMAKE_VERSION VERSION_LESS 3.1)
    set(cmake_env)
  else()
    set(cmake_env ${CMAKE_COMMAND} -E env
      --unset=CC
      --unset=CFLAGS
      --unset=LDFLAGS
      --unset=DESTDIR
    )
  endif()

  include(ExternalProject)
  set(QJS_DEPENDS host-qjsc)
  ExternalProject_Add(${QJS_DEPENDS}
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    CMAKE_COMMAND ${cmake_env} ${CMAKE_COMMAND}
    CMAKE_CACHE_ARGS
      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}
      -DCMAKE_BUILD_TYPE:STRING=Release
      -DCMAKE_TOOLCHAIN_FILE:FILEPATH=
      -DQUICKJS_CROSSCOMPILING:BOOL=1
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/host
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
  )
  set(QJSC_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/bin/qjsc${SUFFIX})
else()
  set(QJSC_EXECUTABLE $<TARGET_FILE:qjsc>)
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel ..." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release MinSizeRel RelWithDebInfo)
endif()

# https://cmake.org/cmake/help/latest/module/CheckIPOSupported.html
if(NOT CMAKE_VERSION VERSION_LESS 3.9)
  cmake_policy(SET CMP0069 NEW)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT CONFIG_LTO)
endif()

if(NOT QUICKJS_MATH_LIBRARY AND WIN32)
  unset(QUICKJS_MATH_LIBRARY CACHE)
elseif(NOT QUICKJS_MATH_LIBRARY)
  set(QUICKJS_MATH_LIBRARY m)
endif()

find_package(Threads)

function(quickjs_compile target)
  add_library(${target} STATIC
    cutils.c
    libbf.c
    libregexp.c
    libunicode.c
    quickjs.c
    quickjs-libc.c
  )
  set_target_properties(${target} PROPERTIES
    DEFINE_SYMBOL CONFIG_VERSION="${PROJECT_VERSION}"
    INTERPROCEDURAL_OPTIMIZATION "${ARGN}"
    POSITION_INDEPENDENT_CODE 1
  )
  target_include_directories(${target}
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    PUBLIC $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
  )
  target_compile_definitions(${target} PRIVATE
    CONFIG_VERSION="${PROJECT_VERSION}"
    CONFIG_BIGNUM _GNU_SOURCE
  )

  if(UNIX)
    target_link_libraries(${target} PUBLIC
      ${QUICKJS_MATH_LIBRARY} ${CMAKE_DL_LIBS}
    )
  endif()

  if(CMAKE_USE_PTHREADS_INIT)
    target_link_libraries(${target} PUBLIC pthread)
  endif()

  if(CMAKE_C_COMPILER_ID MATCHES "GNU|[Cc]lang")
    target_compile_options(${target} PRIVATE -fwrapv)
  endif()
endfunction()

quickjs_compile(quickjs.lto ${CONFIG_LTO})
set(INSTALL_TARGETS quickjs.lto qjsc)
add_executable(qjsc qjsc.c)
set_target_properties(qjsc PROPERTIES
  INTERPROCEDURAL_OPTIMIZATION "${CONFIG_LTO}"
)
target_compile_definitions(qjsc PRIVATE
  CONFIG_PREFIX="${CMAKE_INSTALL_PREFIX}"
  CONFIG_VERSION="${PROJECT_VERSION}"
  CONFIG_BIGNUM _GNU_SOURCE
  CONFIG_CC="${CONFIG_CC}"
)
target_link_libraries(qjsc PRIVATE quickjs.lto)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|[Cc]lang")
  target_compile_options(qjsc PRIVATE -fwrapv)
endif()

if(NOT QUICKJS_CROSSCOMPILING)
  quickjs_compile(quickjs)
  list(APPEND INSTALL_TARGETS quickjs qjs)
  add_custom_command(DEPENDS ${QJS_DEPENDS}
    OUTPUT ${CMAKE_CURRENT_LIST_DIR}/repl.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMAND ${QJSC_EXECUTABLE} -m -o repl.c -c repl.js
  )
  add_custom_command(DEPENDS ${QJS_DEPENDS}
    OUTPUT ${CMAKE_CURRENT_LIST_DIR}/qjscalc.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMAND ${QJSC_EXECUTABLE} -fbignum -o qjscalc.c -c qjscalc.js
  )
  add_executable(qjs qjs.c repl.c qjscalc.c)
  set_target_properties(qjs PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION "${CONFIG_LTO}"
  )
  target_compile_definitions(qjs PRIVATE
    CONFIG_VERSION="${PROJECT_VERSION}"
    CONFIG_BIGNUM _GNU_SOURCE
  )
  target_link_libraries(qjs PRIVATE quickjs.lto)

  if(CMAKE_C_COMPILER_ID MATCHES "GNU|[Cc]lang")
    target_compile_options(qjs PRIVATE -fwrapv)
  endif()
endif()

include(GNUInstallDirs)
install(FILES quickjs.h quickjs-libc.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)
install(TARGETS ${INSTALL_TARGETS} EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(EXPORT ${PROJECT_NAME}-targets FILE ${PROJECT_NAME}-targets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
include(CMakePackageConfigHelpers)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake "@PACKAGE_INIT@\n"
  "include(\"\${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@-targets.cmake\")\n"
)
configure_package_config_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  VERSION ${PROJECT_VERSION} COMPATIBILITY AnyNewerVersion
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

get_property(prop TARGET quickjs.lto PROPERTY INTERFACE_LINK_LIBRARIES)
string(REGEX REPLACE "\\$<BUILD_INTERFACE:[^>]*>" "" prop "${prop}")
string(REPLACE "INSTALL_INTERFACE" "BUILD_INTERFACE" prop "${prop}")
string(REPLACE "-l$<JOIN:, -l>" "" PC_LDFLAGS "-l$<JOIN:${prop}, -l>")
file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc CONTENT
  "prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=\${prefix}
libdir=\${exec_prefix}/${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
includedir=\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}\n
Name: ${PROJECT_NAME}
Description: ${PROJECT_DESCRIPTION}
Version: ${PROJECT_VERSION}
URL: ${PROJECT_HOMEPAGE_URL}
Cflags: -I\${includedir}
Libs: -L\${libdir} -l${PROJECT_NAME}
Libs.private: ${PC_LDFLAGS}
")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
include(CPack)
