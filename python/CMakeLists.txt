get_filename_component(WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
get_filename_component(WORKING_DIRECTORY ${WORKING_DIRECTORY} DIRECTORY)

function(unittest source name)
  add_test(NAME py-${name} WORKING_DIRECTORY ${WORKING_DIRECTORY}
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/test/${source}.py ${ARGN}
  )
endfunction()

unittest(a a)
