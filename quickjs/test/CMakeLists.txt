function(unittest source name)
  add_test(NAME qjs-${name} WORKING_DIRECTORY $<TARGET_FILE_DIR:aqjs>
      COMMAND ${QJS_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/${source}.js ${ARGN}
  )
endfunction()

unittest(a a)
