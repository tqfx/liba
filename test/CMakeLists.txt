get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
string_append(CMAKE_CXX_FLAGS ${WARNINGS_XX} ${SANITIZE_XX})
string_append(CMAKE_C_FLAGS ${WARNINGS_CC} ${SANITIZE_CC})
string_append(CMAKE_EXE_LINKER_FLAGS ${SANITIZE_LD})

function(set_executable_options)
  list(FIND ENABLED_LANGUAGES CXX HAS_CXX)
  set_target_properties(${ARGN} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION ${LIBA_IPO}
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

  if(LIBA_ANALYZER)
    target_compile_analyzer(${ARGN})
  endif()

  if(LIBA_STATIC)
    target_link_static(${ARGN})
  endif()
endfunction()

set(TARGET_PREFIX test.)

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
  elseif(BUILD_SHARED_LIBS)
    target_link_libraries(${TARGET} PRIVATE liba)
  else()
    target_link_libraries(${TARGET} PRIVATE liba.o)
  endif()

  set_executable_options(${TARGET})
endfunction()

function(unittest target)
  set(TARGET "${TARGET_PREFIX}${target}")
  cmake_parse_arguments(TEST "" "NAME" "ARGS" ${ARGN})
  set(ARGS)

  if(NOT TEST_NAME)
    set(TEST_NAME ${target})
  endif()

  if(IS_MULTI_CONFIG)
    set(BINARY_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
  else()
    set(BINARY_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  endif()

  if((BUILD_SHARED_LIBS OR LIBA_SANITIZE) AND IS_MULTI_CONFIG)
    set(WORKING_DIRECTORY $<TARGET_FILE_DIR:alib>)
  else()
    set(WORKING_DIRECTORY ${BINARY_DIRECTORY})
  endif()

  foreach(arg ${TEST_ARGS} ${TEST_UNPARSED_ARGUMENTS})
    get_filename_component(ext ${arg} EXT)

    if(NOT ext OR IS_ABSOLUTE ${arg})
      list(APPEND ARGS ${arg})
    elseif(NOT EMSCRIPTEN)
      list(APPEND ARGS ${BINARY_DIRECTORY}/${arg})
    endif()
  endforeach()

  if(NOT TARGET_SUPPORTS_EXECUTABLES AND NOT CMAKE_CROSSCOMPILING_EMULATOR)
    return()
  endif()

  add_test(NAME ${TEST_NAME} WORKING_DIRECTORY ${WORKING_DIRECTORY}
    COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} $<TARGET_FILE:${TARGET}> ${ARGS}
  )
endfunction()

option(LIBA_GNUPLOT "Enable/Disable gnuplot" 0)

if(LIBA_GNUPLOT)
  find_package(Gnuplot)
endif()

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  function(unitplot target script output)
    set(TARGET "${TARGET_PREFIX}${target}")
    set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    if(IS_MULTI_CONFIG)
      set(BINARY_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
    else()
      set(BINARY_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    if((BUILD_SHARED_LIBS OR LIBA_SANITIZE) AND IS_MULTI_CONFIG)
      set(WORKING_DIRECTORY $<TARGET_FILE_DIR:alib>)
    else()
      set(WORKING_DIRECTORY ${BINARY_DIRECTORY})
    endif()

    if(NOT IS_ABSOLUTE ${script})
      file(TO_CMAKE_PATH ${SOURCE_DIRECTORY}/${script} script)
    endif()

    if(NOT IS_ABSOLUTE ${output})
      file(TO_CMAKE_PATH ${BINARY_DIRECTORY}/${output} output)
    endif()

    if(NOT TARGET_SUPPORTS_EXECUTABLES AND NOT CMAKE_CROSSCOMPILING_EMULATOR)
      return()
    endif()

    add_custom_command(TARGET ${TARGET} POST_BUILD WORKING_DIRECTORY ${WORKING_DIRECTORY}
      COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} $<TARGET_FILE:${TARGET}> ${output} ${ARGN}
      COMMAND ${GNUPLOT_EXECUTABLE} -c ${script} ${output}
    )
  endfunction()
endif()

building(a a.c a.cpp)
unittest(a NAME a_bkdr ARGS bkdr bkdr)
unittest(a NAME a_for ARGS for 10)
unittest(a)

building(avl avl.c avl.cpp)
unittest(avl)

building(buf buf.c buf.cpp)
unittest(buf)

building(complex complex.c complex.cpp)
unittest(complex ARGS -4,3 -2,1)

building(crc crc.c crc.cpp)
unittest(crc ARGS crc.c)

building(hpf hpf.c hpf.cpp)
unittest(hpf)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(hpf 2.gp hpf.log)
endif()

building(list list.c list.cpp)
unittest(list)

building(lpf lpf.c lpf.cpp)
unittest(lpf)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(lpf 2.gp lpf.log)
endif()

building(main main.c main.cpp)
unittest(main)

building(math math.c math.cpp)
unittest(math)

building(mf mf.c mf.cpp)
unittest(mf)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(mf mf.gp mf_gauss.log -4 4 1 0)
  unitplot(mf mf.gp mf_gauss2.log -4 4 1 -1 1 1)
  unitplot(mf mf.gp mf_gbell.log -4 4 2 4 0)
  unitplot(mf mf.gp mf_sig.log -4 4 2 0)
  unitplot(mf mf.gp mf_dsig.log -4 4 5 -2 5 2)
  unitplot(mf mf.gp mf_psig.log -4 4 5 -2 -5 2)
  unitplot(mf mf.gp mf_trap.log -3 3 -2 -1 1 2)
  unitplot(mf mf.gp mf_tri.log -2 2 -1 0 1)
  unitplot(mf mf.gp mf_lins.log -2 2 -1 1)
  unitplot(mf mf.gp mf_linz.log -2 2 -1 1)
  unitplot(mf mf.gp mf_s.log -2 2 -1 1)
  unitplot(mf mf.gp mf_z.log -2 2 -1 1)
  unitplot(mf mf.gp mf_pi.log -3 3 -2 -1 1 2)
endif()

building(notefreqs notefreqs.c notefreqs.cpp)
unittest(notefreqs)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(notefreqs notefreqs.gp notefreqs.log)
endif()

building(operator operator.c operator.cpp)
unittest(operator)

building(pid pid.c pid.cpp)
unittest(pid)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(pid 3.gp pid.log)
endif()

building(pid_expert pid_expert.c pid_expert.cpp)
unittest(pid_expert)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(pid_expert 3.gp pid_expert.log)
endif()

building(pid_fuzzy pid_fuzzy.c pid_fuzzy.cpp)
unittest(pid_fuzzy)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(pid_fuzzy 3.gp pid_fuzzy.log)
endif()

building(pid_neuro pid_neuro.c pid_neuro.cpp)
unittest(pid_neuro)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(pid_neuro 3.gp pid_neuro.log)
endif()

building(poly poly.c poly.cpp)
unittest(poly)

building(polytraj3 polytraj3.c polytraj3.cpp)
unittest(polytraj3 ARGS polytraj3.log 0 10 0 10)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(polytraj3 polytraj3.gp polytraj3.log 0 10 0 10)
endif()

building(polytraj5 polytraj5.c polytraj5.cpp)
unittest(polytraj5 ARGS polytraj5.log 0 10 0 10)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(polytraj5 polytraj3.gp polytraj5.log 0 10 0 10)
endif()

building(polytraj7 polytraj7.c polytraj7.cpp)
unittest(polytraj7 ARGS polytraj7.log 0 10 0 10)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(polytraj7 polytraj7.gp polytraj7.log 0 10 0 10)
endif()

building(que que.c que.cpp)
unittest(que)

building(rbf rbf.c rbf.cpp)
unittest(rbf)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(rbf 3.gp rbf.log)
endif()

building(rbt rbt.c rbt.cpp)
unittest(rbt)

building(str str.c str.cpp)
unittest(str)

building(slist slist.c slist.cpp)
unittest(slist)

building(tf tf.c tf.cpp)
unittest(tf)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(tf 2.gp tf.log)
endif()

building(utf utf.c utf.cpp)
unittest(utf)

building(vec vec.c vec.cpp)
unittest(vec)

building(version version.c version.cpp)
unittest(version)
