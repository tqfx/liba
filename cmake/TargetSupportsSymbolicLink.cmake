function(TARGET_SUPPORTS_SYMBOLIC_LINK)
  get_filename_component(name ${CMAKE_CURRENT_LIST_FILE} NAME)
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_CURRENT_LIST_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${name}
    ERROR_QUIET RESULT_VARIABLE result
  )
  if(${result} EQUAL 0)
    set(TARGET_SUPPORTS_SYMBOLIC_LINK 1 CACHE INTERNAL "Test TARGET_SUPPORTS_SYMBOLIC_LINK")
  else()
    set(TARGET_SUPPORTS_SYMBOLIC_LINK 0 CACHE INTERNAL "Test TARGET_SUPPORTS_SYMBOLIC_LINK")
  endif()
  file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/${name})
endfunction()
if(NOT DEFINED TARGET_SUPPORTS_SYMBOLIC_LINK)
  TARGET_SUPPORTS_SYMBOLIC_LINK()
endif()
