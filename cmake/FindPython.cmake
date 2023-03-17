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
# ``PYTHON_FOUND``, ``Python_FOUND``
#
# ``PYTHON_EXECUTABLE``, ``Python_EXECUTABLE``
#
if(CMAKE_VERSION VERSION_LESS 3.12)
  set(PythonInterp_FIND_VERSION ${Python_FIND_VERSION})
  include(${CMAKE_ROOT}/Modules/FindPythonInterp.cmake)
  list(FIND Python_FIND_COMPONENTS Development PYTHON_FOUND)
  if(${PYTHON_FOUND} GREATER -1)
    list(INSERT Python_ADDITIONAL_VERSIONS 0 ${Python_FIND_VERSION})
    list(INSERT Python_ADDITIONAL_VERSIONS 0 ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR})
    include(${CMAKE_ROOT}/Modules/FindPythonLibs.cmake)
  endif()
  set(Python_EXECUTABLE ${PYTHON_EXECUTABLE})
  set(PYTHON_FOUND ${PYTHONINTERP_FOUND})
  set(Python_FOUND ${PYTHONINTERP_FOUND})
else()
  include(${CMAKE_ROOT}/Modules/FindPython.cmake)
  set(PYTHON_EXECUTABLE ${Python_EXECUTABLE})
  set(PYTHON_FOUND ${Python_FOUND})
endif()
