function(unittest source name)
  add_test(NAME js_${name}
    COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} ${CMAKE_CURRENT_LIST_DIR}/${source}.js ${ARGN}
  )
endfunction()

unittest(a a)

unittest(mf mf)

unittest(pid pid)

unittest(pid_fuzzy pid_fuzzy)

unittest(pid_neuron pid_neuron)

unittest(polytraj3 polytraj3)

unittest(polytraj5 polytraj5)

unittest(polytraj7 polytraj7)

unittest(tf tf)

unittest(version version)
