#!/usr/bin/env python
import os, sys

base = os.path.dirname(__file__)
path = os.path.dirname(base)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

print(liba.hash_bkdr(b"0123456789"))
print(liba.hash_sdbm(b"0123456789"))
print(liba.sqrt_u64(7), liba.sqrt_u32(7))
print(liba.sqrt_u64([4, 8]), liba.sqrt_u32([4, 8]))
print(liba.rsqrt_f64(4), liba.rsqrt_f32(4))
print(liba.rsqrt_f64([4, 8]), liba.rsqrt_f32([4, 8]))
