file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.js)
file(COPY ${SOURCES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

function(unittest source name)
  add_test(NAME js_${name} WORKING_DIRECTORY ${WORKING_DIRECTORY}
    COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} ${CMAKE_CURRENT_BINARY_DIR}/${source}.js ${ARGN}
  )
endfunction()

unittest(a a)

unittest(pid pid)

unittest(pid_fuzzy pid_fuzzy)

unittest(polytrack polytrack)

unittest(tf tf)

unittest(version version)
