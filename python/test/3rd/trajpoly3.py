#!/usr/bin/env python
import os, sys

base = os.path.dirname(__file__)
path = os.path.dirname(base)
path = os.path.dirname(path)
sys.path.insert(0, path)
try:
    import numpy as np
    import matplotlib.pyplot as plt
except Exception as e:
    print(e)
    exit()

import liba  # type: ignore

t = (0, 1)
p = (0, 1)
v = (0, 1)
traj = liba.trajpoly3(t[1] - t[0], p[0], p[1], v[0], v[1])
data = np.arange(t[0], t[1], (t[1] - t[0]) / 1000)

text_p = "p="
if traj.c0[0]:
    text_p += "%g" % (traj.c0[0])
if traj.c0[1]:
    text_p += "%+g%s" % (traj.c0[1], "t")
if traj.c0[2]:
    text_p += "%+g%s" % (traj.c0[2], "t^2")
if traj.c0[3]:
    text_p += "%+g%s" % (traj.c0[3], "t^3")
text_p = text_p.replace("=+", "=")

text_v = "v="
if traj.c1[0]:
    text_v += "%g" % (traj.c1[0])
if traj.c1[1]:
    text_v += "%+g%s" % (traj.c1[1], "t")
if traj.c1[2]:
    text_v += "%+g%s" % (traj.c1[2], "t^2")
text_v = text_v.replace("=+", "=")

text_a = "a="
if traj.c2[0]:
    text_a += "%g" % (traj.c2[0])
if traj.c2[1]:
    text_a += "%+g%s" % (traj.c2[1], "t")
text_a = text_a.replace("=+", "=")

plt.figure("3 polynomial trajectory")

plt.subplot(311)
plt.title("cubic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, np.array(traj.pos(data), copy=False), "r-", label=text_p)
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, np.array(traj.vel(data), copy=False), "b-", label=text_v)
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, np.array(traj.acc(data), copy=False), "g-", label=text_a)
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(base, "trajectory_polynomial_3.png"))
plt.show()
