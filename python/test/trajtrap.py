#!/usr/bin/env python
import os, sys

path = os.path.dirname(__file__)
path = os.path.dirname(path)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

traj = liba.trajtrap()
traj.gen(2, 2, -2, 0, 4)

N = 1000
T = traj.t / N
x = liba.new_num(N)
for i in range(N):
    x[i] = i * T

p = traj.pos(x)
v = traj.vel(x)
a = traj.acc(x)

for i in range(N):
    print("%g,%g,%g,%g" % (x[i], p[i], v[i], a[i]))

traj.t
traj.p0
traj.p1
traj.v0
traj.v1
traj.vc
traj.ta
traj.td
traj.pa
traj.pd
traj.ac
traj.de
