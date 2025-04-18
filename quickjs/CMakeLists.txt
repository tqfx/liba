if(LIBA_WITH_QUICKJS)
  include(${CMAKE_CURRENT_LIST_DIR}/quickjs.cmake)
  add_subdirectory(${QUICKJS_SOURCE_DIR} ${QUICKJS_BINARY_DIR})
  set(QJS_EXECUTABLE ${CMAKE_CROSSCOMPILING_EMULATOR} $<TARGET_FILE:qjs>)
else()
  include(../cmake/QuickJSPIC.cmake)
endif()

if(LIBA_REAL EQUAL 8)
  set(OBJECTS $<TARGET_OBJECTS:a>)
else()
  get_property(OBJECTS TARGET a PROPERTY SOURCES)
endif()

if(LIBA_CXX)
  file_scaner(SOURCES RECURSE src EXT c h cc hh cpp hpp)
else()
  file_scaner(SOURCES RECURSE src EXT c h)
endif()

set(CMAKE_SHARED_MODULE_PREFIX "")
set(CMAKE_SHARED_MODULE_SUFFIX .so)
add_library(aqjs MODULE ${OBJECTS} ${SOURCES})
set_target_properties(aqjs PROPERTIES DEFINE_SYMBOL A_EXPORTS OUTPUT_NAME ${PROJECT_NAME})
target_include_directories(aqjs PRIVATE ${QUICKJS_INCLUDE_DIR})
add_library_properties(aqjs PRIVATE alib)
set_library_options(aqjs)

if(NOT LIBA_REAL EQUAL 8)
  target_compile_definitions(aqjs PRIVATE A_SIZE_REAL=8)
endif()

if(LIBA_WITH_QUICKJS OR QUICKJS_PIC)
  if(LIBA_IPO)
    target_link_libraries(aqjs PRIVATE quickjs.lto)
  else()
    target_link_libraries(aqjs PRIVATE quickjs)
  endif()
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
