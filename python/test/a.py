#!/usr/bin/env python
from __future__ import print_function
import os, sys

path = os.path.dirname(__file__)
path = os.path.dirname(path)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

u32_48 = liba.new_u32([4, 8])
u64_48 = liba.new_u64([4, 8])
f32_48 = liba.new_f32([4, 8])
f64_48 = liba.new_f64([4, 8])

print(liba.hash_bkdr("0123456789"))
print(liba.hash_sdbm("0123456789"))
print(liba.sqrt_u64(7), liba.sqrt_u32(7))
print(list(liba.sqrt_u64(u64_48)), list(liba.sqrt_u32(u32_48)))
print(liba.rsqrt_f64(4), liba.rsqrt_f32(4))
print(list(liba.rsqrt_f64(f64_48)), list(liba.rsqrt_f32(f32_48)))
