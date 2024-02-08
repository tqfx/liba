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

unittest(tf tf)

unittest(trajbell trajbell)

unittest(trajpoly3 trajpoly3)

unittest(trajpoly5 trajpoly5)

unittest(trajpoly7 trajpoly7)

unittest(trajtrap trajtrap)

unittest(version version)
