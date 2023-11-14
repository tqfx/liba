#!/usr/bin/env python
import os, sys

sys.path.insert(0, os.getcwd())
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba

print(liba.f64.rsqrt(4), liba.f32.rsqrt(4))
print(liba.f64.rsqrt([4, 8]), liba.f32.rsqrt([4, 8]))
print(liba.hash.bkdr(b"0", 0), liba.u32.sqrt(3), liba.u64.sqrt(7))
