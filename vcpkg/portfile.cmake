set(VCPKG_POLICY_ALLOW_OBSOLETE_MSVCRT enabled)

vcpkg_from_git(OUT_SOURCE_PATH SOURCE_PATH
  URL https://github.com/tqfx/${PORT}
  REF @GIT_COMMIT_LONG@
  HEAD_REF main
)

vcpkg_check_features(OUT_FEATURE_OPTIONS OPTIONS_RELEASE
  FEATURES ipo LIBA_IPO
)

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
  FEATURES
    pkgconfig LIBA_PKGCONFIG
    symlink LIBA_SYMLINK
    float LIBA_REAL
)

if(LIBA_REAL)
  string(REGEX REPLACE "REAL=([^;]+)" "REAL=4"
    FEATURE_OPTIONS "${FEATURE_OPTIONS}"
  )
else()
  string(REGEX REPLACE "REAL=([^;]+)" "REAL=8"
    FEATURE_OPTIONS "${FEATURE_OPTIONS}"
  )
endif()

vcpkg_cmake_configure(SOURCE_PATH ${SOURCE_PATH}
  OPTIONS -DBUILD_TESTING=OFF ${FEATURE_OPTIONS}
  OPTIONS_RELEASE ${OPTIONS_RELEASE}
)

vcpkg_cmake_install()

vcpkg_copy_pdbs()

if(LIBA_PKGCONFIG)
  vcpkg_fixup_pkgconfig()
endif()

vcpkg_cmake_config_fixup(CONFIG_PATH lib/cmake/${PORT})

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

if(VCPKG_LIBRARY_LINKAGE STREQUAL "static")
  file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/bin" "${CURRENT_PACKAGES_DIR}/debug/bin")
endif()

file(INSTALL ${SOURCE_PATH}/LICENSE.txt DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
