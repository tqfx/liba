#!/usr/bin/env python
import os, sys

base = os.path.dirname(__file__)
path = os.path.dirname(base)
sys.path.insert(0, path)
if len(sys.argv) > 1:
    sys.stdout = open(sys.argv[1], "w")

import liba  # type: ignore

traj = liba.trajbell()
traj.gen(3, 2, 3, 0, 10)

N = 1000
x = [0.0] * N
T = traj.t / N
for i in range(N):
    x[i] = i * T

p = traj.pos(x)
v = traj.vel(x)
a = traj.acc(x)
j = traj.jer(x)

for i in range(N):
    print("%g,%g,%g,%g,%g" % (x[i], p[i], v[i], a[i], j[i]))

traj.t
traj.tv
traj.ta
traj.td
traj.taj
traj.tdj
traj.p0
traj.p1
traj.v0
traj.v1
traj.vm
traj.jm
traj.am
traj.dm
