#!/usr/bin/env python
from __future__ import print_function
import os, sys

path = os.path.dirname(__file__)
path = os.path.dirname(path)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

print("version", liba.VERSION)
print("major:", liba.version.MAJOR)
print("minor:", liba.version.MINOR)
print("patch:", liba.version.PATCH)
print("tweak:", liba.version.TWEAK)
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
print(liba.version.check())
v = liba.version()
v.parse(b"1.2.3")
v.major = v.major
v.minor = v.minor
v.third = v.third
v.extra = v.extra
v.alpha = v.alpha
