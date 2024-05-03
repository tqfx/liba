get_property(OPTIONS TARGET a PROPERTY SOURCES)
set(OPTIONS MAIN_DEPENDENCY ${CMAKE_CURRENT_LIST_DIR}/src/a.pyx
  DEPENDS ${OPTIONS}
)

if(NOT CMAKE_VERSION VERSION_LESS 3.2)
  list(APPEND OPTIONS BYPRODUCTS ${CMAKE_CURRENT_LIST_DIR}/src/a.c
    ${CMAKE_CURRENT_LIST_DIR}/liba${CYTHON_SUFFIX}
  )
endif()

add_custom_command( # https://cython.readthedocs.io/en/stable
  OUTPUT ${CMAKE_CURRENT_LIST_DIR}/liba${CYTHON_SUFFIX}
  COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/setup.py ${OPTIONS}
)
add_custom_target(apy ALL
  DEPENDS ${CMAKE_CURRENT_LIST_DIR}/liba${CYTHON_SUFFIX}
)

if("${LIBA_INSTALL}" MATCHES "[Pp]ython")
  install(FILES ${CMAKE_CURRENT_LIST_DIR}/liba.pyi
    ${CMAKE_CURRENT_LIST_DIR}/liba${CYTHON_SUFFIX}
    DESTINATION ${CYTHON_PLATLIB}
  )
elseif("${LIBA_INSTALL}" MATCHES "^$")
  get_filename_component(name ${CYTHON_PLATLIB} NAME)
  install(FILES ${CMAKE_CURRENT_LIST_DIR}/liba.pyi
    ${CMAKE_CURRENT_LIST_DIR}/liba${CYTHON_SUFFIX}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/${name}
  )
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/test/CMakeLists.txt)
  add_subdirectory(test)
endif()
