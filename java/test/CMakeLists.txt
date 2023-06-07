function(building source target)
  add_jar(jar_${target} INCLUDE_JARS ajar
    SOURCES ${SOURCES} ${source}.java
    ENTRY_POINT ${source}
    OUTPUT_NAME ${source}
  )
endfunction()

set(JAVA_EXECUTABLE ${Java_JAVA_EXECUTABLE} -Djava.library.path=.)

function(unittest source name)
  set(ARGS)

  foreach(arg ${ARGN})
    get_filename_component(ext ${arg} EXT)

    if(NOT ext OR IS_ABSOLUTE ${arg})
      list(APPEND ARGS ${arg})
    else()
      list(APPEND ARGS ${CMAKE_CURRENT_BINARY_DIR}/${arg})
    endif()
  endforeach()

  add_test(NAME jar_${name} WORKING_DIRECTORY $<TARGET_FILE_DIR:ajni>
    COMMAND ${JAVA_EXECUTABLE} -jar ${CMAKE_CURRENT_BINARY_DIR}/${source}.jar ${ARGS}
  )
endfunction()

building(_a a)
unittest(_a a a.log)

building(_mf mf)
unittest(_mf mf)

building(_pid pid)
unittest(_pid pid)

building(_pid_fuzzy pid_fuzzy)
unittest(_pid_fuzzy pid_fuzzy)

building(_polytrack3 polytrack3)
unittest(_polytrack3 polytrack3)

building(_polytrack5 polytrack5)
unittest(_polytrack5 polytrack5)

building(_polytrack7 polytrack7)
unittest(_polytrack7 polytrack7)

building(_tf tf)
unittest(_tf tf)
