function(unittest source name)
  add_test(NAME lua-${name} WORKING_DIRECTORY $<TARGET_FILE_DIR:alua>
    COMMAND ${LUA_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/${source}.lua ${ARGN}
  )
endfunction()

unittest(a a)

unittest(complex complex)

unittest(fpid fpid)

unittest(mf mf)

unittest(pid pid)

unittest(polytrack polytrack)

unittest(tf tf)

unittest(version version)
