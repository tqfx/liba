#!/usr/bin/env python
import sys, os, re

SUFFIXS = (".c", ".cc", ".cpp", ".cxx")
ROOT = os.path.abspath(sys.argv[0])
ROOT = os.path.dirname(ROOT)
ROOT = os.path.dirname(ROOT)


def main(index=0, SUFFIXS=SUFFIXS):
    sources = []
    for dirpath, dirnames, filenames in os.walk("src"):
        for filename in filenames:
            source = os.path.join(dirpath, filename)
            prefix, suffix = os.path.splitext(source)
            if suffix in SUFFIXS:
                sources.append(source.replace("\\", "/"))
    sources = sorted(sources)

    with open("build.rs", "r") as f:
        build = f.read()
    cur = re.findall(r"make([^;]+)\.compile\(\"a\"\)", build)[index]
    new = '.file("' + '")\n        .file("'.join(sources) + '")\n        '
    with open("build.rs", "wb") as f:
        build = f.write(build.replace(cur, new).encode())


os.chdir(ROOT)
main()
