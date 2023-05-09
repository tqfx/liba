#!/usr/bin/env python
import os, sys
from typing import Any

sys.path.insert(0, os.getcwd())
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba

print("version", liba.version())
print("major:", liba.version_major())
print("minor:", liba.version_minor())
print("patch:", liba.version_patch())

print(liba.f64_rsqrt(4), liba.f32_rsqrt(4))
