from conans import ConanFile, CMake, tools


class aConan(ConanFile):
    name = "liba"
    version = "0.1.1"
    license = "MPL-2.0"
    author = "tqfx tqfx@foxmail.com"
    homepage = url = "https://github.com/tqfx/liba.git"
    description = "An algorithm library based on C/C++ language"
    topics = ("algorithm",)
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [0, 1],
        "fPIC": [0, 1],
        "lto": [0, 1],
        "symlink": [0, 1],
        "pkgconfig": [0, 1],
    }
    default_options = {
        "shared": 0,
        "fPIC": 1,
        "lto": 0,
        "symlink": 0,
        "pkgconfig": 1,
    }
    exports_sources = (
        "CMakeLists.txt",
        "LICENSE.txt",
        "README.md",
        "include/*",
        "cmake/*",
        "src/*",
    )

    def config_options(self):
        if self.settings.os == "Windows":  # type: ignore
            del self.options.fPIC  # type: ignore

    def source(self):
        CMakeLists_txt = str(tools.load("CMakeLists.txt"))
        if "conan_basic_setup" not in CMakeLists_txt:
            CMakeLists_txt = CMakeLists_txt.replace(
                "include(cmake/CMakeExportCompileCommands.cmake)\n",
                "include(cmake/CMakeExportCompileCommands.cmake)\n"
                "include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)\n"
                "conan_basic_setup()\n",
            )
        tools.save("CMakeLists.txt", CMakeLists_txt)

    def build(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_TESTING"] = 0
        cmake.definitions["LIBA_SYMLINK"] = self.options.symlink  # type: ignore
        cmake.definitions["LIBA_PKGCONFIG"] = self.options.pkgconfig  # type: ignore
        if self.settings.build_type != "Debug":  # type: ignore
            cmake.definitions["LIBA_LTO"] = self.options.lto  # type: ignore
        else:
            cmake.definitions["LIBA_LTO"] = 0
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
