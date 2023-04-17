get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
string_append(CMAKE_CXX_FLAGS ${WARNINGS_CXXFLAGS} ${SANITIZE_CXXFLAGS})
string_append(CMAKE_C_FLAGS ${WARNINGS_CFLAGS} ${SANITIZE_CFLAGS})
string_append(CMAKE_EXE_LINKER_FLAGS ${SANITIZE_LDFLAGS})

function(set_executable_options)
  list(FIND ENABLED_LANGUAGES CXX HAS_CXX)
  set_target_properties(${ARGN} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION ${LIBA_LTO}
    POSITION_INDEPENDENT_CODE ${LIBA_PIE}
  )

  if(${HAS_CXX} GREATER -1)
    set_property(TARGET ${ARGN} APPEND PROPERTY COMPILE_DEFINITIONS HAS_CXX)
  endif()

  if(LIBA_IWYU AND IWYU_FOUND)
    add_include_what_you_use(TARGETS ${ARGN})
  endif()

  if(LIBA_CLANG_TIDY AND CLANG_TIDY_FOUND)
    add_clang_tidy(TARGETS ${ARGN} OPTIONS --fix)
  endif()

  if(LIBA_CPPCHECK AND CPPCHECK_FOUND)
    add_cppcheck(TARGETS ${ARGN} OPTIONS --enable=warning,performance)
  endif()

  if(LIBA_STATIC)
    target_link_static(${ARGN})
  endif()
endfunction()

set(TARGET_PREFIX test-)

function(building target)
  set(TARGET "${TARGET_PREFIX}${target}")
  list(FIND ENABLED_LANGUAGES CXX HAS_CXX)

  if(${HAS_CXX} EQUAL -1)
    file_filter(ARGN ${ARGN} EXT c h)
  endif()

  if(NOT TARGET_SUPPORTS_EXECUTABLES)
    add_library(${TARGET} STATIC ${ARGN})
  else()
    add_executable(${TARGET} ${ARGN})
  endif()

  set_property(TARGET ${TARGET} PROPERTY OUTPUT_NAME ${target})

  if(TARGET_SUPPORTS_SHARED_LIBS AND LIBA_SANITIZE)
    target_link_libraries(${TARGET} PRIVATE libasan)
  elseif(NOT CMAKE_VERSION VERSION_LESS 3.12 AND LIBA_SANITIZE)
    target_link_libraries(${TARGET} PRIVATE asan)
    set_library_link(${TARGET})
  else()
    target_link_libraries(${TARGET} PRIVATE alib)
  endif()

  set_executable_options(${TARGET})
endfunction()

function(unittest target)
  set(TARGET "${TARGET_PREFIX}${target}")
  cmake_parse_arguments(TEST "" "NAME" "ARGS" ${ARGN})

  if(NOT TEST_NAME)
    set(TEST_NAME ${target})
  endif()

  if(${IS_MULTI_CONFIG})
    set(WORKING_DIRECTORY $<TARGET_FILE_DIR:alib>)
  else()
    set(WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  endif()

  if(NOT TARGET_SUPPORTS_EXECUTABLES AND NOT CMAKE_CROSSCOMPILING_EMULATOR)
    return()
  endif()

  add_test(NAME ${TEST_NAME} WORKING_DIRECTORY ${WORKING_DIRECTORY}
    COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} $<TARGET_FILE:${TARGET}> ${TEST_ARGS}
  )
endfunction()

building(a a.c a.cpp)
unittest(a NAME bkdr ARGS bkdr bkdr)
unittest(a NAME for ARGS for 10)
unittest(a)

building(avl avl.c avl.cpp)
unittest(avl)

building(buf buf.c buf.cpp)
unittest(buf)

building(complex complex.c complex.cpp)
unittest(complex ARGS -4,3 -2,1)

building(crc crc.c crc.cpp)
unittest(crc ARGS crc.c)

building(fpid fpid.c fpid.cpp)
unittest(fpid)

building(list list.c list.cpp)
unittest(list)

building(main main.c main.cpp)
unittest(main)

building(math math.c math.cpp)
unittest(math)

building(notefreqs notefreqs.c notefreqs.cpp)
unittest(notefreqs)

building(operator operator.c operator.cpp)
unittest(operator)

building(pid pid.c pid.cpp)
unittest(pid)

building(poly poly.c poly.cpp)
unittest(poly)

building(polytrack polytrack.c polytrack.cpp)
unittest(polytrack)

building(rbt rbt.c rbt.cpp)
unittest(rbt)

building(slist slist.c slist.cpp)
unittest(slist)

building(version version.c version.cpp)
unittest(version)

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/host/CMakeLists.txt)
    add_subdirectory(host)
endif()
