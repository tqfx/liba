#.rst:
# FindGit
# -------
#
# https://cmake.org/cmake/help/latest/module/FindGit.html
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``GIT_BRANCH``
#
# ``GIT_COMMIT``
#
# ``GIT_COMMIT_LONG``
#
# ``GIT_COMMIT_DATE``
#
# Functions
# ^^^^^^^^^
#
# .. command:: git_command
#
#   ::
#
#     git_command(variable [arg...])
#
include(${CMAKE_ROOT}/Modules/FindGit.cmake)
if(GIT_FOUND)
  function(git_command output)
    execute_process(ERROR_QUIET
      COMMAND ${GIT_EXECUTABLE} ${ARGN}
      OUTPUT_STRIP_TRAILING_WHITESPACE
      OUTPUT_VARIABLE ${output}
    )
    set(${output} ${${output}} PARENT_SCOPE)
  endfunction()
  git_command(GIT_BRANCH branch --show-current)
  git_command(GIT_COMMIT log -1 --pretty=format:%h)
  git_command(GIT_COMMIT_LONG log -1 --pretty=format:%H)
  git_command(GIT_COMMIT_DATE log -1 --pretty=format:%cd --date=format:%Y%m%d%H%M)
endif()
