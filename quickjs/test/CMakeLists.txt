function(unittest source name)
  add_test(NAME qjs_${name} WORKING_DIRECTORY ${WORKING_DIRECTORY}
    COMMAND ${QJS_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/${source}.js ${ARGN}
  )
endfunction()

unittest(a a)

unittest(crc crc)

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

unittest(traptraj traptraj)

unittest(version version)
