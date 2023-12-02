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

  add_test(NAME lua_${name} WORKING_DIRECTORY ${WORKING_DIRECTORY}
    COMMAND ${LUA_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/${source}.lua ${ARGS}
  )
endfunction()

unittest(a a a.log)

unittest(complex complex)

unittest(mf mf)

unittest(pid pid)

unittest(pid_fuzzy pid_fuzzy)

unittest(pid_neuron pid_neuron)

unittest(polytraj polytraj)

unittest(tf tf)

unittest(version version)
