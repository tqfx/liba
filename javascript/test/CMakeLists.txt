function(unittest source name)
  add_test(NAME js_${name}
    COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} ${CMAKE_CURRENT_LIST_DIR}/${source}.js ${ARGN}
  )
  set_tests_properties(js_${name} PROPERTIES TIMEOUT 30
    FAIL_REGULAR_EXPRESSION "ERROR;error"
  )
endfunction()

unittest(a a)

unittest(mf mf)

unittest(crc crc)

unittest(hpf hpf)

unittest(lpf lpf)

unittest(pid pid)

unittest(pid_fuzzy pid_fuzzy)

unittest(pid_neuro pid_neuro)

unittest(regress_linear regress_linear)

unittest(regress_simple regress_simple)

unittest(tf tf)

unittest(trajbell trajbell)

unittest(trajpoly3 trajpoly3)

unittest(trajpoly5 trajpoly5)

unittest(trajpoly7 trajpoly7)

unittest(trajtrap trajtrap)

unittest(version version)
