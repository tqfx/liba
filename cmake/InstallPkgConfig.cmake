function(install_pkgconfig package target)
  set(one_value_keywords "NAME;DESTINATION;HOMEPAGE_URL;LICENSE;VERSION")
  set(multi_value_keywords "REQUIRES;PRIVATE_REQUIRES;CONFLICTS")
  cmake_parse_arguments(PC "" "${one_value_keywords}" "${multi_value_keywords}" ${ARGN})

  if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR lib)
  endif()

  if(NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
    set(CMAKE_INSTALL_INCLUDEDIR include)
  endif()
  set(PKGCONFIGDIR ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
  set(CONTENT "prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=\${prefix}
libdir=\${exec_prefix}/${CMAKE_INSTALL_LIBDIR}
includedir=\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}
")

  if(PC_NAME)
    set(CONTENT "${CONTENT}\nName: ${PC_NAME}\n")
  elseif(PROJECT_NAME)
    set(CONTENT "${CONTENT}\nName: ${PROJECT_NAME}\n")
  endif()

  if(PC_DESCRIPTION)
    set(CONTENT "${CONTENT}Description: ${PC_DESCRIPTION}\n")
  elseif(PROJECT_DESCRIPTION)
    set(CONTENT "${CONTENT}Description: ${PROJECT_DESCRIPTION}\n")
  endif()

  if(PC_HOMEPAGE_URL)
    set(CONTENT "${CONTENT}URL: ${PC_HOMEPAGE_URL}\n")
  elseif(PROJECT_HOMEPAGE_URL)
    set(CONTENT "${CONTENT}URL: ${PROJECT_HOMEPAGE_URL}\n")
  endif()

  if(PC_LICENSE)
    set(CONTENT "${CONTENT}License: ${PC_LICENSE}\n")
  elseif(PROJECT_LICENSE)
    set(CONTENT "${CONTENT}License: ${PROJECT_LICENSE}\n")
  endif()

  if(PC_VERSION)
    set(CONTENT "${CONTENT}Version: ${PC_VERSION}\n")
  elseif(PROJECT_VERSION)
    set(CONTENT "${CONTENT}Version: ${PROJECT_VERSION}\n")
  endif()

  if(PC_REQUIRES)
    set(CONTENT "${CONTENT}Requires: $<JOIN:${PC_REQUIRES}, >\n")
  endif()

  if(PC_PRIVATE_REQUIRES)
    set(CONTENT "${CONTENT}Requires.private: $<JOIN:${PC_PRIVATE_REQUIRES}, >\n")
  endif()

  if(PC_CONFLICTS)
    set(CONTENT "${CONTENT}Conflicts: $<JOIN:${PC_CONFLICTS},$<COMMA> >\n")
  endif()

  get_property(prop TARGET ${target} PROPERTY INTERFACE_COMPILE_DEFINITIONS)
  string(REGEX REPLACE "\\$<BUILD_INTERFACE:[^>]*>" "" prop "${prop}")
  string(REPLACE "INSTALL_INTERFACE" "BUILD_INTERFACE" prop "${prop}")
  string(REPLACE "-D$<JOIN:, -D>" "" PC_CFLAGS "-D$<JOIN:${prop}, -D>")
  if(PC_LDFLAGS)
    set(CONTENT "${CONTENT}Cflags: -I\${includedir} ${PC_CFLAGS}\n")
  else()
    set(CONTENT "${CONTENT}Cflags: -I\${includedir}\n")
  endif()

  get_property(name TARGET ${target} PROPERTY OUTPUT_NAME)
  if(NOT DEFINED name)
    set(name ${target})
  endif()
  set(CONTENT "${CONTENT}Libs: -L\${libdir} -l${name}\n")

  get_property(prop TARGET ${target} PROPERTY INTERFACE_LINK_LIBRARIES)
  string(REGEX REPLACE "\\$<BUILD_INTERFACE:[^>]*>" "" prop "${prop}")
  string(REPLACE "INSTALL_INTERFACE" "BUILD_INTERFACE" prop "${prop}")
  string(REPLACE "-l$<JOIN:, -l>" "" PC_LDFLAGS "-l$<JOIN:${prop}, -l>")
  if(PC_LDFLAGS)
    set(CONTENT "${CONTENT}Libs.private: ${PC_LDFLAGS}\n")
  endif()

  file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${package}.pc CONTENT "${CONTENT}")
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${package}.pc DESTINATION ${PKGCONFIGDIR})
endfunction()
