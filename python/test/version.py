#!/usr/bin/env python
import os, sys

sys.path.insert(0, os.getcwd())
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba

print("version", liba.VERSION)
print("major:", liba.VERSION_MAJOR)
print("minor:", liba.VERSION_MINOR)
print("patch:", liba.VERSION_PATCH)
print("tweak:", liba.VERSION_TWEAK)
assert liba.version(1) > liba.version()
assert liba.version() < liba.version(1)
assert liba.version(1) >= liba.version()
assert liba.version() <= liba.version(1)
assert liba.version(0) == liba.version()
assert liba.version(1) != liba.version()
print(liba.version())
print(liba.version(1))
print(liba.version(1, 2))
print(liba.version(1, 2, 3))
print(liba.version_check())
