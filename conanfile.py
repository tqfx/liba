from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake


class Conan(ConanFile):
    name = "liba"
    version = "0.1.12"
    license = "MPL-2.0"
    topics = ["algorithm"]
    author = "tqfx tqfx@tqfx.org"
    homepage = url = "https://github.com/tqfx/liba"
    description = "An algorithm library based on C/C++"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "pkgconfig": [0, 1],
        "symlink": [0, 1],
        "shared": [0, 1],
        "float": [4, 8],
        "ipo": [0, 1],
    }
    default_options = {
        "pkgconfig": 1,
        "symlink": 0,
        "shared": 0,
        "float": 8,
        "ipo": 0,
    }
    exports_sources = [
        "include/a.cmake.h.in",
        "include/a/*.h*",
        "CMakeLists.txt",
        "cmake/*.cmake",
        "src/*.[ch]*",
        "LICENSE.txt",
        "README.md",
    ]

    def generate(self):
        cmake = CMakeToolchain(self)
        cmake.variables["BUILD_TESTING"] = 0
        if self.options.shared:
            cmake.variables["LIBA_INSTALL"] = "shared"
        else:
            cmake.variables["LIBA_INSTALL"] = "static"
        if self.options.float != 8:
            cmake.variables["LIBA_FLOAT"] = self.options.float
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
