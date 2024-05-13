#.rst:
# FindPython
# ----------
#
# https://cmake.org/cmake/help/latest/module/FindPythonInterp.html
# https://cmake.org/cmake/help/latest/module/FindPythonLibs.html
# https://cmake.org/cmake/help/latest/module/FindPython.html
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``Python_FOUND``
#
# ``Python_EXECUTABLE``
#
# ``Python_INCLUDE_DIRS``
#
# ``Python_LIBRARIES``
#
# ``Python_VERSION``
#
# ``Python_VERSION_MAJOR``
#
# ``Python_VERSION_MINOR``
#
# ``Python_VERSION_PATCH``
#
if(CMAKE_VERSION VERSION_LESS 3.12)
  set(PythonInterp_FIND_VERSION ${Python_FIND_VERSION})
  include(${CMAKE_ROOT}/Modules/FindPythonInterp.cmake)
  list(FIND Python_FIND_COMPONENTS Development Python_FOUND)
  if(${Python_FOUND} GREATER -1)
    list(INSERT Python_ADDITIONAL_VERSIONS 0 "${Python_FIND_VERSION}")
    list(INSERT Python_ADDITIONAL_VERSIONS 0 ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR})
    include(${CMAKE_ROOT}/Modules/FindPythonLibs.cmake)
    set(Python_Development_FOUND ${PYTHONLIBS_FOUND})
    set(Python_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS})
    set(Python_LIBRARIES ${PYTHON_LIBRARIES})
  endif()
  set(Python_VERSION_MAJOR ${PYTHON_VERSION_MAJOR})
  set(Python_VERSION_MINOR ${PYTHON_VERSION_MINOR})
  set(Python_VERSION_PATCH ${PYTHON_VERSION_PATCH})
  set(Python_VERSION ${PYTHON_VERSION_STRING})
  set(Python_EXECUTABLE ${PYTHON_EXECUTABLE})
  set(Python_FOUND ${PYTHONINTERP_FOUND})
else()
  include(${CMAKE_ROOT}/Modules/FindPython.cmake)
endif()
