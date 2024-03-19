#!/usr/bin/env python
import os, sys, math

base = os.path.dirname(__file__)
path = os.path.dirname(base)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

Ts = 1.0
f_0 = 1.0
f_e = 1000.0
c = (f_e - f_0) / Ts
T = 1.0 / 10000
t = 0
x = []
while t <= Ts:
    x.append(t)
    t += T
hpf = liba.hpf(10, 0.01)
for i in range(len(x)):
    x1 = math.cos(2 * math.pi * (f_0 * x[i] + 0.5 * c * x[i] * x[i]))
    print("%g,%g,%g" % (x[i], x1, hpf(x1)))

hpf.zero()
hpf.alpha
hpf.output
hpf.input
