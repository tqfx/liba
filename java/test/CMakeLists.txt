set(JAVA_EXECUTABLE ${Java_JAVA_EXECUTABLE} -Djava.library.path=.)

function(building target)
  add_jar(jar_${target} INCLUDE_JARS ajar
    SOURCES ${SOURCES} _${target}.java
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
endfunction()

building(a)
unittest(a a.log)

building(mf)
unittest(mf)

building(pid)
unittest(pid)

building(pid_fuzzy)
unittest(pid_fuzzy)

building(pid_neuro)
unittest(pid_neuro)

building(polytraj3)
unittest(polytraj3)

building(polytraj5)
unittest(polytraj5)

building(polytraj7)
unittest(polytraj7)

building(tf)
unittest(tf)

building(version)
unittest(version)
