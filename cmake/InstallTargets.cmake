include(GNUInstallDirs)
install(TARGETS ${INSTALL_TARGETS} EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(EXPORT ${PROJECT_NAME}-targets FILE ${PROJECT_NAME}-targets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
include(CMakePackageConfigHelpers)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake "\@PACKAGE_INIT\@\n"
  "include(\"\${CMAKE_CURRENT_LIST_DIR}/\@PROJECT_NAME\@-targets.cmake\")\n"
)
configure_package_config_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  VERSION ${PROJECT_VERSION} COMPATIBILITY AnyNewerVersion
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

function(install_fixup target define config)
  get_filename_component(config "${config}" NAME)
  install(CODE "file(READ \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/${target}\" text)
  string(REGEX REPLACE \"#if([defin\\t (]+)${define}([) \\t\\r\\n]*)\\n\" \"#include \\\"${config}\\\"\\n#if\\\\1${define}\\\\2\\n\" text \"\${text}\")
  file(WRITE \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/${target}\" \"\${text}\")")
endfunction()
