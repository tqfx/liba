#!/usr/bin/env python
import os, sys

sys.path.insert(0, os.getcwd())
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

t = (0, 1)
p = (0, 1)
v = (0, 1)
traj = liba.trajpoly3(t[1] - t[0], p[0], p[1], v[0], v[1])

N = 1000
x = [0.0] * N
T = (t[1] - t[0]) / N
for i in range(N):
    x[i] = i * T

p = traj.pos(x)
v = traj.vel(x)
a = traj.acc(x)

for i in range(N):
    print("%g,%g,%g,%g" % (x[i], p[i], v[i], a[i]))

traj.p
traj.v
traj.a
