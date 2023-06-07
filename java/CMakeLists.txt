# https://cmake.org/cmake/help/latest/module/UseJava.html
include(UseJava)

file(GLOB_RECURSE SOURCES src/*.java)
add_jar(ajar GENERATE_NATIVE_HEADERS ajar_native
  ENTRY_POINT a OUTPUT_NAME a SOURCES ${SOURCES}
)
install_jar(ajar ${CMAKE_INSTALL_LIBDIR}/java)

option(LIBA_JAVADOC "Enable/Disable ffi javadoc" 0)

if(LIBA_JAVADOC)
  create_javadoc(${PROJECT_NAME} FILES ${SOURCES}
    INSTALLPATH ${CMAKE_INSTALL_DATADIR}/javadoc
  )
  add_dependencies(adoc ${PROJECT_NAME}_javadoc)
endif()

if(WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX)
endif()

if(LIBA_FLOAT EQUAL 8)
  set(OBJECTS $<TARGET_OBJECTS:a>)
else()
  get_property(OBJECTS TARGET a PROPERTY SOURCES)
endif()

if(LIBA_CXX)
  file_scaner(SOURCES RECURSE src EXT c h cc hh cpp hpp)
else()
  file_scaner(SOURCES RECURSE src EXT c h)
endif()

add_library(ajni SHARED ${OBJECTS} ${SOURCES})
set_target_properties(ajni PROPERTIES DEFINE_SYMBOL A_EXPORTS OUTPUT_NAME a)
target_link_libraries(ajni PRIVATE ajar_native)
add_library_properties(ajni PRIVATE alib)
set_library_options(ajni)

if(NOT LIBA_FLOAT EQUAL 8)
  target_compile_definitions(ajni PRIVATE A_SIZE_FLOAT=8)
endif()

install(TARGETS ajni
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/java
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/java
)

execute_process(COMMAND ${Java_JAVA_EXECUTABLE} -version
  OUTPUT_VARIABLE version ERROR_VARIABLE version
)
string(FIND "${version}" "64-Bit" index)

if(${index} GREATER -1)
  set(JAVA_SIZEOF_VOID_P 8) # 64
else()
  set(JAVA_SIZEOF_VOID_P 4) # 32
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL JAVA_SIZEOF_VOID_P AND BUILD_TESTING)
  file(GLOB_RECURSE SOURCES src/*.java)
  add_subdirectory(test)
endif()
