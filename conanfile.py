from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake


class aConan(ConanFile):
    name = "liba"
    version = "0.1.6"
    license = "MPL-2.0"
    topics = ("algorithm",)
    author = "tqfx tqfx@tqfx.org"
    homepage = url = "https://github.com/tqfx/liba.git"
    description = "An algorithm library based on C/C++ language"
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
        if self.settings.os == "Windows":  # type: ignore
            del self.options.fPIC  # type: ignore

    def generate(self):
        cmake = CMakeToolchain(self)
        cmake.variables["BUILD_TESTING"] = 0
        cmake.variables["LIBA_SYMLINK"] = self.options.symlink  # type: ignore
        cmake.variables["LIBA_PKGCONFIG"] = self.options.pkgconfig  # type: ignore
        if self.settings.build_type != "Debug":  # type: ignore
            cmake.variables["LIBA_IPO"] = self.options.ipo  # type: ignore
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
