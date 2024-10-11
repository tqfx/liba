#!/usr/bin/env python
from __future__ import print_function
import os, sys

path = os.path.dirname(__file__)
path = os.path.dirname(path)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

t = (0, 1)
p = (0, 1)
v = (0, 1)
traj = liba.trajpoly5(t[1] - t[0], p[0], p[1], v[0], v[1])

N = 1000
T = (t[1] - t[0]) / N
x = liba.new_float(N)
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
