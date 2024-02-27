#!/usr/bin/env python
import os, sys, math, random

sys.path.insert(0, os.getcwd())
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

N = 100
x = [0.0] * N
T = math.pi * 0.1
lpf = liba.lpf(10, 0.01)
for i in range(N):
    x[i] = i * T
    x1 = math.sin(x[i]) + 0.2 * (random.random() - 0.5)
    print("%g,%g,%g" % (x[i], x1, lpf(x1)))

lpf.zero()
lpf.alpha
lpf.output
