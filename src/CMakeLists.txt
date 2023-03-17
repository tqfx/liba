get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)

foreach(lang ${ENABLED_LANGUAGES})
  set(CMAKE_${lang}_CREATE_STATIC_LIBRARY "<CMAKE_${lang}_COMPILER> <LANGUAGE_COMPILE_FLAGS> -nostdlib -o <TARGET> -r <OBJECTS>")
endforeach()

set(CMAKE_STATIC_LIBRARY_SUFFIX .o)
add_library(aobj STATIC $<TARGET_OBJECTS:a>)
add_library_properties(aobj INTERFACE alib INTERFACE_)
set_target_properties(aobj PROPERTIES OUTPUT_NAME a
  INTERPROCEDURAL_OPTIMIZATION ${LIBA_LTO}
)

if(A_HAVE_MIMALLOC_H)
  target_link_libraries(aobj PUBLIC mimalloc-static)
endif()

include(GNUInstallDirs)
install(TARGETS aobj EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
