function(unittest source name)
  add_test(NAME js_${name}
    COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} ${CMAKE_CURRENT_LIST_DIR}/${source}.js ${ARGN}
  )
endfunction()

unittest(a a)

unittest(pid pid)

unittest(pid_fuzzy pid_fuzzy)

unittest(pid_neuron pid_neuron)

unittest(polytrack polytrack)

unittest(tf tf)

unittest(version version)
