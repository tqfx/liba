option(LIBA_OPENMP "Enable/Disable openmp" $ENV{LIBA_OPENMP})

if(LIBA_OPENMP)
  find_package(OpenMP)
endif()

if(LIBA_OPENMP AND OpenMP_C_FLAGS)
  string_append(CMAKE_C_FLAGS ${OpenMP_C_FLAGS})
endif()

if(LIBA_OPENMP AND OpenMP_CXX_FLAGS)
  string_append(CMAKE_CXX_FLAGS ${OpenMP_CXX_FLAGS})
endif()

if(NOT Python_VERSION VERSION_LESS 3.11)
  set(CMAKE_C_STANDARD 11)
elseif(NOT Python_VERSION VERSION_LESS 3.6)
  set(CMAKE_C_STANDARD 99)
endif()

if(WIN32)
  set(CMAKE_SHARED_MODULE_SUFFIX ".pyd")
endif()

if(Python_SOABI)
  set(python_suffix ".${Python_SOABI}${CMAKE_SHARED_MODULE_SUFFIX}")
elseif(EXISTS ${Python_EXECUTABLE})
  execute_process(COMMAND ${Python_EXECUTABLE} -c
    "import sysconfig;print(sysconfig.get_config_var(\"EXT_SUFFIX\") or sysconfig.get_config_var(\"SO\"))"
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE python_suffix
  )
endif()

if(CYTHON_FOUND) # https://cython.readthedocs.io/en/stable
  add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}.c
    COMMAND ${CYTHON_EXECUTABLE} --fast-fail ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}.pyx
  )
endif()

if(python_suffix)
  set(CMAKE_SHARED_MODULE_SUFFIX ${python_suffix})
else()
  set(python_suffix ${CMAKE_SHARED_MODULE_SUFFIX})
endif()

set(CMAKE_SHARED_MODULE_PREFIX "")
set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
set(CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_RELWITHDEBINFO})
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
add_library(apy MODULE $<TARGET_OBJECTS:a> ${CMAKE_CURRENT_LIST_DIR}/src/${PROJECT_NAME}.c)
set_target_properties(apy PROPERTIES DEFINE_SYMBOL A_EXPORTS OUTPUT_NAME ${PROJECT_NAME}
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

if(Python_SITEARCH)
  set(python_platlib ${Python_SITEARCH})
else()
  execute_process(COMMAND ${Python_EXECUTABLE} -c
    "import sysconfig;print(sysconfig.get_path(\"platlib\"))"
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE python_platlib
  )
endif()

if(NOT python_platlib)
  set(python_platlib ${CMAKE_INSTALL_LIBDIR}/site-packages)
endif()

if("${LIBA_INSTALL}" MATCHES "[Pp]ython")
  install(FILES ${CMAKE_CURRENT_LIST_DIR}/liba.pyi
    ${CMAKE_CURRENT_LIST_DIR}/liba${python_suffix}
    DESTINATION ${python_platlib}
  )
elseif("${LIBA_INSTALL}" MATCHES "^$")
  string(REGEX REPLACE ".*[Ll]ib[/\\](.*)$" "\\1" site "${python_platlib}")
  install(FILES ${CMAKE_CURRENT_LIST_DIR}/liba.pyi
    ${CMAKE_CURRENT_LIST_DIR}/liba${python_suffix}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/${site}
  )
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/test/CMakeLists.txt AND Python_EXECUTABLE)
  add_subdirectory(test)
endif()
