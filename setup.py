#!/usr/bin/env python
from sys import argv
import os, sys, time

os.chdir(os.path.dirname(os.path.abspath(argv[0])))
if len(argv) < 2 and sys.version.find("MSC") > 0:
    sys.argv += ["--quiet", "build_ext", "--inplace"]
elif len(argv) < 2:
    sys.argv += ["build_ext", "--inplace"]
try:
    from setuptools.command.build_ext import build_ext
    from setuptools import setup, Extension
except ImportError:
    from distutils.command.build_ext import build_ext
    from distutils.extension import Extension
    from distutils.core import setup
try:
    USE_CYTHON = True
    from sys import version_info
    from Cython.Build import cythonize
except:
    USE_CYTHON = False
from argparse import ArgumentParser
from sys import byteorder
from re import findall
import ctypes.util
import ctypes


def check_math(define_macros=[]):
    if sys.platform == "win32":
        path_libm = ctypes.util.find_library("ucrtbase")
        if not path_libm:
            path_libm = ctypes.util.find_msvcrt()
    else:
        path_libm = ctypes.util.find_library("m")
    text = "#define A_HAVE_COMPLEX_H 1\n"
    text += "#define A_HAVE_STDINT_H 1\n"
    try:
        libm = ctypes.CDLL(path_libm)
    except:
        return text
    A_SIZE_FLOAT = 0x08
    for define_macro in define_macros:
        if "A_SIZE_FLOAT" in define_macro:
            A_SIZE_FLOAT = int(define_macro[-1])
            break
    for func in (
        "hypot",
        "log1p",
        "atan2",
        "csqrt",
        "cpow",
        "cexp",
        "clog",
        "csin",
        "ccos",
        "ctan",
        "csinh",
        "ccosh",
        "ctanh",
        "casin",
        "cacos",
        "catan",
        "casinh",
        "cacosh",
        "catanh",
    ):
        name = "A_HAVE_" + func.upper()
        if A_SIZE_FLOAT == 0x10:
            func += "l"
        if A_SIZE_FLOAT == 0x04:
            func += "f"
        try:
            libm[func]
        except:
            continue
        text += "#define %s 1\n" % (name)
    return text


def configure(config, define_macros=[]):
    with open("setup.cfg", "r") as f:
        version = findall(r"version = (.+)", f.read())[0]
    major, minor, patch = findall(r"(\d+).(\d+).(\d+)", version)[0]
    order = {"little": 1234, "big": 4321}.get(byteorder)
    vsize = ctypes.sizeof(ctypes.c_void_p(0))
    tweak = time.strftime("%Y%m%d%H%M")
    check = check_math(define_macros)
    text = """/* autogenerated by setup.py */
#define A_VERSION "{}"
#define A_VERSION_MAJOR {}
#define A_VERSION_MINOR {}
#define A_VERSION_PATCH {}
#define A_VERSION_TWEAK A_U64_C({})
#if !defined A_SIZE_POINTER
#define A_SIZE_POINTER {}
#endif /* A_SIZE_POINTER */
#if !defined A_BYTE_ORDER
#define A_BYTE_ORDER {}
#endif /* A_BYTE_ORDER */
{}""".format(
        version, major, minor, patch, tweak, vsize, order, check
    )
    with open(config, "wb") as f:
        f.write(text.encode("UTF-8"))


parser = ArgumentParser(add_help=False)
parser.add_argument("-b", "--build-base", default="build")
args = parser.parse_known_args(argv[1:])
base = args[0].build_base

sources, objects = [], []
config_h = os.path.relpath(os.path.join(base, "a.setup.h"), "include")
define_macros = [("A_HAVE_H", '"' + config_h + '"'), ("A_EXPORTS", None)]
if USE_CYTHON and os.path.exists("python/src/a.pyx"):
    sources += ["python/src/a.pyx"]
elif os.path.exists("python/src/a.c"):
    sources += ["python/src/a.c"]
config = os.path.join(base, config_h)
if not os.path.exists(base):
    os.makedirs(base)
configure(config, define_macros)

for dirpath, dirnames, filenames in os.walk("src"):
    for filename in filenames:
        source = os.path.join(dirpath, filename)
        if os.path.splitext(source)[-1] == ".c":
            sources.append(source)

ext_modules = [
    Extension(
        name="liba",
        language="c",
        sources=sources,
        include_dirs=["include"],
        define_macros=define_macros,
    )
]
if USE_CYTHON:
    ext_modules = cythonize(  # type: ignore
        ext_modules,
        language_level=version_info[0],  # type: ignore
        quiet=True,
    )


class Build(build_ext):  # type: ignore
    def build_extensions(self):
        if self.compiler.compiler_type == "msvc":
            for e in self.extensions:
                if e.language == "c":
                    e.extra_compile_args += ["/std:c11"]
        if not self.compiler.compiler_type == "msvc":
            for e in self.extensions:
                if e.language == "c++":
                    e.extra_compile_args += ["-std=c++11"]
                elif e.language == "c":
                    e.extra_compile_args += ["-std=c11"]
        if self.compiler.compiler_type == "mingw32":
            self.compiler.define_macro("__USE_MINGW_ANSI_STDIO", 1)
            for e in self.extensions:
                if e.language == "c++":
                    e.extra_link_args += ["-static-libstdc++"]
                e.extra_link_args += ["-static-libgcc"]
                e.extra_link_args += [
                    "-Wl,-Bstatic,--whole-archive",
                    "-lwinpthread",
                    "-Wl,--no-whole-archive",
                ]
        build_ext.build_extensions(self)


setup(
    ext_modules=ext_modules,  # type: ignore
    cmdclass={"build_ext": Build},
)
