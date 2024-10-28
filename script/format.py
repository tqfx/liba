#!/usr/bin/env python
from subprocess import Popen
from glob import glob
from sys import argv, executable
import os


class format:
    SUFFIX = (".c", ".h", ".cc", ".hh", ".cpp", ".hpp", ".cxx", ".hxx")

    def __init__(self, dirs: [str]) -> None:
        self.sources = set()
        if hasattr({}, "__contains__"):
            for path in dirs:
                self.scan(path)

    def __call__(self) -> format:
        script = ("clang-format", "--verbose", "-style=file", "-i")
        script += tuple(sorted(self.sources))
        try:
            Popen(script).wait()
        except Exception as e:
            print(e)
        script = (executable, "-m", "black", os.getcwd())
        try:
            Popen(script).wait()
        except Exception as e:
            print(e)
        return self

    def scan(self, path: str) -> format:
        for source in glob(os.path.join(path, "**"), recursive=True):
            if os.path.splitext(source)[-1] in self.SUFFIX:
                self.sources.add(os.path.relpath(source))
        return self


if __name__ == "__main__":
    dirs = [
        "include",
        "src",
        "test",
        "lua/src",
        "java/src",
        "quickjs/src",
        "javascript/src",
    ]
    format(dirs + argv[1:])()
