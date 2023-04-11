function(building source target)
  add_jar(jar-${target} INCLUDE_JARS ajar
    SOURCES ${SOURCES} ${source}.java
    ENTRY_POINT ${source}
    OUTPUT_NAME ${source}
  )
endfunction()

set(JAVA_EXECUTABLE ${Java_JAVA_EXECUTABLE} -Djava.library.path=.)

function(unittest source name)
  add_test(NAME jar-${name} WORKING_DIRECTORY $<TARGET_FILE_DIR:ajni>
    COMMAND ${JAVA_EXECUTABLE} -jar ${CMAKE_CURRENT_BINARY_DIR}/${source}.jar ${ARGN}
  )
endfunction()

building(_a a)
unittest(_a a)

building(_fpid fpid)
unittest(_fpid fpid)

building(_mf mf)
unittest(_mf mf)

building(_pid pid)
unittest(_pid pid)

building(_polytrack3 polytrack3)
unittest(_polytrack3 polytrack3)

building(_polytrack5 polytrack5)
unittest(_polytrack5 polytrack5)

building(_polytrack7 polytrack7)
unittest(_polytrack7 polytrack7)

building(_tf tf)
unittest(_tf tf)
