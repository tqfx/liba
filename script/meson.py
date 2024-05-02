#!/usr/bin/env python
import sys, os, re

SUFFIXS = (".c", ".h", ".cc", ".hh", ".cpp", ".hpp", ".cxx", ".hxx")
ROOT = os.path.abspath(sys.argv[0])
ROOT = os.path.dirname(ROOT)
ROOT = os.path.dirname(ROOT)


def main():
    sources = []
    for dirpath, dirnames, filenames in os.walk("include"):
        for filename in filenames:
            source = os.path.join(dirpath, filename)
            prefix, suffix = os.path.splitext(source)
            if suffix in SUFFIXS:
                sources.append(source.replace("\\", "/"))
    for dirpath, dirnames, filenames in os.walk("src"):
        for filename in filenames:
            source = os.path.join(dirpath, filename)
            prefix, suffix = os.path.splitext(source)
            if suffix in SUFFIXS:
                sources.append(source.replace("\\", "/"))
    sources = sorted(sources)

    with open("meson.build", "r") as f:
        meson = f.read()
    cur = re.findall(r"sources = ([^\]]+)", meson)[0] + "]\n"
    new = "[\n    '" + "',\n    '".join(sources) + "',\n]\n"
    with open("meson.build", "wb") as f:
        meson = f.write(meson.replace(cur, new).encode())


os.chdir(ROOT + "/java")
main()
os.chdir(ROOT + "/lua")
main()
os.chdir(ROOT + "/quickjs")
main()
os.chdir(ROOT)
main()
