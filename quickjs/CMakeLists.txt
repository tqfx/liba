include(../cmake/QuickJSPIC.cmake)
set(CMAKE_SHARED_MODULE_SUFFIX .so)

if(WIN32)
  set(CMAKE_SHARED_MODULE_PREFIX lib)
endif()

if(LIBA_CXX)
  file_scaner(SOURCES RECURSE src EXT c h cc hh cpp hpp)
else()
  file_scaner(SOURCES RECURSE src EXT c h)
endif()

add_library(aqjs MODULE $<TARGET_OBJECTS:a> ${SOURCES})
set_target_properties(aqjs PROPERTIES DEFINE_SYMBOL A_EXPORTS OUTPUT_NAME a)
target_include_directories(aqjs PRIVATE ${QUICKJS_INCLUDE_DIR})
add_library_properties(aqjs PRIVATE alib)
set_library_options(aqjs)

if(QUICKJS_PIC)
  target_link_libraries(aqjs PRIVATE ${QUICKJS_LIBRARIES})
endif()

if("${LIBA_INSTALL}" MATCHES "^$|[Qq]uick[Jj][Ss]")
  install(TARGETS aqjs
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/quickjs
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/quickjs
  )
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/test/CMakeLists.txt AND QJS_EXECUTABLE)
  get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

  if(NOT CMAKE_VERSION VERSION_LESS 3.0)
    set(WORKING_DIRECTORY $<TARGET_FILE_DIR:aqjs>)
  elseif(IS_MULTI_CONFIG)
    set(WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
  else()
    set(WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  endif()

  add_subdirectory(test)
endif()
