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
# ``Python_Interpreter_FOUND``
#
# ``Python_EXECUTABLE``
#
# ``Python_Development_FOUND``
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
  if(NOT Python_FIND_COMPONENTS)
    set(Python_FIND_COMPONENTS Interpreter)
  endif()
  foreach(module ${Python_FIND_COMPONENTS})
    if(module MATCHES "Interpreter")
      set(PythonInterp_FIND_VERSION ${Python_FIND_VERSION})
      include(${CMAKE_ROOT}/Modules/FindPythonInterp.cmake)
      set(Python_Interpreter_FOUND ${PYTHONINTERP_FOUND})
      set(Python_VERSION_MAJOR ${PYTHON_VERSION_MAJOR})
      set(Python_VERSION_MINOR ${PYTHON_VERSION_MINOR})
      set(Python_VERSION_PATCH ${PYTHON_VERSION_PATCH})
      set(Python_VERSION ${PYTHON_VERSION_STRING})
      set(Python_EXECUTABLE ${PYTHON_EXECUTABLE})
      if(Python_FIND_REQUIRED_Interpreter)
        list(APPEND Python_REQUIRED_VARS
          Python_EXECUTABLE
        )
      endif()
    endif()
    if(module MATCHES "Development")
      list(INSERT Python_ADDITIONAL_VERSIONS 0 "${Python_FIND_VERSION}")
      include(${CMAKE_ROOT}/Modules/FindPythonLibs.cmake)
      set(Python_Development_FOUND ${PYTHONLIBS_FOUND})
      set(Python_VERSION ${PYTHONLIBS_VERSION_STRING})
      set(Python_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS})
      set(Python_LIBRARIES ${PYTHON_LIBRARIES})
      if(Python_FIND_REQUIRED_Development)
        list(APPEND Python_REQUIRED_VARS
          Python_INCLUDE_DIRS
          Python_LIBRARIES
        )
      endif()
    endif()
  endforeach()
  find_package_handle_standard_args(Python
    FOUND_VAR
      Python_FOUND
    REQUIRED_VARS
      ${Python_REQUIRED_VARS}
    VERSION_VAR
      Python_VERSION
    HANDLE_COMPONENTS
  )
else()
  include(${CMAKE_ROOT}/Modules/FindPython.cmake)
endif()
