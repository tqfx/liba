set(JAVA_EXECUTABLE ${Java_JAVA_EXECUTABLE} -ea -Djava.library.path=.)

function(building target)
  add_jar(java.test.${target} INCLUDE_JARS ajar
    MANIFEST ${CMAKE_CURRENT_LIST_DIR}/../manifest
    SOURCES _${target}.java ${SOURCES}
    ENTRY_POINT _${target}
    OUTPUT_NAME ${target}
  )
endfunction()

function(unittest target)
  set(ARGS)

  foreach(arg ${ARGN})
    get_filename_component(ext ${arg} EXT)

    if(NOT ext OR IS_ABSOLUTE ${arg})
      list(APPEND ARGS ${arg})
    else()
      list(APPEND ARGS ${CMAKE_CURRENT_BINARY_DIR}/${arg})
    endif()
  endforeach()

  add_test(NAME jar_${target} WORKING_DIRECTORY ${WORKING_DIRECTORY}
    COMMAND ${JAVA_EXECUTABLE} -jar ${CMAKE_CURRENT_BINARY_DIR}/${target}.jar ${ARGS}
  )
  set_tests_properties(jar_${target} PROPERTIES TIMEOUT 30
    FAIL_REGULAR_EXPRESSION "ERROR;error"
  )
endfunction()

building(a)
unittest(a a.log)

building(mf)
unittest(mf)

building(crc)
unittest(crc)

building(hpf)
unittest(hpf)

building(lpf)
unittest(lpf)

building(pid)
unittest(pid)

building(pid_fuzzy)
unittest(pid_fuzzy)

building(pid_neuro)
unittest(pid_neuro)

building(regress_linear)
unittest(regress_linear)

building(regress_simple)
unittest(regress_simple)

building(tf)
unittest(tf)

building(trajpoly3)
unittest(trajpoly3)

building(trajpoly5)
unittest(trajpoly5)

building(trajpoly7)
unittest(trajpoly7)

building(trajtrap)
unittest(trajtrap)

building(version)
unittest(version)
