include(${CMAKE_CURRENT_LIST_DIR}/FindCCache.cmake)
if(CCACHE_FOUND)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_EXECUTABLE}")
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY RULE_LAUNCH_LINK "${CCACHE_EXECUTABLE}")
endif()
if(CCACHE_FOUND AND CMAKE_GENERATOR STREQUAL "Xcode")
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/cc
    "#!/usr/bin/env sh\n\n"
    "# Xcode generator doesn't include the compiler as the\n"
    "# first argument, Ninja and Makefiles do. Handle both cases.\n"
    "if [ \"$1\" = \"${CMAKE_C_COMPILER}\" ] ; then\n"
    "    shift\n"
    "fi\n\n"
    "export CCACHE_CPP2=true\n"
    "exec \"${CCACHE_EXECUTABLE}\" \"${CMAKE_C_COMPILER}\" \"$@\"\n"
  )
  execute_process(COMMAND chmod a+rx ${CMAKE_CURRENT_BINARY_DIR}/cc)
  set(CMAKE_XCODE_ATTRIBUTE_CC ${CMAKE_CURRENT_BINARY_DIR}/cc)
  set(CMAKE_XCODE_ATTRIBUTE_LD ${CMAKE_CURRENT_BINARY_DIR}/cc)
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/cxx
    "#!/usr/bin/env sh\n\n"
    "# Xcode generator doesn't include the compiler as the\n"
    "# first argument, Ninja and Makefiles do. Handle both cases.\n"
    "if [ \"$1\" = \"${CMAKE_CXX_COMPILER}\" ] ; then\n"
    "    shift\n"
    "fi\n\n"
    "export CCACHE_CPP2=true\n"
    "exec \"${CCACHE_EXECUTABLE}\" \"${CMAKE_CXX_COMPILER}\" \"$@\"\n"
  )
  execute_process(COMMAND chmod a+rx ${CMAKE_CURRENT_BINARY_DIR}/cxx)
  set(CMAKE_XCODE_ATTRIBUTE_CXX ${CMAKE_CURRENT_BINARY_DIR}/cxx)
  set(CMAKE_XCODE_ATTRIBUTE_LDPLUSPLUS ${CMAKE_CURRENT_BINARY_DIR}/cxx)
endif()
