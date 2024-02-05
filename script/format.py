#!/usr/bin/env python
from subprocess import Popen
from typing import Any, Iterable
from glob import glob
from sys import argv, executable
import os


class format:
    SUFFIX = (".c", ".h", ".cc", ".hh", ".cpp", ".hpp", ".cxx", ".hxx")

    def __init__(self, dirs: Any) -> None:
        self.sources = set()
        if isinstance(dirs, Iterable):
            for path in dirs:
                self.scan(path)

    def __call__(self) -> Any:
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

    def scan(self, path: str) -> Any:
        for source in glob(os.path.join(path, "**"), recursive=True):
            if os.path.splitext(source)[-1] in self.SUFFIX:
                self.sources.add(os.path.relpath(source))
        return self


if __name__ == "__main__":
    format(
        [
            "include",
            "src",
            "test",
            "lua",
            "java",
            "quickjs",
            "javascript",
        ]
        + argv[1:]
    )()
