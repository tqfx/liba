set(JAVA_EXECUTABLE ${Java_JAVA_EXECUTABLE} -Djava.library.path=.)
file(GLOB_RECURSE SOURCES src/${PROJECT_NAME}/*.java)

function(building target source)
  add_jar(jar-${target} INCLUDE_JARS ajar
    SOURCES ${SOURCES} test/${source}.java
    ENTRY_POINT ${source}
    OUTPUT_NAME ${source}
  )
endfunction()

function(unittest source name)
  add_test(NAME jar-${name} WORKING_DIRECTORY $<TARGET_FILE_DIR:ajni>
    COMMAND ${JAVA_EXECUTABLE} -jar ${CMAKE_CURRENT_BINARY_DIR}/${source}.jar ${ARGN}
  )
endfunction()

building(test-a test_a)
unittest(test_a a)

building(test-fpid test_fpid)
unittest(test_fpid fpid)

building(test-mf test_mf)
unittest(test_mf mf)

building(test-pid test_pid)
unittest(test_pid pid)

building(test-polytrack3 test_polytrack3)
unittest(test_polytrack3 polytrack3)

building(test-polytrack5 test_polytrack5)
unittest(test_polytrack5 polytrack5)

building(test-polytrack7 test_polytrack7)
unittest(test_polytrack7 polytrack7)

building(test-tf test_tf)
unittest(test_tf tf)
