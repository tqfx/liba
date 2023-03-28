#!/usr/bin/env python
import sys, os, re


class single(object):
    undef_macros = []
    define_macros = []
    include_files = {}
    _include_dirs = []
    _include_files = []

    @property
    def include_dirs(self):
        return self._include_dirs

    @include_dirs.setter
    def include_dirs(self, values):
        for value in values:
            value = os.path.relpath(value)
            self._include_dirs.append(value)

    def read(self, name):
        self.name = os.path.relpath(name).replace("\\", "/")
        with open(self.name, "r") as f:
            self.source = f.read()
        return self

    def write(self, name):
        with open(name, "wb") as f:
            f.write(self.source.encode())
        return self

    def stdout(self):
        sys.stdout.write(self.source)

    def __call__(self, *args):
        macros = ""
        if args:
            name = args[0]
        else:
            name = self.name
        name = name.replace("\\", "/")
        if not os.path.exists(name):
            return ""
        if name in self._include_files:
            return ""
        if args:
            with open(name, "r") as f:
                source = f.read()
        else:
            source = self.source
        include_dirs = [os.path.dirname(name)] + self._include_dirs
        includes = re.findall(r"#include \"([^\"]+)\"", source)
        for include in includes:
            old = '#include "{}"\n'.format(include)
            for include_dir in include_dirs:
                new = os.path.join(include_dir, include)
                if not os.path.exists(new):
                    continue
                new = self.__call__(new)
                source = source.replace(old, new)
        self._include_files.append(name)
        if name == self.name:
            for define_macro in self.define_macros:
                macros += "#define %s\n" % define_macro
            for undef_macro in self.undef_macros:
                macros += "#undef %s\n" % undef_macro
            self.include_files[name] = {
                "header": tuple(self._include_files),
                "source": source,
            }
            self.source = macros + source
            self._include_files.clear()
        return source


if __name__ == "__main__":
    import argparse

    o = single()
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument("-D", default=[], action="append")
    parser.add_argument("-U", default=[], action="append")
    parser.add_argument("-I", default=[], action="append")
    parser.add_argument("-H")
    parser.add_argument("-C")
    parser.add_argument("-c")
    parser.add_argument("-O")
    parser.add_argument("-o")
    args = parser.parse_known_args()
    o.define_macros = args[0].D
    o.undef_macros = args[0].U
    o.include_dirs = args[0].I
    if args[0].c:
        o.read(args[0].c)()
        if args[0].o:
            o.write(args[0].o)
        elif args[0].O:
            outname = os.path.relpath(args[0].c)
            outname = os.path.join(args[0].O, outname)
            outpath = os.path.dirname(outname)
            os.makedirs(outpath, exist_ok=True)
            o.write(outname)
        else:
            o.stdout()
    if args[0].O and args[0].H:
        for dirpath, dirnames, filenames in os.walk(args[0].H):
            outpath = os.path.relpath(dirpath, args[0].H)
            outpath = os.path.join(args[0].O, outpath)
            os.makedirs(outpath, exist_ok=True)
            for filename in filenames:
                header = os.path.join(dirpath, filename)
                output = os.path.join(outpath, filename)
                prefix, suffix = os.path.splitext(header)
                if suffix in (".h", ".hh", ".hpp", ".hxx"):
                    o.read(header)()
                    o.write(output)
    if args[0].O and args[0].C:
        for dirpath, dirnames, filenames in os.walk(args[0].C):
            outpath = os.path.relpath(dirpath, args[0].C)
            outpath = os.path.join(args[0].O, outpath)
            os.makedirs(outpath, exist_ok=True)
            for filename in filenames:
                source = os.path.join(dirpath, filename)
                output = os.path.join(outpath, filename)
                prefix, suffix = os.path.splitext(source)
                if suffix in (".c", ".cc", ".cpp", ".cxx"):
                    o.read(source)()
                    o.write(output)
    if args[0].verbose:
        sources = " ".join(o.include_files)
        objects = ".o ".join(o.include_files) + ".o"
        for key in o.include_files:
            item = o.include_files[key]
            item = " ".join(reversed(item["header"]))
            sys.stderr.write(key + ".o:%s\n" % item)
        sys.stderr.write("SOURCES = %s\n" % sources)
        sys.stderr.write("OBJECTS = %s\n" % objects)
