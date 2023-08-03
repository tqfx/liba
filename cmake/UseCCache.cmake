include(${CMAKE_CURRENT_LIST_DIR}/FindCCache.cmake)
if(CCACHE_FOUND)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_EXECUTABLE}")
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY RULE_LAUNCH_LINK "${CCACHE_EXECUTABLE}")
endif()
if(CCACHE_FOUND AND CMAKE_GENERATOR STREQUAL "Xcode")
  set(CMAKE_XCODE_ATTRIBUTE_CC ${CMAKE_CURRENT_BINARY_DIR}/cc)
  set(CMAKE_XCODE_ATTRIBUTE_CXX ${CMAKE_CURRENT_BINARY_DIR}/cxx)
  include(${CMAKE_CURRENT_LIST_DIR}/TargetSupportsSymbolicLink.cmake)
  if(NOT TARGET_SUPPORTS_SYMBOLIC_LINK)
    include(${CMAKE_CURRENT_LIST_DIR}/TemporaryDirectory.cmake)
    if(EXISTS "${TEMPORARY_DIRECTORY}")
      string(MD5 hash "${CMAKE_CURRENT_BINARY_DIR}")
      set(CMAKE_XCODE_ATTRIBUTE_CC ${TEMPORARY_DIRECTORY}/cmake-${hash}/cc)
      set(CMAKE_XCODE_ATTRIBUTE_CXX ${TEMPORARY_DIRECTORY}/cmake-${hash}/cxx)
      set(hash)
    endif()
  endif()
  set(CMAKE_XCODE_ATTRIBUTE_LD ${CMAKE_XCODE_ATTRIBUTE_CC})
  file(WRITE ${CMAKE_XCODE_ATTRIBUTE_CC}
    "#!/usr/bin/env sh\n\n"
    "# Xcode generator doesn't include the compiler as the\n"
    "# first argument, Ninja and Makefiles do. Handle both cases.\n"
    "if [ \"$1\" = \"${CMAKE_C_COMPILER}\" ] ; then\n"
    "    shift\n"
    "fi\n\n"
    "export CCACHE_CPP2=true\n"
    "exec \"${CCACHE_EXECUTABLE}\" \"${CMAKE_C_COMPILER}\" \"$@\"\n"
  )
  execute_process(COMMAND chmod a+rx ${CMAKE_XCODE_ATTRIBUTE_CC})
  set(CMAKE_XCODE_ATTRIBUTE_LDPLUSPLUS ${CMAKE_XCODE_ATTRIBUTE_CXX})
  file(WRITE ${CMAKE_XCODE_ATTRIBUTE_CXX}
    "#!/usr/bin/env sh\n\n"
    "# Xcode generator doesn't include the compiler as the\n"
    "# first argument, Ninja and Makefiles do. Handle both cases.\n"
    "if [ \"$1\" = \"${CMAKE_CXX_COMPILER}\" ] ; then\n"
    "    shift\n"
    "fi\n\n"
    "export CCACHE_CPP2=true\n"
    "exec \"${CCACHE_EXECUTABLE}\" \"${CMAKE_CXX_COMPILER}\" \"$@\"\n"
  )
  execute_process(COMMAND chmod a+rx ${CMAKE_XCODE_ATTRIBUTE_CXX})
endif()
