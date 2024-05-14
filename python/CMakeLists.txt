if(Python_SITEARCH)
  set(python_sitelib ${Python_SITEARCH})
else()
  execute_process(COMMAND ${Python_EXECUTABLE} -c
    "import sysconfig;print(sysconfig.get_path(\"platlib\"))"
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE python_sitelib
  )
endif()

if(Python_Development_FOUND)
  if(WIN32)
    set(CMAKE_SHARED_MODULE_SUFFIX ".pyd")
  endif()

  if(Python_SOABI)
    set(CMAKE_SHARED_MODULE_SUFFIX
      ".${Python_SOABI}${CMAKE_SHARED_MODULE_SUFFIX}"
    )
  endif()

  set(CMAKE_SHARED_MODULE_PREFIX "")
  set(python_suffix ${CMAKE_SHARED_MODULE_SUFFIX})
  set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
  set(CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_RELWITHDEBINFO})
  set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/src/a.c
    COMMAND ${CYTHON_EXECUTABLE} --fast-fail --module-name ${PROJECT_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/a.pyx # https://cython.readthedocs.io/en/stable
  )
  add_library(apy MODULE $<TARGET_OBJECTS:a> ${CMAKE_CURRENT_LIST_DIR}/src/a.c)
  set_target_properties(apy PROPERTIES DEFINE_SYMBOL A_EXPORTS OUTPUT_NAME liba
    INTERPROCEDURAL_OPTIMIZATION ${LIBA_IPO} VISIBILITY_INLINES_HIDDEN 1
    LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_LIST_DIR}
    LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_LIST_DIR}
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}
    CXX_VISIBILITY_PRESET hidden C_VISIBILITY_PRESET hidden
  )
  add_library_properties(apy PRIVATE alib)

  if(TARGET Python::Python)
    target_link_libraries(apy PRIVATE Python::Python)
    get_property(implib TARGET Python::Python PROPERTY IMPORTED_IMPLIB_RELEASE)

    if(implib)
      set_property(TARGET Python::Python PROPERTY MAP_IMPORTED_CONFIG_DEBUG Release)
    endif()
  else()
    string(REGEX REPLACE "optimized;([^;]+).*" "\\1" Python_LIBRARIES "${Python_LIBRARIES}")
    target_include_directories(apy PRIVATE ${Python_INCLUDE_DIRS})
    target_link_libraries(apy PRIVATE ${Python_LIBRARIES})
  endif()
else()
  get_property(OPTIONS TARGET a PROPERTY SOURCES)
  set(OPTIONS MAIN_DEPENDENCY ${CMAKE_CURRENT_LIST_DIR}/src/a.pyx DEPENDS ${OPTIONS})

  if(NOT CMAKE_VERSION VERSION_LESS 3.2)
    list(APPEND OPTIONS BYPRODUCTS ${CMAKE_CURRENT_LIST_DIR}/src/a.c)
  endif()

  execute_process(COMMAND ${Python_EXECUTABLE} -c
    "import sysconfig;print(sysconfig.get_config_var(\"EXT_SUFFIX\") or sysconfig.get_config_var(\"SO\"))"
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE python_suffix
  )
  add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/liba${python_suffix}
    COMMAND ${Python_EXECUTABLE} ${PROJECT_SOURCE_DIR}/setup.py ${OPTIONS}
  )
  add_custom_target(apy ALL
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/liba${python_suffix}
  )
endif()

if("${LIBA_INSTALL}" MATCHES "[Pp]ython")
  install(FILES ${CMAKE_CURRENT_LIST_DIR}/liba.pyi
    ${CMAKE_CURRENT_LIST_DIR}/liba${python_suffix}
    DESTINATION ${python_sitelib}
  )
elseif("${LIBA_INSTALL}" MATCHES "^$")
  get_filename_component(site ${python_sitelib} NAME)
  install(FILES ${CMAKE_CURRENT_LIST_DIR}/liba.pyi
    ${CMAKE_CURRENT_LIST_DIR}/liba${python_suffix}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/${site}
  )
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/test/CMakeLists.txt)
  add_subdirectory(test)
endif()
