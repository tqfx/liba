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

  add_test(NAME py_${name} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/test/${source}.py ${ARGS}
  )
endfunction()

unittest(a a a.log)
