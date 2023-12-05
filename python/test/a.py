#!/usr/bin/env python
import os, sys

sys.path.insert(0, os.getcwd())
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba

print(liba.hash_bkdr(b"0", 0))
print(liba.sqrt_u64(7), liba.sqrt_u32(7))
print(liba.sqrt_u64([4, 8]), liba.sqrt_u32([4, 8]))
print(liba.rsqrt_f64(4), liba.rsqrt_f32(4))
print(liba.rsqrt_f64([4, 8]), liba.rsqrt_f32([4, 8]))
