function(file_scaner var)
  cmake_parse_arguments(FILE "RECURSE" "RELATIVE" "OPTIONS;DIR;EXT" ${ARGN})

  if(FILE_RELATIVE)
    list(APPEND FILE_OPTIONS RELATIVE ${FILE_RELATIVE})
  endif()

  string(REPLACE ";." ";" FILE_EXT ";${FILE_EXT};")
  foreach(dir ${FILE_DIR} ${FILE_UNPARSED_ARGUMENTS})
    foreach(ext ${FILE_EXT})
      list(APPEND FILE_OPTIONS "${dir}/*.${ext}")
    endforeach()
  endforeach()

  if(FILE_RECURSE)
    file(GLOB_RECURSE FILES ${FILE_OPTIONS})
  else()
    file(GLOB FILES ${FILE_OPTIONS})
  endif()

  set(${var} ${FILES} PARENT_SCOPE)
endfunction()

function(file_filter var)
  cmake_parse_arguments(FILE "" "VAR" "EXT" ${ARGN})

  set(FILES)
  string(REPLACE ";." ";" FILE_EXT ";${FILE_EXT};")
  foreach(arg ${${FILE_VAR}} ${FILE_UNPARSED_ARGUMENTS})
    get_filename_component(ext ${arg} EXT)
    string(REGEX REPLACE "^\\." "" ext "${ext}")
    list(FIND FILE_EXT "${ext}" index)
    if(${index} GREATER -1)
      list(APPEND FILES ${arg})
    endif()
  endforeach()

  set(${var} ${FILES} PARENT_SCOPE)
endfunction()
