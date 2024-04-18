from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake


class aConan(ConanFile):
    name = "liba"
    version = "0.1.11"
    license = "MPL-2.0"
    topics = ("algorithm",)
    author = "tqfx tqfx@tqfx.org"
    homepage = url = "https://github.com/tqfx/liba.git"
    description = "An algorithm library based on C/C++"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [0, 1],
        "fPIC": [0, 1],
        "ipo": [0, 1],
        "symlink": [0, 1],
        "pkgconfig": [0, 1],
    }
    default_options = {
        "shared": 0,
        "fPIC": 1,
        "ipo": 0,
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
        if self.settings.os == "Windows":
            del self.options.fPIC

    def generate(self):
        cmake = CMakeToolchain(self)
        cmake.variables["BUILD_TESTING"] = 0
        if self.options.shared:
            cmake.variables["LIBA_INSTALL"] = "shared"
        else:
            cmake.variables["LIBA_INSTALL"] = "static"
        cmake.variables["LIBA_SYMLINK"] = self.options.symlink
        cmake.variables["LIBA_PKGCONFIG"] = self.options.pkgconfig
        if self.settings.build_type != "Debug":
            cmake.variables["LIBA_IPO"] = self.options.ipo
        else:
            cmake.variables["LIBA_IPO"] = 0
        cmake.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["a"]
        if self.settings.os != "Windows":
            self.cpp_info.system_libs = ["m"]
        if self.options.shared:
            if self.settings.os == "Windows":
                self.cpp_info.libs = ["liba"]
            self.cpp_info.defines = ["A_IMPORTS"]
            self.cpp_info.set_property("cmake_target_name", "liba")
        else:
            self.cpp_info.set_property("cmake_target_name", "alib")
        if self.options.pkgconfig:
            self.cpp_info.set_property("pkg_config_name", "liba")
