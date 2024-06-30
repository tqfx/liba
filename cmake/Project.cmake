set(PROJECT_VERSION 0.1.14)
set(PROJECT_LICENSE MPL-2.0)
set(PROJECT_CONTACT tqfx@tqfx.org)
set(PROJECT_DESCRIPTION "An algorithm library based on C/C++")
set(PROJECT_HOMEPAGE_URL "https://github.com/tqfx/liba")
string(REGEX MATCHALL "[0-9]+" VERSION "${PROJECT_VERSION}")
list(GET VERSION 0 PROJECT_VERSION_MAJOR)
list(GET VERSION 1 PROJECT_VERSION_MINOR)
list(GET VERSION 2 PROJECT_VERSION_PATCH)
if(PROJECT_NAME)
  set(${PROJECT_NAME}_VERSION ${PROJECT_VERSION})
  set(${PROJECT_NAME}_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(${PROJECT_NAME}_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(${PROJECT_NAME}_VERSION_PATCH ${PROJECT_VERSION_PATCH})
endif()
if(PROJECT_NAME)
  set(${PROJECT_NAME}_DESCRIPTION ${PROJECT_DESCRIPTION})
endif()
if(PROJECT_NAME)
  set(${PROJECT_NAME}_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL})
endif()
if(PROJECT_NAME)
  set(${PROJECT_NAME}_LICENSE ${PROJECT_LICENSE})
endif()
if(CMAKE_VERSION VERSION_LESS 3.21)
  if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(PROJECT_IS_TOP_LEVEL 1)
  else()
    set(PROJECT_IS_TOP_LEVEL 0)
  endif()
endif()
if(CMAKE_C_COMPILER_ID MATCHES "TinyCC")
  string(FIND CMAKE_C_FLAGS "-std=c${CMAKE_C_STANDARD}" found)
  if(${found} EQUAL -1)
    string(STRIP "${CMAKE_C_FLAGS} -std=c${CMAKE_C_STANDARD}" CMAKE_C_FLAGS)
  endif()
endif()
if(CMAKE_VERSION VERSION_LESS 3.1 AND CMAKE_C_COMPILER_ID MATCHES "GNU|[Cc]lang|LLVM")
  string(FIND CMAKE_C_FLAGS "-std=c${CMAKE_C_STANDARD}" found)
  if(${found} EQUAL -1)
    string(STRIP "${CMAKE_C_FLAGS} -std=c${CMAKE_C_STANDARD}" CMAKE_C_FLAGS)
  endif()
endif()
if(CMAKE_VERSION VERSION_LESS 3.1 AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|[Cc]lang|LLVM")
  string(FIND CMAKE_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD}" found)
  if(${found} EQUAL -1)
    string(STRIP "${CMAKE_CXX_FLAGS} -std=c++${CMAKE_CXX_STANDARD}" CMAKE_CXX_FLAGS)
  endif()
endif()
if(NOT CMAKE_PROJECT_VERSION_PATCH AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_VERSION_PATCH ${PROJECT_VERSION_PATCH} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
if(NOT CMAKE_PROJECT_VERSION_MINOR AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_VERSION_MINOR ${PROJECT_VERSION_MINOR} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
if(NOT CMAKE_PROJECT_VERSION_MAJOR AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
if(NOT CMAKE_PROJECT_HOMEPAGE_URL AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
if(NOT CMAKE_PROJECT_DESCRIPTION AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_DESCRIPTION ${PROJECT_DESCRIPTION} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
if(NOT CMAKE_PROJECT_VERSION AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_VERSION ${PROJECT_VERSION} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
set(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME ${PROJECT_NAME})
set(CPACK_RPM_PACKAGE_LICENSE ${PROJECT_LICENSE})
set(CPACK_PACKAGE_CONTACT ${PROJECT_CONTACT})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
