get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

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

  if(LIBA_WARNINGS)
    target_compile_warnings(${ARGN})
  endif()

  if(LIBA_ANALYZER)
    target_compile_analyzer(${ARGN})
  endif()

  if(LIBA_SANITIZE)
    target_compile_sanitize(${ARGN})
    target_link_sanitize(${ARGN})
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

  if(LIBA_SANITIZE AND CMAKE_VERSION VERSION_LESS 3.12)
    list(APPEND ARGN $<TARGET_OBJECTS:asan>)
  endif()

  if(NOT TARGET_SUPPORTS_EXECUTABLES)
    add_library(${TARGET} STATIC ${ARGN})
  else()
    add_executable(${TARGET} ${ARGN})
  endif()

  if(LIBA_SANITIZE AND CMAKE_VERSION VERSION_LESS 3.12)
    add_library_properties(${TARGET} PRIVATE asan)
  elseif(LIBA_SANITIZE)
    target_link_libraries(${TARGET} PRIVATE asan)
  elseif(BUILD_SHARED_LIBS)
    target_link_libraries(${TARGET} PRIVATE liba)
  else()
    target_link_libraries(${TARGET} PRIVATE alib)
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

  if(IS_MULTI_CONFIG AND BUILD_SHARED_LIBS)
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
  set_tests_properties(${TEST_NAME} PROPERTIES TIMEOUT 30
    FAIL_REGULAR_EXPRESSION "ERROR;error;:[0-9]+:"
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

    if(IS_MULTI_CONFIG AND BUILD_SHARED_LIBS)
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

building(a a.c a.cc)
unittest(a NAME a_for ARGS for 10)
unittest(a NAME a_hash_bkdr ARGS hash_bkdr hash_bkdr)
unittest(a NAME a_hash_sdbm ARGS hash_sdbm hash_sdbm)
unittest(a)

building(avl avl.c avl.cc)
unittest(avl)

building(buf buf.c buf.cc)
unittest(buf)

building(complex complex.c complex.cc)
unittest(complex ARGS -4,3 -2,1)

building(crc crc.c crc.cc)
unittest(crc ARGS crc.c)

building(hpf hpf.c hpf.cc)
unittest(hpf)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(hpf 2.gp hpf.csv)
endif()

building(list list.c list.cc)
unittest(list)

building(lpf lpf.c lpf.cc)
unittest(lpf)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(lpf 3.gp lpf.csv)
endif()

building(math math.c math.cc)
unittest(math)

building(mf mf.c mf.cc)
unittest(mf)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(mf mf.gp mf_gauss.csv -4 4 1 0)
  unitplot(mf mf.gp mf_gauss2.csv -4 4 1 -1 1 1)
  unitplot(mf mf.gp mf_gbell.csv -4 4 2 4 0)
  unitplot(mf mf.gp mf_sig.csv -4 4 2 0)
  unitplot(mf mf.gp mf_dsig.csv -4 4 5 -2 5 2)
  unitplot(mf mf.gp mf_psig.csv -4 4 5 -2 -5 2)
  unitplot(mf mf.gp mf_trap.csv -3 3 -2 -1 1 2)
  unitplot(mf mf.gp mf_tri.csv -2 2 -1 0 1)
  unitplot(mf mf.gp mf_lins.csv -2 2 -1 1)
  unitplot(mf mf.gp mf_linz.csv -2 2 -1 1)
  unitplot(mf mf.gp mf_s.csv -2 2 -1 1)
  unitplot(mf mf.gp mf_z.csv -2 2 -1 1)
  unitplot(mf mf.gp mf_pi.csv -3 3 -2 -1 1 2)
endif()

building(notefreqs notefreqs.c notefreqs.cc)
unittest(notefreqs)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(notefreqs notefreqs.gp notefreqs.csv)
endif()

building(operator operator.c operator.cc)
unittest(operator)

building(pid pid.c pid.cc)
unittest(pid)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(pid 3.gp pid.csv)
endif()

building(pid_expert pid_expert.c pid_expert.cc)
unittest(pid_expert)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(pid_expert 3.gp pid_expert.csv)
endif()

building(pid_fuzzy pid_fuzzy.c pid_fuzzy.cc)
unittest(pid_fuzzy)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(pid_fuzzy 3.gp pid_fuzzy.csv)
endif()

building(pid_neuro pid_neuro.c pid_neuro.cc)
unittest(pid_neuro)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(pid_neuro 3.gp pid_neuro.csv)
endif()

building(poly poly.c poly.cc)
unittest(poly)

building(que que.c que.cc)
unittest(que)

building(rbt rbt.c rbt.cc)
unittest(rbt)

building(slist slist.c slist.cc)
unittest(slist)

building(str str.c str.cc)
unittest(str)

building(test test.c test.cc)
unittest(test)

building(tf tf.c tf.cc)
unittest(tf)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(tf 2.gp tf.csv)
endif()

building(trajbell trajbell.c trajbell.cc)
unittest(trajbell ARGS trajbell.csv 3 2 3 0 10)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(trajbell traj4.gp trajbell.csv 3 2 3 0 10)
endif()

building(trajpoly3 trajpoly3.c trajpoly3.cc)
unittest(trajpoly3 ARGS trajpoly3.csv 0 10 0 10)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(trajpoly3 traj3.gp trajpoly3.csv 0 10 0 10)
endif()

building(trajpoly5 trajpoly5.c trajpoly5.cc)
unittest(trajpoly5 ARGS trajpoly5.csv 0 10 0 10)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(trajpoly5 traj3.gp trajpoly5.csv 0 10 0 10)
endif()

building(trajpoly7 trajpoly7.c trajpoly7.cc)
unittest(trajpoly7 ARGS trajpoly7.csv 0 10 0 10)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(trajpoly7 traj4.gp trajpoly7.csv 0 10 0 10)
endif()

building(trajtrap trajtrap.c trajtrap.cc)
unittest(trajtrap ARGS trajtrap.csv 2 2 -2 0 4)

if(LIBA_GNUPLOT AND GNUPLOT_FOUND)
  unitplot(trajtrap traj3.gp trajtrap.csv 2 2 -2 0 4)
endif()

building(utf utf.c utf.cc)
unittest(utf)

building(vec vec.c vec.cc)
unittest(vec)

building(version version.c version.cc)
unittest(version)
