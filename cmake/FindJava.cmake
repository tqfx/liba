#.rst:
# FindJava
# --------
#
# https://cmake.org/cmake/help/latest/module/FindJava.html
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``JAVA_EXECUTABLE``
#
# ``JAVA_BINDIR``
#
# ``JAVA_LIBDIR``
#
# ``JAVA_HOME``
#
include(${CMAKE_ROOT}/Modules/FindJava.cmake)
if(EXISTS "${Java_JAVAC_EXECUTABLE}" AND Java_JAVAH_EXECUTABLE STREQUAL "Java_JAVAH_EXECUTABLE-NOTFOUND")
  set(Java_JAVAH_EXECUTABLE "${Java_JAVAC_EXECUTABLE} -h" CACHE FILEPATH "Path to a program." FORCE)
endif()
if(EXISTS "${Java_JAVA_EXECUTABLE}")
  get_filename_component(JAVA_EXECUTABLE "${Java_JAVA_EXECUTABLE}" REALPATH)
  get_filename_component(JAVA_BINDIR "${JAVA_EXECUTABLE}" DIRECTORY)
  get_filename_component(JAVA_HOME "${JAVA_BINDIR}" DIRECTORY)
  set(JAVA_LIBDIR "${JAVA_HMOE}/lib")
  if(NOT DEFINED ENV{JAVA_HOME})
    set(ENV{JAVA_HOME} "${JAVA_HOME}")
  endif()
endif()
