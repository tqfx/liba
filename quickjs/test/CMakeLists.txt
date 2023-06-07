function(unittest source name)
  add_test(NAME qjs_${name} WORKING_DIRECTORY $<TARGET_FILE_DIR:aqjs>
      COMMAND ${QJS_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/${source}.js ${ARGN}
  )
endfunction()

unittest(a a)

unittest(mf mf)

unittest(polytrack3 polytrack3)

unittest(polytrack5 polytrack5)

unittest(polytrack7 polytrack7)
