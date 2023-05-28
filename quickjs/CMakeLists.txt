set(CMAKE_SHARED_LIBRARY_SUFFIX .so)

if(WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX lib)
endif()

if(LIBA_CXX)
  file_scaner(SOURCES RECURSE src EXT c h cc hh cpp hpp)
else()
  file_scaner(SOURCES RECURSE src EXT c h)
endif()

add_library(aqjs SHARED $<TARGET_OBJECTS:a> ${SOURCES})
set_target_properties(aqjs PROPERTIES DEFINE_SYMBOL A_EXPORTS OUTPUT_NAME a)
target_link_libraries(aqjs PRIVATE quickjs)
add_library_properties(aqjs PRIVATE alib)
set_library_options(aqjs)

if(QJS_EXECUTABLE)
  add_subdirectory(test)
endif()
