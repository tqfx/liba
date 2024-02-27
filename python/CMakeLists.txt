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

unittest(crc crc)

unittest(hpf hpf)

unittest(lpf lpf)

unittest(mf mf)

unittest(pid pid)

unittest(pid_fuzzy pid_fuzzy)

unittest(pid_neuro pid_neuro)

unittest(poly poly)

unittest(tf tf)

unittest(trajbell trajbell)

unittest(trajpoly3 trajpoly3)

unittest(trajpoly5 trajpoly5)

unittest(trajpoly7 trajpoly7)

unittest(trajtrap trajtrap)

unittest(version version)
