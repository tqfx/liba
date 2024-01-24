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

unittest(crc8 crc8)

unittest(crc16 crc16)

unittest(crc32 crc32)

unittest(crc64 crc64)

unittest(hpf hpf)

unittest(lpf lpf)

unittest(mf mf)

unittest(pid pid)

unittest(pid_fuzzy pid_fuzzy)

unittest(pid_neuro pid_neuro)

unittest(polytraj3 polytraj3)

unittest(polytraj5 polytraj5)

unittest(polytraj7 polytraj7)

unittest(tf tf)

unittest(version version)
