function(unittest source name)
  add_test(NAME py-${name} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/test/${source}.py ${ARGN}
  )
endfunction()

unittest(a a)
