vcpkg_from_git(OUT_SOURCE_PATH SOURCE_PATH
  URL https://github.com/tqfx/${PORT}.git
  REF @GIT_COMMIT_LONG@
  HEAD_REF main
)

vcpkg_check_features(OUT_FEATURE_OPTIONS OPTIONS_RELEASE
  FEATURES lto LIBA_LTO
)

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
  FEATURES
    pkgconfig LIBA_PKGCONFIG
    symlink LIBA_SYMLINK
)

vcpkg_configure_cmake(SOURCE_PATH ${SOURCE_PATH}
  OPTIONS -DBUILD_TESTING=OFF ${FEATURE_OPTIONS}
  OPTIONS_RELEASE ${OPTIONS_RELEASE}
)

vcpkg_install_cmake()

vcpkg_copy_pdbs()

if(LIBA_PKGCONFIG)
  vcpkg_fixup_pkgconfig()
endif()

vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/${PORT})

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

if(VCPKG_LIBRARY_LINKAGE STREQUAL "static")
  file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/bin" "${CURRENT_PACKAGES_DIR}/debug/bin")
endif()

file(INSTALL ${SOURCE_PATH}/LICENSE.txt DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
